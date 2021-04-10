#include <Audio.h>

// set SYNTH_DEBUG to enable debug logging (0=off,1=most,2=all messages)
#define SYNTH_DEBUG 0

// define MIDI channel
#define SYNTH_MIDICHANNEL 1

// inital poly mode (POLY, MONO or PORTAMENTO)
#define SYNTH_INITIALMODE POLY

// define tuning of A4 in Hz
#define SYNTH_TUNING 440

// gain at oscillator/filter input stage (1:1)
// keep low so filter does not saturate with resonance
#define GAIN_OSC 0.5

// gain in final mixer stage for polyphonic mode (4:1)
// (0.25 is the safe value but larger sounds better :) )
//#define GAIN_POLY 1.
#define GAIN_POLY 0.25

// gain in final mixer stage for monophonic modes
//#define GAIN_MONO 1.
#define GAIN_MONO 0.25

// define delay lines for modulation effects
#define DELAY_LENGTH (16*AUDIO_BLOCK_SAMPLES)
short delaylineL[DELAY_LENGTH];
short delaylineR[DELAY_LENGTH];

// audio memory
#define AMEMORY 50

// switch between USB and UART MIDI
#if defined USB_MIDI || defined USB_MIDI_SERIAL
#define SYNTH_USBMIDI
#endif

#define SYNTH_COM Serial

#include <MIDI.h>
MIDI_CREATE_DEFAULT_INSTANCE();

//////////////////////////////////////////////////////////////////////
// Data types and lookup tables
//////////////////////////////////////////////////////////////////////
struct Oscillator {
  AudioSynthWaveform*       wf;
  AudioFilterStateVariable* filt;
  AudioMixer4*              mix;
  AudioEffectEnvelope*      env;
  int8_t  note;
  uint8_t velocity;
};

// synth architecture in separate file
#include "SynthArch.h"

#define NVOICES 8
Oscillator oscs[NVOICES] = {
  { &waveform1, &filter1, &mixer1, &envelope1, -1, 0 },
  { &waveform2, &filter2, &mixer2, &envelope2, -1, 0 },
  { &waveform3, &filter3, &mixer3, &envelope3, -1, 0 },
  { &waveform4, &filter4, &mixer4, &envelope4, -1, 0 },
  { &waveform5, &filter5, &mixer5, &envelope5, -1, 0 },
  { &waveform6, &filter6, &mixer6, &envelope6, -1, 0 },
  { &waveform7, &filter7, &mixer7, &envelope7, -1, 0 },
  { &waveform8, &filter8, &mixer8, &envelope8, -1, 0 },
};

#define NPROGS 8
uint8_t progs[NPROGS] = {
  WAVEFORM_SINE,
  WAVEFORM_SQUARE,
  WAVEFORM_TRIANGLE,
  WAVEFORM_SAWTOOTH,
  WAVEFORM_SAWTOOTH_REVERSE,
  WAVEFORM_PULSE,
  WAVEFORM_SAMPLE_HOLD,
  WAVEFORM_ARBITRARY,
};

enum FilterMode_t {
  LOWPASS,
  BANDPASS,
  HIGHPASS,
  FILTEROFF,
  FILTERMODE_N,
};

//////////////////////////////////////////////////////////////////////
// Global variables
//////////////////////////////////////////////////////////////////////
float   masterVolume   = 0.3;
uint8_t currentProgram = WAVEFORM_SAWTOOTH;

bool  polyOn;
bool  omniOn;
bool  velocityOn;

bool  sustainPressed;
float channelVolume;
float panorama;
float pulseWidth; // 0.05-0.95
float pitchBend;  // -1/+1 oct
float pitchScale;
int   octCorr;

// filter
FilterMode_t filterMode;
float filtFreq; // 20-AUDIO_SAMPLE_RATE_EXACT/2.5
float filtReso; // 0.9-5.0
float filtAtt;  // 0-1

// envelope
bool  envOn;
float envDelay;   // 0-200
float envAttack;  // 0-200
float envHold;    // 0-200
float envDecay;   // 0-200
float envSustain; // 0-1
float envRelease; // 0-200

// FX
bool  flangerOn;
int   flangerOffset;
int   flangerDepth;
float flangerFreqCoarse;
float flangerFreqFine;

// portamento
bool     portamentoOn;
uint16_t portamentoTime;
int8_t   portamentoDir;
float    portamentoStep;
float    portamentoPos;

