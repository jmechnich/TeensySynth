#include <Audio.h>

// define SYNTH_DEBUG to enable debug logging on HWSerial 1 (digital pins 0/1)
#define SYNTH_DEBUG

// define IGNORE_OTHERCHANNELS to only listen to MIDI channel 1
#define IGNORE_OTHERCHANNELS

// define MIDI channel
#define SYNTH_MIDICHANNEL 1

// define tuning of A4 in Hz
#define SYNTH_TUNING 440

// gain in final mixer stage for POLY mode
// (0.25 is the safe value but 1 sounds better :) )
#define POLY_GAIN 0.75
//#define POLY_GAIN 0.25

// Audio architecture generated with
// http://www.pjrc.com/teensy/gui/

// GUItool: begin automatically generated code
AudioSynthWaveform       waveform1;      //xy=80,180
AudioSynthWaveform       waveform2;      //xy=80,240
AudioSynthWaveform       waveform3;      //xy=80,300
AudioSynthWaveform       waveform4;      //xy=80,360
AudioSynthWaveform       waveform5;      //xy=80,420
AudioSynthWaveform       waveform6;      //xy=80,480
AudioSynthWaveform       waveform7;      //xy=80,540
AudioSynthWaveform       waveform8;      //xy=80,600
AudioFilterStateVariable filter1;        //xy=260,180
AudioFilterStateVariable filter2;        //xy=260,240
AudioFilterStateVariable filter3;        //xy=260,300
AudioFilterStateVariable filter4;        //xy=260,360
AudioFilterStateVariable filter5;        //xy=260,420
AudioFilterStateVariable filter6;        //xy=260,480
AudioFilterStateVariable filter7;        //xy=260,540
AudioFilterStateVariable filter8;        //xy=260,600
AudioMixer4              mixer1;         //xy=440,180
AudioMixer4              mixer2;         //xy=440,240
AudioMixer4              mixer3;         //xy=440,300
AudioMixer4              mixer4;         //xy=440,360
AudioMixer4              mixer5;         //xy=440,420
AudioMixer4              mixer6;         //xy=440,480
AudioMixer4              mixer7;         //xy=440,540
AudioMixer4              mixer8;         //xy=440,600
AudioEffectEnvelope      envelope1;      //xy=640,180
AudioEffectEnvelope      envelope2;      //xy=640,240
AudioEffectEnvelope      envelope3;      //xy=640,300
AudioEffectEnvelope      envelope4;      //xy=640,360
AudioEffectEnvelope      envelope5;      //xy=640,420
AudioEffectEnvelope      envelope6;      //xy=640,480
AudioEffectEnvelope      envelope7;      //xy=640,540
AudioEffectEnvelope      envelope8;      //xy=640,600
AudioMixer4              envmixer1;      //xy=900,210
AudioMixer4              envmixer2;      //xy=900,330
AudioMixer4              envmixer3;      //xy=900,450
AudioMixer4              envmixer4;      //xy=900,570
AudioMixer4              mixerL;         //xy=1160,270
AudioMixer4              mixerR;         //xy=1160,510
AudioEffectFlange        flangerL;       //xy=1300,270
AudioEffectFlange        flangerR;       //xy=1300,510
AudioOutputI2S           i2s1;           //xy=1450,390
AudioConnection          patchCord1(waveform1, 0, filter1, 0);
AudioConnection          patchCord2(waveform1, 0, mixer1, 3);
AudioConnection          patchCord3(waveform2, 0, filter2, 0);
AudioConnection          patchCord4(waveform2, 0, mixer2, 3);
AudioConnection          patchCord5(waveform3, 0, filter3, 0);
AudioConnection          patchCord6(waveform3, 0, mixer3, 3);
AudioConnection          patchCord7(waveform4, 0, filter4, 0);
AudioConnection          patchCord8(waveform4, 0, mixer4, 3);
AudioConnection          patchCord9(waveform5, 0, filter5, 0);
AudioConnection          patchCord10(waveform5, 0, mixer5, 3);
AudioConnection          patchCord11(waveform6, 0, filter6, 0);
AudioConnection          patchCord12(waveform6, 0, mixer6, 3);
AudioConnection          patchCord13(waveform7, 0, filter7, 0);
AudioConnection          patchCord14(waveform7, 0, mixer7, 3);
AudioConnection          patchCord15(waveform8, 0, filter8, 0);
AudioConnection          patchCord16(waveform8, 0, mixer8, 3);
AudioConnection          patchCord17(filter1, 0, mixer1, 0);
AudioConnection          patchCord18(filter1, 1, mixer1, 1);
AudioConnection          patchCord19(filter1, 2, mixer1, 2);
AudioConnection          patchCord20(filter2, 0, mixer2, 0);
AudioConnection          patchCord21(filter2, 1, mixer2, 1);
AudioConnection          patchCord22(filter2, 2, mixer2, 2);
AudioConnection          patchCord23(filter3, 0, mixer3, 0);
AudioConnection          patchCord24(filter3, 1, mixer3, 1);
AudioConnection          patchCord25(filter3, 2, mixer3, 2);
AudioConnection          patchCord26(filter4, 0, mixer4, 0);
AudioConnection          patchCord27(filter4, 1, mixer4, 1);
AudioConnection          patchCord28(filter4, 2, mixer4, 2);
AudioConnection          patchCord29(filter5, 0, mixer5, 0);
AudioConnection          patchCord30(filter5, 1, mixer5, 1);
AudioConnection          patchCord31(filter5, 2, mixer5, 2);
AudioConnection          patchCord32(filter6, 0, mixer6, 0);
AudioConnection          patchCord33(filter6, 1, mixer6, 1);
AudioConnection          patchCord34(filter6, 2, mixer6, 2);
AudioConnection          patchCord35(filter7, 0, mixer7, 0);
AudioConnection          patchCord36(filter7, 1, mixer7, 1);
AudioConnection          patchCord37(filter7, 2, mixer7, 2);
AudioConnection          patchCord38(filter8, 0, mixer8, 0);
AudioConnection          patchCord39(filter8, 1, mixer8, 1);
AudioConnection          patchCord40(filter8, 2, mixer8, 2);
AudioConnection          patchCord41(mixer1, 0, envelope1, 0);
AudioConnection          patchCord42(mixer1, 0, envmixer1, 2);
AudioConnection          patchCord43(mixer2, 0, envelope2, 0);
AudioConnection          patchCord44(mixer2, 0, envmixer1, 3);
AudioConnection          patchCord45(mixer3, 0, envelope3, 0);
AudioConnection          patchCord46(mixer3, 0, envmixer2, 2);
AudioConnection          patchCord47(mixer4, 0, envelope4, 0);
AudioConnection          patchCord48(mixer4, 0, envmixer2, 3);
AudioConnection          patchCord49(mixer5, 0, envelope5, 0);
AudioConnection          patchCord50(mixer5, 0, envmixer3, 2);
AudioConnection          patchCord51(mixer6, 0, envelope6, 0);
AudioConnection          patchCord52(mixer6, 0, envmixer3, 3);
AudioConnection          patchCord53(mixer7, 0, envelope7, 0);
AudioConnection          patchCord54(mixer7, 0, envmixer4, 2);
AudioConnection          patchCord55(mixer8, 0, envelope8, 0);
AudioConnection          patchCord56(mixer8, 0, envmixer4, 3);
AudioConnection          patchCord57(envelope1, 0, envmixer1, 0);
AudioConnection          patchCord58(envelope2, 0, envmixer1, 1);
AudioConnection          patchCord59(envelope3, 0, envmixer2, 0);
AudioConnection          patchCord60(envelope4, 0, envmixer2, 1);
AudioConnection          patchCord61(envelope5, 0, envmixer3, 0);
AudioConnection          patchCord62(envelope6, 0, envmixer3, 1);
AudioConnection          patchCord63(envelope7, 0, envmixer4, 0);
AudioConnection          patchCord64(envelope8, 0, envmixer4, 1);
AudioConnection          patchCord65(envmixer1, 0, mixerL, 0);
AudioConnection          patchCord66(envmixer1, 0, mixerR, 0);
AudioConnection          patchCord67(envmixer2, 0, mixerL, 1);
AudioConnection          patchCord68(envmixer2, 0, mixerR, 1);
AudioConnection          patchCord69(envmixer3, 0, mixerL, 2);
AudioConnection          patchCord70(envmixer3, 0, mixerR, 2);
AudioConnection          patchCord71(envmixer4, 0, mixerL, 3);
AudioConnection          patchCord72(envmixer4, 0, mixerR, 3);
AudioConnection          patchCord73(mixerL, 0, flangerL, 0);
AudioConnection          patchCord74(mixerR, 0, flangerR, 0);
AudioConnection          patchCord75(flangerL, 0, i2s1, 0);
AudioConnection          patchCord76(flangerR, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=80,60
// GUItool: end automatically generated code

// define delay lines for modulation effects
#define DELAY_LENGTH (16*AUDIO_BLOCK_SAMPLES)
short delaylineL[DELAY_LENGTH];
short delaylineR[DELAY_LENGTH];

#define AMEMORY 50

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

#define NVOICES 8
Oscillator oscs[NVOICES] = {
  { &waveform1, &filter1, &mixer1, &envelope1, -1, 0 },
  { &waveform2, &filter2, &mixer2, &envelope2, -1, 0 },
  { &waveform3, &filter3, &mixer3, &envelope3, -1, 0 },
  { &waveform4, &filter4, &mixer4, &envelope4, -1, 0 },
  { &waveform5, &filter5, &mixer5, &envelope5, -1, 0 },
  { &waveform6, &filter6, &mixer6, &envelope6, -1, 0 },
  { &waveform7, &filter7, &mixer7, &envelope7, -1, 0 },
  { &waveform8, &filter8, &mixer7, &envelope8, -1, 0 },
};

enum PolyMode_t {
  POLY,
  MONO,
  //MONO_L,
  //MONO_R,
  POLYMODE_N,
};

enum FilterMode_t {
  LOWPASS,
  BANDPASS,
  HIGHPASS,
  FILTEROFF,
  FILTERMODE_N,
};

#define NPROGS 7
uint8_t progs[NPROGS] = {
  WAVEFORM_SINE,
  WAVEFORM_SQUARE,
  WAVEFORM_TRIANGLE,
  WAVEFORM_SAWTOOTH,
  WAVEFORM_SAWTOOTH_REVERSE,
  WAVEFORM_PULSE,
  WAVEFORM_SAMPLE_HOLD,
};

//////////////////////////////////////////////////////////////////////
// Global variables
//////////////////////////////////////////////////////////////////////
float   masterVolume   = 0.3;
uint8_t currentProgram = 3;

PolyMode_t polyMode;
bool       sustainPressed;
float      channelVolume;
float      panorama;
float      pulseWidth;
float      pitchBend;

// filter
FilterMode_t filterMode;
float filtFreq; // 20-AUDIO_SAMPLE_RATE_EXACT/2.5
float filtReso; // 0.9-5.0
float filtOcta; // 0-7

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

int8_t notesOn[NVOICES]      = { -1, -1, -1, -1, -1, -1, -1, -1, };
int8_t notesPressed[NVOICES] = { -1, -1, -1, -1, -1, -1, -1, -1, };

float   statsCpu = 0;
uint8_t statsMem = 0;

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
      if (fm == filterMode) o->mix->gain(fm,1);
      else                  o->mix->gain(fm,0);
    }
  } while (++o < end);
}

inline void updateFilter() {
  Oscillator *o=oscs,*end=oscs+NVOICES;
  do {
    o->filt->frequency(filtFreq);
    o->filt->resonance(filtReso);
    o->filt->octaveControl(filtOcta);
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
  float gainOn = polyMode == POLY ? 0.5 : 1;
  float env    = envOn ? gainOn : 0;
  float noenv  = envOn ? 0 : gainOn;
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
#ifdef SYNTH_DEBUG
    Serial1.print("Flanger: offset=");
    Serial1.print(flangerOffset);
    Serial1.print(", depth=");
    Serial1.print(flangerDepth);
    Serial1.print(", freq=");
    Serial1.println(flangerFreqCoarse+flangerFreqFine);    
#endif
  } else {
    flangerL.voices(FLANGE_DELAY_PASSTHRU,0,0);
    flangerR.voices(FLANGE_DELAY_PASSTHRU,0,0);        
  }
}

void resetAll() {
  polyMode       = POLY;
  filterMode     = FILTEROFF;
  sustainPressed = false;
  channelVolume  = 1.0;
  panorama       = 0.5;
  pulseWidth     = 0.5;
  pitchBend      = 0;

  // filter
  filtFreq = 10000.;
  filtReso = 0.7;
  filtOcta = 0;

  // envelope
  envOn      = false;
  envDelay   = 0;
  envAttack  = 50;
  envHold    = 50;
  envDecay   = 50;
  envSustain = 0.75;
  envRelease = 50;

  // FX
  flangerOn         = false;
  flangerOffset     = DELAY_LENGTH/4;
  flangerDepth      = DELAY_LENGTH/16;
  flangerFreqCoarse = 0;
  flangerFreqFine   = .5;

  updatePolyMode();
  updateFilterMode();
  updateEnvelope();
  updatePan();
}