//////////////////////////////////////////////////////////////////////
// Handling of sounding and pressed notes
//////////////////////////////////////////////////////////////////////
int8_t notesOn[NVOICES]      = { -1, -1, -1, -1, -1, -1, -1, -1, };
int8_t notesPressed[NVOICES] = { -1, -1, -1, -1, -1, -1, -1, -1, };

inline void notesReset(int8_t* notes) {
  memset(notes,-1,NVOICES*sizeof(int8_t));
}

inline void notesAdd(int8_t* notes, uint8_t note) {
  int8_t *end=notes+NVOICES;
  do {
    if(*notes == -1) {
      *notes = note;
      break;
    }
  } while (++notes < end);
}

inline int8_t notesDel(int8_t* notes, uint8_t note) {
  int8_t lastNote = -1;
  int8_t *pos=notes, *end=notes+NVOICES;
  while (++pos < end && *(pos-1) != note);
  if (pos-1 != notes) lastNote = *(pos-2);
  while (pos < end) {
    *(pos-1) = *pos;
    if (*pos++ == -1) break;
  }
  if (*(end-1)==note || pos == end)
      *(end-1) = -1;
  return lastNote;
}

inline bool notesFind(int8_t* notes, uint8_t note) {
  int8_t *end=notes+NVOICES;
  do {
    if (*notes == note) return true;
  } while (++notes < end);
  return false;
}

//////////////////////////////////////////////////////////////////////
// Parameter control functions
//////////////////////////////////////////////////////////////////////
inline void updateFilterMode() {
  Oscillator *o=oscs,*end=oscs+NVOICES;
  do {
    for (uint8_t fm=0; fm<FILTERMODE_N; ++fm) {
      if (fm == filterMode) o->mix->gain(fm,filtAtt);
      else                  o->mix->gain(fm,0);
    }
  } while (++o < end);
}

inline void updateFilter() {
  Oscillator *o=oscs,*end=oscs+NVOICES;
  do {
    o->filt->frequency(filtFreq);
    o->filt->resonance(filtReso);
  } while (++o < end);
}

inline void updateEnvelope() {
  Oscillator *o=oscs,*end=oscs+NVOICES;
  do {
    o->env->delay(envDelay);
    o->env->attack(envAttack);
    o->env->hold(envHold);
    o->env->decay(envDecay);
    o->env->sustain(envSustain);
    o->env->release(envRelease);
  } while (++o < end);
}

inline void updateEnvelopeMode() {
  float env    = envOn ? 1 : 0;
  float noenv  = envOn ? 0 : 1;
  for (uint8_t i=0; i<2; ++i) {
    // env
    envmixer1.gain(i,env);
    envmixer2.gain(i,env);
    envmixer3.gain(i,env);
    envmixer4.gain(i,env);
    // no env
    envmixer1.gain(i+2,noenv);
    envmixer2.gain(i+2,noenv);
    envmixer3.gain(i+2,noenv);
    envmixer4.gain(i+2,noenv);
  }
}

void updateFlanger() {
  if (flangerOn) {
    AudioNoInterrupts();
    flangerL.voices(flangerOffset,flangerDepth,flangerFreqCoarse+flangerFreqFine);
    flangerR.voices(flangerOffset,flangerDepth,flangerFreqCoarse+flangerFreqFine);
    AudioInterrupts();
#if SYNTH_DEBUG > 0
    SYNTH_COM.print("Flanger: offset=");
    SYNTH_COM.print(flangerOffset);
    SYNTH_COM.print(", depth=");
    SYNTH_COM.print(flangerDepth);
    SYNTH_COM.print(", freq=");
    SYNTH_COM.println(flangerFreqCoarse+flangerFreqFine);
#endif
  } else {
    flangerL.voices(FLANGE_DELAY_PASSTHRU,0,0);
    flangerR.voices(FLANGE_DELAY_PASSTHRU,0,0);
  }
}

void resetAll() {
  polyOn     = true;
  omniOn     = false;
  velocityOn = true;

  filterMode     = FILTEROFF;
  sustainPressed = false;
  channelVolume  = 1.0;
  panorama       = 0.5;
  pulseWidth     = 0.5;
  pitchBend      = 0;
  pitchScale     = 1;
  octCorr        = currentProgram == WAVEFORM_PULSE ? 1 : 0;

  // filter
  filtFreq = 15000.;
  filtReso = 0.9;
  filtAtt  = 1.;

  // envelope
  envOn      = true;
  envDelay   = 0;
  envAttack  = 20;
  envHold    = 0;
  envDecay   = 0;
  envSustain = 1;
  envRelease = 20;

  // FX
  flangerOn         = false;
  flangerOffset     = DELAY_LENGTH/4;
  flangerDepth      = DELAY_LENGTH/16;
  flangerFreqCoarse = 0;
  flangerFreqFine   = .5;

  // portamento
  portamentoOn   = false;
  portamentoTime = 1000;
  portamentoDir  = 0;
  portamentoStep = 0;
  portamentoPos  = -1;

  updatePolyMode();
  updateFilterMode();
  updateEnvelope();
  updatePan();
}

inline void updateProgram() {
  if (currentProgram==WAVEFORM_PULSE) octCorr = 1;
  else                   octCorr = 0;

  Oscillator *o=oscs,*end=oscs+NVOICES;
  do {
    if (currentProgram==WAVEFORM_PULSE) o->wf->pulseWidth(pulseWidth);
    o->wf->begin(progs[currentProgram]);
  } while(++o < end);
}

inline void updatePulseWidth() {
  if (currentProgram!=WAVEFORM_PULSE) return;
  Oscillator *o=oscs,*end=oscs+NVOICES;
  do {
    if (o->note < 0) continue;
    o->wf->pulseWidth(pulseWidth);
  } while(++o < end);
}

inline void updatePitch() {
  Oscillator *o=oscs,*end=oscs+NVOICES;
  do {
    if (o->note < 0) continue;
    o->wf->frequency(noteToFreq(o->note));
  } while(++o < end);
}

inline void updateVolume() {
  Oscillator *o=oscs,*end=oscs+NVOICES;
  float velocity;
  do {
    if (o->note < 0) continue;
    velocity = velocityOn ? o->velocity/127. : 1;
    o->wf->amplitude(velocity*channelVolume*GAIN_OSC);
  } while(++o < end);
}

inline void updatePan() {
  float norm  = (polyOn && !portamentoOn) ? GAIN_POLY : GAIN_MONO;
  float left=norm, right=norm;
  if (panorama < 0.5) right *= 2*panorama;
  else left *= 2*(1-panorama);

  for (uint8_t i=0; i<4; ++i) {
    mixerL.gain(i,left);
    mixerR.gain(i,right);
  }
}

inline void updateMasterVolume() {
  // read the volume knob
  float vol = (float) analogRead(A1) / 1280.0;
  if( fabs(vol-masterVolume) > 0.01) {
    masterVolume = vol;
    sgtl5000_1.volume(masterVolume);
#if SYNTH_DEBUG > 0
    SYNTH_COM.print("Volume: ");
    SYNTH_COM.println(vol);
#endif
  }
}

inline void updatePolyMode() {
  allOff();
  updateEnvelopeMode();
  updatePan();
}

inline void updatePortamento()
{
  if (portamentoDir == 0) return;
  if (oscs->note < 0) {
    portamentoDir = 0;
    return;
  }
  if (portamentoDir < 0) {
    portamentoPos -= portamentoStep;
    if (portamentoPos < oscs->note) {
      portamentoPos = oscs->note;
      portamentoDir = 0;
    }
  }
  else {
    portamentoPos += portamentoStep;
    if (portamentoPos > oscs->note) {
      portamentoPos = oscs->note;
      portamentoDir = 0;
    }
  }
  oscs->wf->frequency(noteToFreq(portamentoPos));
}

//////////////////////////////////////////////////////////////////////
// Oscillator control functions
//////////////////////////////////////////////////////////////////////
inline float noteToFreq(float note) {
  // Sets all notes as an offset of A4 (#69)
  if (portamentoOn) note = portamentoPos;
  return SYNTH_TUNING*pow(2,(note - 69)/12.+pitchBend/pitchScale+octCorr);
}

inline void oscOn(Oscillator& osc, int8_t note, uint8_t velocity) {
  float v = velocityOn ? velocity/127. : 1;
  if (osc.note!=note) {
    osc.wf->frequency(noteToFreq(note));
    notesAdd(notesOn,note);
    if (envOn && !osc.velocity) osc.env->noteOn();
    osc.wf->amplitude(v*channelVolume*GAIN_OSC);
    osc.velocity = velocity;
    osc.note = note;
  } else if (velocity > osc.velocity) {
    osc.wf->amplitude(v*channelVolume*GAIN_OSC);
    osc.velocity = velocity;
  }
}