inline void updateProgram() {
  Oscillator *o=oscs,*end=oscs+NVOICES;
  do {
    if (currentProgram==5) o->wf->pulseWidth(pulseWidth);
    o->wf->begin(progs[currentProgram]);
  } while(++o < end);
}

inline void updatePulseWidth() {
  if (currentProgram!=5) return;
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
  do {
    if (o->note < 0) continue;
    o->wf->amplitude(o->velocity/127.*channelVolume);
  } while(++o < end);
}

inline void updatePan() {
  float norm  = polyMode == POLY ? POLY_GAIN : 1;
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
#ifdef SYNTH_DEBUG
    Serial1.print("Volume: ");
    Serial1.println(vol);
#endif
  }
}

inline void updatePolyMode() {
  allOff();
  updateEnvelopeMode();
  updatePan();
}

inline void updatePortamento()
{}

//////////////////////////////////////////////////////////////////////
// Oscillator control functions
//////////////////////////////////////////////////////////////////////
inline float noteToFreq(float note) {
  // Sets all notes as an offset of A4 (#69)
  return SYNTH_TUNING*pow(2,(note - 69)/12.+pitchBend);
}

inline void oscOn(Oscillator& osc, int8_t note, uint8_t velocity) {
  if (osc.note!=note) {
    osc.wf->frequency(noteToFreq(note));
    notesAdd(notesOn,note);
    osc.wf->amplitude(velocity/127.*channelVolume);
    osc.velocity = velocity;
    osc.note = note;
    if (envOn)
      osc.env->noteOn();
  } else {
    if (velocity > osc.velocity) {
      osc.wf->amplitude(velocity/127.*channelVolume);
      osc.velocity = velocity;
    }
  }
}