inline void oscOff(Oscillator& osc) {
  if (envOn) osc.env->noteOff();
  else       osc.wf->amplitude(0);
  notesDel(notesOn,osc.note);
  osc.note = -1;
  osc.velocity = 0;
}

inline void allOff() {
  Oscillator *o=oscs,*end=oscs+NVOICES;
  do {
    oscOff(*o);
    o->wf->amplitude(0);
    o->env->noteOff();
  } while(++o < end);
  notesReset(notesOn);
}

//////////////////////////////////////////////////////////////////////
// MIDI handlers
//////////////////////////////////////////////////////////////////////
void OnNoteOn(uint8_t channel, uint8_t note, uint8_t velocity) {
  if (!omniOn && channel != SYNTH_MIDICHANNEL) return;

#if SYNTH_DEBUG > 1
  SYNTH_COM.println("NoteOn");
#endif

  notesAdd(notesPressed,note);

  Oscillator *o=oscs;
  if (portamentoOn) {
    if (portamentoTime == 0 || portamentoPos < 0) {
      portamentoPos = note;
      portamentoDir = 0;
    } else if (portamentoPos > -1) {
      portamentoDir  = note > portamentoPos ? 1 : -1;
      portamentoStep = fabs(note-portamentoPos)/(portamentoTime);
    }
    *notesOn = -1;
    oscOn(*o, note, velocity);
  }
  else if (polyOn) {
    Oscillator *curOsc=0, *end=oscs+NVOICES;
    if (sustainPressed && notesFind(notesOn,note)) {
      do {
        if (o->note == note) {
          curOsc = o;
          break;
        }
      } while (++o < end);
    }
    for (o=oscs; o < end && !curOsc; ++o) {
      if (o->note < 0) {
        curOsc = o;
        break;
      }
    }
    if (!curOsc && *notesOn != -1) {
#if SYNTH_DEBUG > 0
      SYNTH_COM.println("Stealing voice");
#endif
      curOsc = OnNoteOffReal(channel,*notesOn,velocity,true);
    }
    if (!curOsc) return;
    oscOn(*curOsc, note, velocity);
  }
  else
  {
    *notesOn = -1;
    oscOn(*o, note, velocity);
  }

  return;
}

Oscillator* OnNoteOffReal(uint8_t channel, uint8_t note, uint8_t velocity, bool ignoreSustain) {
  if (!omniOn && channel != SYNTH_MIDICHANNEL) return 0;

#if SYNTH_DEBUG > 1
  SYNTH_COM.println("NoteOff");
#endif
  int8_t lastNote = notesDel(notesPressed,note);

  if (sustainPressed && !ignoreSustain) return 0;

  Oscillator *o=oscs;
  if (portamentoOn) {
    if (o->note == note) {
      if (lastNote != -1) {
        notesDel(notesOn,note);
        if (portamentoTime == 0) {
          portamentoPos = lastNote;
          portamentoDir = 0;
        } else {
          portamentoDir = lastNote > portamentoPos? 1 : -1;
          portamentoStep = fabs(lastNote-portamentoPos)/(portamentoTime);
        }
        oscOn(*o, lastNote, velocity);
      }
      else
      {
        oscOff(*o);
        portamentoPos = -1;
        portamentoDir = 0;
      }
    }
    if (oscs->note == note) {
      if (lastNote != -1) {
        notesDel(notesOn,o->note);
        oscOn(*o, lastNote, velocity);
      } else {
        oscOff(*o);
      }
    }
  }
  else if (polyOn) {
    Oscillator *end=oscs+NVOICES;
    do {
      if (o->note == note) break;
    } while (++o < end);
    if (o == end) return 0;
    oscOff(*o);
  } else {
    if (oscs->note == note) {
      if (lastNote != -1) {
        notesDel(notesOn,o->note);
        oscOn(*o, lastNote, velocity);
      } else {
        oscOff(*o);
      }
    }
  }

  return o;
}

inline void OnNoteOff(uint8_t channel, uint8_t note, uint8_t velocity) {
  OnNoteOffReal(channel,note,velocity,false);
}