inline void oscOff(Oscillator& osc) {
  if (envOn)
    osc.env->noteOff();
  else
    osc.wf->amplitude(0);
  notesDel(notesOn,osc.note);
  osc.note = -1;
  osc.velocity = 0;
}

inline void allOff() {
  Oscillator *o=oscs,*end=oscs+NVOICES;
  do {
    oscOff(*o);
    if (envOn) o->wf->amplitude(0);
  } while(++o < end);
  notesReset(notesOn);
}

//////////////////////////////////////////////////////////////////////
// MIDI handlers
//////////////////////////////////////////////////////////////////////
void OnNoteOn(uint8_t channel, uint8_t note, uint8_t velocity) {
#ifdef IGNORE_OTHERCHANNELS
  if (channel != SYNTH_MIDICHANNEL) return;
#endif

#if 0 //#ifdef SYNTH_DEBUG
  Serial1.println("NoteOn");
#endif

  notesAdd(notesPressed,note);

  Oscillator *curOsc=0, *o=oscs, *end=oscs+NVOICES;
  switch(polyMode) {
  case POLY:
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
#ifdef SYNTH_DEBUG
      Serial1.println("Stealing voice");
#endif
      curOsc = OnNoteOffReal(channel,*notesOn,velocity,true);
    }
    if (!curOsc) return;
    oscOn(*curOsc, note, velocity);
    break;
  case MONO:
    oscOn(*oscs, note, velocity);
    break;
  default:
    break;
  }

  return;
}