void OnAfterTouchPoly(uint8_t channel, uint8_t note, uint8_t value) {
#if SYNTH_DEBUG > 0
  SYNTH_COM.print("AfterTouchPoly: channel ");
  SYNTH_COM.print(channel);
  SYNTH_COM.print(", note ");
  SYNTH_COM.print(note);
  SYNTH_COM.print(", value ");
  SYNTH_COM.println(value);
#endif
}

void OnControlChange(uint8_t channel, uint8_t control, uint8_t value) {
  if (!omniOn && channel != SYNTH_MIDICHANNEL) return;

  switch (control) {
  case 0: // bank select, do nothing (switch sounds via program change only)
    break;
  case 5: // portamento time
  {
    float portamentoRange = portamentoStep*portamentoTime;
    portamentoTime = value*50;
    portamentoStep = portamentoRange/portamentoTime;
    break;
  }
  case 7: // volume
    channelVolume = value/127.;
    updateVolume();
    break;
  case 9: // fix volume
    switch (value) {
    case 0:
      velocityOn = false;
      break;
    case 1:
      velocityOn = true;
      break;
    default:
      velocityOn = !velocityOn;
      break;
    }
    break;
  case 10: // pan
    panorama = value/127.;
    updatePan();
    break;
  case 12: // attack
    envAttack = value*200./127.;
    updateEnvelope();
    break;
  case 13: // release
    envRelease = value*200./127.;
    updateEnvelope();
    break;
  case 14: // filter frequency
    //filtFreq = value/2.5*AUDIO_SAMPLE_RATE_EXACT/127.;
    filtFreq = float(pow(value, 2));
    //filtFreq = float(pow(value, 3)/127.);
    updateFilter();
    break;
  case 15: // filter resonance
    filtReso = value*4.1/127.+0.9;
    updateFilter();
    break;
  case 16: // filter attenuation
    filtAtt = value/127.;
    updateFilterMode();
    break;
  case 17: // filter mode
    if (value < FILTERMODE_N) {
      filterMode = FilterMode_t(value);
    } else {
      filterMode = FilterMode_t((filterMode+1)%FILTERMODE_N);
    }
    updateFilterMode();
    break;
  case 18: // poly mode
    switch (value) {
    case 0:
      polyOn = true;
      portamentoOn = false;
      break;
    case 1:
      polyOn = false;
      portamentoOn = false;
      break;
    case 2:
      polyOn = false;
      portamentoOn = true;
      break;
    default: // cycle POLY, MONO, PORTAMENTO
    {
      bool tmp = polyOn;
      polyOn = portamentoOn;
      portamentoOn = !(tmp || portamentoOn);
      break;
    }
    }
    updatePolyMode();
    break;
  case 19: // envelope mode
    allOff();
    envOn = !envOn;
    updateEnvelopeMode();
    break;
  case 20: // delay
    envDelay = value*200./127.;
    updateEnvelope();
    break;
  case 21: // hold
    envHold = value*200./127.;
    updateEnvelope();
    break;
  case 22: // decay
    envDecay = value*200./127.;
    updateEnvelope();
    break;
  case 23: // sustain
    envSustain = value/127.;
    updateEnvelope();
    break;
  case 24: // pulse width
    pulseWidth = (value/127.)*0.9+0.05;
    updatePulseWidth();
    break;
  case 25: // flanger toggle
    if (value < 2)
        flangerOn = bool(value);
    else
        flangerOn = !flangerOn;
    updateFlanger();
    break;
  case 26: // flanger offset
    flangerOffset = int(value/127.*8)*DELAY_LENGTH/8;
    updateFlanger();
    break;
  case 27: // flanger depth
    flangerDepth = int(value/127.*8)*DELAY_LENGTH/8;
    updateFlanger();
    break;
  case 28: // flanger coarse frequency
    flangerFreqCoarse = value/127.*10.;
    updateFlanger();
    break;
  case 29: // flanger fine frequency
    flangerFreqFine = value/127.;
    updateFlanger();
    break;
  case 30: // pitch range in semitones
    pitchScale = 12./value;
    break;
  case 64: // sustain/damper pedal
    if (value > 63) sustainPressed = true;
    else {
      sustainPressed = false;
      Oscillator *o=oscs, *end=oscs+NVOICES;
      do {
        if (o->note != -1 && !notesFind(notesPressed,o->note)) oscOff(*o);
      } while (++o < end);
    }
    break;
  case 65: // portamento on/off
    if (polyOn) break;
    if (value > 63) {
      portamentoOn = true;
      if (oscs->note != -1) portamentoPos = oscs->note;
    }
    else portamentoOn = false;
    break;
  case 84: // portamento control (start note)
    portamentoPos = value;
    break;
  case 121: // controller reset
    resetAll();
    break;
  case 123: // all notes off
    allOff();
    break;
  case 124: // omni off
    allOff();
    omniOn = false;
    break;
  case 125: // omni on
    allOff();
    omniOn = true;
    break;
  case 126: // mono
    polyOn = false;
    portamentoOn = false;
    updatePolyMode();
    break;
  case 127: // poly
    polyOn = true;
    portamentoOn = false;
    updatePolyMode();
    break;
  default:
#if SYNTH_DEBUG > 0
    SYNTH_COM.print("Unhandled Control Change: channel ");
    SYNTH_COM.print(channel);
    SYNTH_COM.print(", control ");
    SYNTH_COM.print(control);
    SYNTH_COM.print(", value ");
    SYNTH_COM.println(value);
#endif
    break;
  }
#if 1 //0
  SYNTH_COM.print("Control Change: channel ");
  SYNTH_COM.print(channel);
  SYNTH_COM.print(", control ");
  SYNTH_COM.print(control);
  SYNTH_COM.print(", value ");
  SYNTH_COM.println(value);
#endif
}