Oscillator* OnNoteOffReal(uint8_t channel, uint8_t note, uint8_t velocity, bool ignoreSustain) {
#ifdef IGNORE_OTHERCHANNELS
  if (channel != SYNTH_MIDICHANNEL) return 0;
#endif

#if 0 //#ifdef SYNTH_DEBUG
  Serial1.println("NoteOff");
#endif
  int8_t lastNote = notesDel(notesPressed,note);
  
  if (sustainPressed && !ignoreSustain) return 0;

  Oscillator *o=oscs, *end=oscs+NVOICES;
  switch(polyMode) {
  case POLY:
    do {
      if (o->note == note) break;
    } while (++o < end);
    if (o == end) return 0;
    oscOff(*o);
    break;
  case MONO:
    if (oscs->note == note) {
      oscOff(*o);
      if (lastNote != -1) oscOn(*o, lastNote, velocity);
    }
    break;
  default:
    break;
  }
  
  return o;
}

inline void OnNoteOff(uint8_t channel, uint8_t note, uint8_t velocity) {
  OnNoteOffReal(channel,note,velocity,false);
}

void OnControlChange(uint8_t channel, uint8_t control, uint8_t value) {
#ifdef IGNORE_OTHERCHANNELS
  if (channel != SYNTH_MIDICHANNEL) return;
#endif

  switch (control) {
    case 0: // bank select, do nothing (switch sounds via program change only)
      break;
    case 7: // volume
      channelVolume = value/127.;
      updateVolume();
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
      filtFreq = value/2.5*AUDIO_SAMPLE_RATE_EXACT/127.;
      updateFilter();
      break;
    case 15: // filter resonance
      filtReso = value*4.1/127.+0.9;
      updateFilter();
      break;
    case 16: // filter octave control
      filtOcta = value*7./127.;
      updateFilter();
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
      if (value < POLYMODE_N) {
        polyMode = PolyMode_t(value);
      } else {
        polyMode = PolyMode_t((polyMode+1)%POLYMODE_N);
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
      pulseWidth = value/127.;
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
    case 64: // sustain/damper pedal
      if (value > 63) {
        sustainPressed = true;
      } else {
        sustainPressed = false;
        Oscillator *o=oscs, *end=oscs+NVOICES;
        do {
          if (o->note != -1 && !notesFind(notesPressed,o->note)) oscOff(*o);
        } while (++o < end);
      }
      break;
    case 121: // controller reset
      resetAll();
      break;
    case 123: // all notes off
      allOff();
      break;
    default:
#ifdef SYNTH_DEBUG
      Serial1.print("Unhandled Control Change: channel ");
      Serial1.print(channel);
      Serial1.print(", control ");
      Serial1.print(control);
      Serial1.print(", value ");
      Serial1.println(value);
#endif
      break;
  }    
}

void OnPitchChange(uint8_t channel, int pitch) {
#ifdef IGNORE_OTHERCHANNELS
  if (channel != SYNTH_MIDICHANNEL) return;
#endif

#if 0 //#ifdef SYNTH_DEBUG
  Serial1.print("PitchChange: channel ");
  Serial1.print(channel);
  Serial1.print(", pitch ");
  Serial1.println(pitch);
#endif

  if (pitch == 8192)
    pitchBend = 0;
  else
    pitchBend = (pitch-8192)/8192.;
  updatePitch();
}

void OnProgramChange(uint8_t channel, uint8_t program) {
#ifdef IGNORE_OTHERCHANNELS
  if (channel!=SYNTH_MIDICHANNEL) return;
#endif

#if 0 //#ifdef SYNTH_DEBUG
  Serial1.print("ProgramChange: channel ");
  Serial1.print(channel);
  Serial1.print(", program ");
  Serial1.println(program);
#endif

  if (program <NPROGS) {
    if( program!=currentProgram) {
      currentProgram = program;
      updateProgram();
    }
  }
}

void OnAfterTouch(uint8_t channel, uint8_t pressure) {
#ifdef IGNORE_OTHERCHANNELS
  if (channel!=SYNTH_MIDICHANNEL) return;
#endif

#ifdef SYNTH_DEBUG
  Serial1.print("AfterTouch: channel ");
  Serial1.print(channel);
  Serial1.print(", pressure ");
  Serial1.println(pressure);
#endif
}

void OnSysEx( const uint8_t *data, uint16_t length, bool complete) {
#ifdef SYNTH_DEBUG
  Serial1.print("SysEx: length ");
  Serial1.print(length);
  Serial1.print(", complete ");
  Serial1.println(complete);
#endif
}

void OnRealTimeSystem(uint8_t realtimebyte) {
#ifdef SYNTH_DEBUG
  Serial1.print("RealTimeSystem: ");
  Serial1.println(realtimebyte);
#endif
}

void OnTimeCodeQFrame(uint16_t data)
{
#ifdef SYNTH_DEBUG
  Serial1.print("TimeCodeQuarterFrame: ");
  Serial1.println(data);
#endif
}
        
//////////////////////////////////////////////////////////////////////
// Debugging functions
//////////////////////////////////////////////////////////////////////
#ifdef SYNTH_DEBUG
void oscDump(uint8_t idx) {
  Serial1.print("Oscillator ");
  Serial1.print(idx);
  oscDump(oscs[idx]);
}

void oscDump(const Oscillator& o) {
  Serial1.print(" note=");
  Serial1.print(o.note);
  Serial1.print(", velocity=");
  Serial1.println(o.velocity);  
}

inline void notesDump(int8_t* notes) {
  for (uint8_t i=0; i<NVOICES; ++i) {
    Serial1.print(' ');
    Serial1.print(notes[i]);
  }
  Serial1.println();
}

inline void printResources( float cpu, uint8_t mem) {
  Serial1.print( "CPU Usage: ");
  Serial1.print(cpu);
  Serial1.print( "%, Memory: ");
  Serial1.println(mem);
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
  Serial1.print("Delay line length: ");
  Serial1.println(DELAY_LENGTH);
}

void selectCommand(char c) {
  switch (c) {
    case '\r':
      Serial1.println();
      break;
    case 'b':
      Serial1.print("Notes Pressed:");
      notesDump(notesPressed);
      Serial1.print("Notes On:     ");
      notesDump(notesOn);
      break;
    case 'o':
      for (uint8_t i=0; i<NVOICES; ++i)
        oscDump(i);
      break;
    case 's':
      printResources(statsCpu,statsMem);
      break;
    case 'r':
      resetAll();
      break;
    case 'i':
      printInfo();
      break;
    case ' ':
      allOff();
      break;
    default:
      break;
  }   
}

#endif

//////////////////////////////////////////////////////////////////////
// setup() and loop()
//////////////////////////////////////////////////////////////////////
void setup() {
#ifdef SYNTH_DEBUG
  Serial1.begin(115200);
#endif
  
  AudioMemory(AMEMORY);
  sgtl5000_1.enable();
  sgtl5000_1.volume(masterVolume);

  resetAll();
  updateProgram();
  
  flangerL.begin(delaylineL,DELAY_LENGTH,FLANGE_DELAY_PASSTHRU,0,0);
  flangerR.begin(delaylineR,DELAY_LENGTH,FLANGE_DELAY_PASSTHRU,0,0);
  updateFlanger();

  usbMIDI.setHandleNoteOff(OnNoteOff);
  usbMIDI.setHandleNoteOn(OnNoteOn);
  usbMIDI.setHandleControlChange(OnControlChange);
  usbMIDI.setHandlePitchChange(OnPitchChange);
  usbMIDI.setHandleProgramChange(OnProgramChange);
  usbMIDI.setHandleAfterTouch(OnAfterTouch);
  usbMIDI.setHandleSysEx(OnSysEx);
  //usbMIDI.setHandleRealTimeSystem(OnRealTimeSystem);
  usbMIDI.setHandleTimeCodeQuarterFrame(OnTimeCodeQFrame);
 
  delay(1000);

#ifdef SYNTH_DEBUG
  Serial1.println();
  Serial1.println("TeensySynth v0.1");
#endif
}

void loop() {
  usbMIDI.read();
  updateMasterVolume();
  updatePortamento();

#ifdef SYNTH_DEBUG
  performanceCheck();
  while (Serial1.available())
    selectCommand(Serial1.read());
#endif
}