void OnPitchChange(uint8_t channel, int pitch) {
  if (!omniOn && channel != SYNTH_MIDICHANNEL) return;

#if SYNTH_DEBUG > 1
  SYNTH_COM.print("PitchChange: channel ");
  SYNTH_COM.print(channel);
  SYNTH_COM.print(", pitch ");
  SYNTH_COM.println(pitch);
#endif

#ifdef SYNTH_USBMIDI
  if (pitch == 8192)
    pitchBend = 0;
  else
    pitchBend = (pitch-8192)/8192.;
#else
  pitchBend = pitch/8192.;
#endif

  updatePitch();
}

void OnProgramChange(uint8_t channel, uint8_t program) {
  if (!omniOn && channel!=SYNTH_MIDICHANNEL) return;

#if SYNTH_DEBUG > 1
  SYNTH_COM.print("ProgramChange: channel ");
  SYNTH_COM.print(channel);
  SYNTH_COM.print(", program ");
  SYNTH_COM.println(program);
#endif

  if (program <NPROGS) {
    if( program!=currentProgram) {
      currentProgram = program;
      updateProgram();
    }
  }
}

void OnAfterTouch(uint8_t channel, uint8_t pressure) {
  if (!omniOn && channel!=SYNTH_MIDICHANNEL) return;

#if SYNTH_DEBUG > 0
  SYNTH_COM.print("AfterTouch: channel ");
  SYNTH_COM.print(channel);
  SYNTH_COM.print(", pressure ");
  SYNTH_COM.println(pressure);
#endif
}

void OnSysEx( const uint8_t *data, uint16_t length, bool complete) {
#if SYNTH_DEBUG > 0
  SYNTH_COM.print("SysEx: length ");
  SYNTH_COM.print(length);
  SYNTH_COM.print(", complete ");
  SYNTH_COM.println(complete);
#endif
}

void OnRealTimeSystem(uint8_t realtimebyte) {
#if SYNTH_DEBUG > 0
  SYNTH_COM.print("RealTimeSystem: ");
  SYNTH_COM.println(realtimebyte);
#endif
}

void OnTimeCodeQFrame(uint16_t data)
{
#if SYNTH_DEBUG > 0
  SYNTH_COM.print("TimeCodeQuarterFrame: ");
  SYNTH_COM.println(data);
#endif
}

//////////////////////////////////////////////////////////////////////
// Debugging functions
//////////////////////////////////////////////////////////////////////
#if SYNTH_DEBUG > 0
float   statsCpu = 0;
uint8_t statsMem = 0;

void oscDump(uint8_t idx) {
  SYNTH_COM.print("Oscillator ");
  SYNTH_COM.print(idx);
  oscDump(oscs[idx]);
}

void oscDump(const Oscillator& o) {
  SYNTH_COM.print(" note=");
  SYNTH_COM.print(o.note);
  SYNTH_COM.print(", velocity=");
  SYNTH_COM.println(o.velocity);
}

inline void notesDump(int8_t* notes) {
  for (uint8_t i=0; i<NVOICES; ++i) {
    SYNTH_COM.print(' ');
    SYNTH_COM.print(notes[i]);
  }
  SYNTH_COM.println();
}

inline void printResources( float cpu, uint8_t mem) {
  SYNTH_COM.print( "CPU Usage: ");
  SYNTH_COM.print(cpu);
  SYNTH_COM.print( "%, Memory: ");
  SYNTH_COM.println(mem);
}

void performanceCheck() {
  static unsigned long last = 0;
  unsigned long now = millis();
  if ((now-last)>1000) {
    last = now;
    float cpu = AudioProcessorUsageMax();
    uint8_t mem = AudioMemoryUsageMax();
    if( (statsMem!=mem) || fabs(statsCpu-cpu)>1) {
      printResources( cpu, mem);
    }
    AudioProcessorUsageMaxReset();
    AudioMemoryUsageMaxReset();
    last = now;
    statsCpu = cpu;
    statsMem = mem;
  }
}

void printInfo() {
  SYNTH_COM.println();
  SYNTH_COM.print("Master Volume:        ");
  SYNTH_COM.println(masterVolume);
  SYNTH_COM.print("Current Program:      ");
  SYNTH_COM.println(currentProgram);
  SYNTH_COM.print("Poly On:              ");
  SYNTH_COM.println(polyOn);
  SYNTH_COM.print("Omni On:              ");
  SYNTH_COM.println(omniOn);
  SYNTH_COM.print("Velocity On:          ");
  SYNTH_COM.println(velocityOn);
  SYNTH_COM.println();
  SYNTH_COM.print("Sustain Pressed:      ");
  SYNTH_COM.println(sustainPressed);
  SYNTH_COM.print("Channel Volume:       ");
  SYNTH_COM.println(channelVolume);
  SYNTH_COM.print("Panorama:             ");
  SYNTH_COM.println(panorama);
  SYNTH_COM.print("Pulse Width:          ");
  SYNTH_COM.println(pulseWidth);
  SYNTH_COM.print("Pitch Bend:           ");
  SYNTH_COM.println(pitchBend);
  SYNTH_COM.println();
  SYNTH_COM.print("Filter Mode:          ");
  SYNTH_COM.println(filterMode);
  SYNTH_COM.print("Filter Frequency:     ");
  SYNTH_COM.println(filtFreq);
  SYNTH_COM.print("Filter Resonance:     ");
  SYNTH_COM.println(filtReso);
  SYNTH_COM.print("Filter Attenuation:   ");
  SYNTH_COM.println(filtAtt);
  SYNTH_COM.println();
  SYNTH_COM.print("Envelope On:          ");
  SYNTH_COM.println(envOn);
  SYNTH_COM.print("Envelope Delay:       ");
  SYNTH_COM.println(envDelay);
  SYNTH_COM.print("Envelope Attack:      ");
  SYNTH_COM.println(envAttack);
  SYNTH_COM.print("Envelope Hold:        ");
  SYNTH_COM.println(envHold);
  SYNTH_COM.print("Envelope Decay:       ");
  SYNTH_COM.println(envDecay);
  SYNTH_COM.print("Envelope Sustain:     ");
  SYNTH_COM.println(envSustain);
  SYNTH_COM.print("Envelope Release:     ");
  SYNTH_COM.println(envRelease);
  SYNTH_COM.println();
  SYNTH_COM.print("Flanger On:           ");
  SYNTH_COM.println(flangerOn);
  SYNTH_COM.print("Flanger Offset:       ");
  SYNTH_COM.println(flangerOffset);
  SYNTH_COM.print("Flanger Depth:        ");
  SYNTH_COM.println(flangerDepth);
  SYNTH_COM.print("Flanger Freq. Coarse: ");
  SYNTH_COM.println(flangerFreqCoarse);
  SYNTH_COM.print("Flanger Freq. Fine:   ");
  SYNTH_COM.println(flangerFreqFine);
  SYNTH_COM.print("Delay Line Length:    ");
  SYNTH_COM.println(DELAY_LENGTH);
  SYNTH_COM.println();
  SYNTH_COM.print("Portamento On:        ");
  SYNTH_COM.println(portamentoOn);
  SYNTH_COM.print("Portamento Time:      ");
  SYNTH_COM.println(portamentoTime);
  SYNTH_COM.print("Portamento Step:      ");
  SYNTH_COM.println(portamentoStep);
  SYNTH_COM.print("Portamento Direction: ");
  SYNTH_COM.println(portamentoDir);
  SYNTH_COM.print("Portamento Position:  ");
  SYNTH_COM.println(portamentoPos);
}

void printAbout()
{
  SYNTH_COM.println();
  SYNTH_COM.println("TeensySynth v0.1");
#ifdef SYNTH_USBMIDI
  SYNTH_COM.println("USB_MIDI enabled");
#endif
  SYNTH_COM.println("UART_MIDI enabled");
}

void selectCommand(char c) {
  switch (c) {
  case '\r':
    SYNTH_COM.println();
    break;
  case 'b':
    // print voice statistics
    SYNTH_COM.print("Notes Pressed:");
    notesDump(notesPressed);
    SYNTH_COM.print("Notes On:     ");
    notesDump(notesOn);
    break;
  case 'o':
    // print oscillator status
    for (uint8_t i=0; i<NVOICES; ++i)
        oscDump(i);
    break;
  case 's':
    // print cpu and mem usage
    printResources(statsCpu,statsMem);
    break;
  case 'r':
    // reset parameters
    resetAll();
    break;
  case 'i':
    // print info
    printInfo();
    break;
  case '?':
    // print about
    printAbout();
    break;
  case '\t':
    // reboot Teensy
    *(uint32_t*)0xE000ED0C = 0x5FA0004;
    break;
  case ' ':
    // send note off
    allOff();
    break;
  default:
    break;
  }
}

#endif

#include "saw.h"

//////////////////////////////////////////////////////////////////////
// setup() and loop()
//////////////////////////////////////////////////////////////////////
void setup() {
  SYNTH_COM.begin(115200);

  AudioMemory(AMEMORY);
  sgtl5000_1.enable();
  sgtl5000_1.volume(masterVolume);

  {
    Oscillator *o=oscs,*end=oscs+NVOICES;
    do {
      o->wf->arbitraryWaveform(reinterpret_cast<const int16_t*>(saw),0);
    } while(++o < end);
  }

  resetAll();
  updateProgram();

  flangerL.begin(delaylineL,DELAY_LENGTH,FLANGE_DELAY_PASSTHRU,0,0);
  flangerR.begin(delaylineR,DELAY_LENGTH,FLANGE_DELAY_PASSTHRU,0,0);
  updateFlanger();

#ifdef SYNTH_USBMIDI
  // see arduino/hardware/teensy/avr/libraries/USBHost_t36/USBHost_t36.h
  usbMIDI.setHandleNoteOff(OnNoteOff);
  usbMIDI.setHandleNoteOn(OnNoteOn);
  usbMIDI.setHandleVelocityChange(OnAfterTouchPoly);
  usbMIDI.setHandleControlChange(OnControlChange);
  usbMIDI.setHandlePitchChange(OnPitchChange);
  usbMIDI.setHandleProgramChange(OnProgramChange);
  usbMIDI.setHandleAfterTouch(OnAfterTouch);
  usbMIDI.setHandleSysEx(OnSysEx);
  //usbMIDI.setHandleRealTimeSystem(OnRealTimeSystem);
  usbMIDI.setHandleTimeCodeQuarterFrame(OnTimeCodeQFrame);
#endif
  // see arduino/hardware/teensy/avr/libraries/MIDI/src/MIDI.h
  MIDI.begin();
  MIDI.setHandleNoteOff(OnNoteOff);
  MIDI.setHandleNoteOn(OnNoteOn);
  MIDI.setHandleAfterTouchPoly(OnAfterTouchPoly);
  MIDI.setHandleControlChange(OnControlChange);
  MIDI.setHandlePitchBend(OnPitchChange);
  MIDI.setHandleProgramChange(OnProgramChange);
  MIDI.setHandleAfterTouchChannel(OnAfterTouch);
  // the following functions need a different callback signature but they are
  // not used anyways, so...
  //MIDI.setHandleSystemExclusive(OnSysEx);
  //MIDI.setHandleTimeCodeQuarterFrame(OnTimeCodeQFrame);

  delay(1000);
}

void loop() {
#ifdef SYNTH_USBMIDI
  usbMIDI.read();
#endif
  MIDI.read();

  updateMasterVolume();
  updatePortamento();

#if SYNTH_DEBUG > 0
  performanceCheck();
  while (SYNTH_COM.available())
    selectCommand(SYNTH_COM.read());
#endif
}
