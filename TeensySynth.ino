#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

//#define SYNTH_FILTER
#define AMEMORY 12
#define NVOICES 8

struct Oscillator {
  AudioSynthWaveform*       wf;
#ifdef SYNTH_FILTER
  AudioFilterStateVariable* filt;
  AudioMixer4*              mix;
  AudioEffectEnvelope*      env;
#endif
  int note;
  int idx;
  uint8_t velocity;
};

#ifdef SYNTH_FILTER

// GUItool: begin automatically generated code
AudioSynthWaveform       waveform1;      //xy=79,220
AudioSynthWaveform       waveform2;      //xy=84,293
AudioSynthWaveform       waveform3;      //xy=85,354
AudioSynthWaveform       waveform5;      //xy=85,482
AudioSynthWaveform       waveform4;      //xy=86,415
AudioSynthWaveform       waveform8;      //xy=93,667
AudioSynthWaveform       waveform6;      //xy=95,540
AudioSynthWaveform       waveform7;      //xy=97,603
AudioFilterStateVariable filter1;        //xy=263,225
AudioFilterStateVariable filter5;        //xy=266,479
AudioFilterStateVariable filter2;        //xy=267,292
AudioFilterStateVariable filter4;        //xy=267,416
AudioFilterStateVariable filter3;        //xy=269,353
AudioFilterStateVariable filter6;        //xy=271,542
AudioFilterStateVariable filter7;        //xy=271,602
AudioFilterStateVariable filter8;        //xy=273,664
AudioMixer4              mixer9;         //xy=452,357
AudioMixer4              mixer8;         //xy=454,293
AudioMixer4              mixer12;        //xy=453,548
AudioMixer4              mixer10;        //xy=454,421
AudioMixer4              mixer7;         //xy=457,227
AudioMixer4              mixer11;        //xy=456,485
AudioMixer4              mixer13;        //xy=456,610
AudioMixer4              mixer14;        //xy=456,671
AudioEffectEnvelope      envelope1;      //xy=649,232
AudioEffectEnvelope      envelope7;      //xy=655,614
AudioEffectEnvelope      envelope3;      //xy=656,366
AudioEffectEnvelope      envelope5;      //xy=658,490
AudioEffectEnvelope      envelope6;      //xy=659,547
AudioEffectEnvelope      envelope4;      //xy=662,427
AudioEffectEnvelope      envelope2;      //xy=664,302
AudioEffectEnvelope      envelope8;      //xy=664,673
AudioMixer4              mixer2;         //xy=930,386
AudioMixer4              mixer3;         //xy=933,480
AudioMixer4              mixer1;         //xy=935,297
AudioMixer4              mixer4;         //xy=939,566
AudioMixer4              mixer5;         //xy=1170,357
AudioMixer4              mixer6;         //xy=1176,485
AudioOutputI2S           i2s1;           //xy=1338,415
AudioConnection          patchCord1(waveform1, 0, filter1, 0);
AudioConnection          patchCord2(waveform1, 0, mixer7, 3);
AudioConnection          patchCord3(waveform2, 0, filter2, 0);
AudioConnection          patchCord4(waveform2, 0, mixer8, 3);
AudioConnection          patchCord5(waveform3, 0, filter3, 0);
AudioConnection          patchCord6(waveform3, 0, mixer9, 3);
AudioConnection          patchCord7(waveform5, 0, filter5, 0);
AudioConnection          patchCord8(waveform5, 0, mixer11, 3);
AudioConnection          patchCord9(waveform4, 0, filter4, 0);
AudioConnection          patchCord10(waveform4, 0, mixer10, 3);
AudioConnection          patchCord11(waveform8, 0, filter8, 0);
AudioConnection          patchCord12(waveform8, 0, mixer14, 3);
AudioConnection          patchCord13(waveform6, 0, filter6, 0);
AudioConnection          patchCord14(waveform6, 0, mixer12, 3);
AudioConnection          patchCord15(waveform7, 0, filter7, 0);
AudioConnection          patchCord16(waveform7, 0, mixer13, 3);
AudioConnection          patchCord17(filter1, 0, mixer7, 0);
AudioConnection          patchCord18(filter1, 1, mixer7, 1);
AudioConnection          patchCord19(filter1, 2, mixer7, 2);
AudioConnection          patchCord20(filter5, 0, mixer11, 0);
AudioConnection          patchCord21(filter5, 1, mixer11, 1);
AudioConnection          patchCord22(filter5, 2, mixer11, 2);
AudioConnection          patchCord23(filter2, 0, mixer8, 0);
AudioConnection          patchCord24(filter2, 1, mixer8, 1);
AudioConnection          patchCord25(filter2, 2, mixer8, 2);
AudioConnection          patchCord26(filter4, 0, mixer10, 0);
AudioConnection          patchCord27(filter4, 1, mixer10, 1);
AudioConnection          patchCord28(filter4, 2, mixer10, 2);
AudioConnection          patchCord29(filter3, 0, mixer9, 0);
AudioConnection          patchCord30(filter3, 1, mixer9, 1);
AudioConnection          patchCord31(filter3, 2, mixer9, 2);
AudioConnection          patchCord32(filter6, 0, mixer12, 0);
AudioConnection          patchCord33(filter6, 1, mixer12, 1);
AudioConnection          patchCord34(filter6, 2, mixer12, 2);
AudioConnection          patchCord35(filter7, 0, mixer13, 0);
AudioConnection          patchCord36(filter7, 1, mixer13, 1);
AudioConnection          patchCord37(filter7, 2, mixer13, 2);
AudioConnection          patchCord38(filter8, 0, mixer14, 0);
AudioConnection          patchCord39(filter8, 1, mixer14, 1);
AudioConnection          patchCord40(filter8, 2, mixer14, 2);
AudioConnection          patchCord41(mixer9, envelope3);
AudioConnection          patchCord42(mixer8, envelope2);
AudioConnection          patchCord43(mixer12, envelope6);
AudioConnection          patchCord44(mixer10, envelope4);
AudioConnection          patchCord45(mixer7, envelope1);
AudioConnection          patchCord46(mixer11, envelope5);
AudioConnection          patchCord47(mixer13, envelope7);
AudioConnection          patchCord48(mixer14, envelope8);
AudioConnection          patchCord49(envelope1, 0, mixer1, 0);
AudioConnection          patchCord50(envelope1, 0, mixer2, 0);
AudioConnection          patchCord51(envelope7, 0, mixer3, 2);
AudioConnection          patchCord52(envelope7, 0, mixer4, 2);
AudioConnection          patchCord53(envelope3, 0, mixer1, 2);
AudioConnection          patchCord54(envelope3, 0, mixer2, 2);
AudioConnection          patchCord55(envelope5, 0, mixer3, 0);
AudioConnection          patchCord56(envelope5, 0, mixer4, 0);
AudioConnection          patchCord57(envelope6, 0, mixer3, 1);
AudioConnection          patchCord58(envelope6, 0, mixer4, 1);
AudioConnection          patchCord59(envelope4, 0, mixer1, 3);
AudioConnection          patchCord60(envelope4, 0, mixer2, 3);
AudioConnection          patchCord61(envelope2, 0, mixer1, 1);
AudioConnection          patchCord62(envelope2, 0, mixer2, 1);
AudioConnection          patchCord63(envelope8, 0, mixer3, 3);
AudioConnection          patchCord64(envelope8, 0, mixer4, 3);
AudioConnection          patchCord65(mixer2, 0, mixer6, 0);
AudioConnection          patchCord66(mixer3, 0, mixer5, 1);
AudioConnection          patchCord67(mixer1, 0, mixer5, 0);
AudioConnection          patchCord68(mixer4, 0, mixer6, 1);
AudioConnection          patchCord69(mixer5, 0, i2s1, 0);
AudioConnection          patchCord70(mixer6, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=192,114
// GUItool: end automatically generated code

Oscillator oscs[NVOICES] = {
  { &waveform1, &filter1, &mixer7,  &envelope1, -1, 0, 0 },
  { &waveform2, &filter2, &mixer8,  &envelope2, -1, 0, 0 },
  { &waveform3, &filter3, &mixer9,  &envelope3, -1, 0, 0 },
  { &waveform4, &filter4, &mixer10, &envelope4, -1, 0, 0 },
  { &waveform5, &filter5, &mixer11, &envelope5, -1, 0, 0 },
  { &waveform6, &filter6, &mixer12, &envelope6, -1, 0, 0 },
  { &waveform7, &filter7, &mixer13, &envelope7, -1, 0, 0 },
  { &waveform8, &filter8, &mixer14, &envelope8, -1, 0, 0 },
};

#else

// GUItool: begin automatically generated code
AudioSynthWaveform       waveform1;      //xy=395,244
AudioSynthWaveform       waveform2;      //xy=400,317
AudioSynthWaveform       waveform3;      //xy=401,378
AudioSynthWaveform       waveform5;      //xy=401,506
AudioSynthWaveform       waveform4;      //xy=402,439
AudioSynthWaveform       waveform8;      //xy=409,691
AudioSynthWaveform       waveform6;      //xy=411,564
AudioSynthWaveform       waveform7;      //xy=413,627
AudioMixer4              mixer2;         //xy=930,386
AudioMixer4              mixer3;         //xy=933,480
AudioMixer4              mixer1;         //xy=935,297
AudioMixer4              mixer4;         //xy=939,566
AudioMixer4              mixer5;         //xy=1170,357
AudioMixer4              mixer6;         //xy=1176,485
AudioOutputI2S           i2s1;           //xy=1338,415
AudioConnection          patchCord1(waveform1, 0, mixer1, 0);
AudioConnection          patchCord2(waveform1, 0, mixer2, 0);
AudioConnection          patchCord3(waveform2, 0, mixer1, 1);
AudioConnection          patchCord4(waveform2, 0, mixer2, 1);
AudioConnection          patchCord5(waveform3, 0, mixer1, 2);
AudioConnection          patchCord6(waveform3, 0, mixer2, 2);
AudioConnection          patchCord7(waveform5, 0, mixer3, 0);
AudioConnection          patchCord8(waveform5, 0, mixer4, 0);
AudioConnection          patchCord9(waveform4, 0, mixer1, 3);
AudioConnection          patchCord10(waveform4, 0, mixer2, 3);
AudioConnection          patchCord11(waveform8, 0, mixer3, 3);
AudioConnection          patchCord12(waveform8, 0, mixer4, 3);
AudioConnection          patchCord13(waveform6, 0, mixer3, 1);
AudioConnection          patchCord14(waveform6, 0, mixer4, 1);
AudioConnection          patchCord15(waveform7, 0, mixer3, 2);
AudioConnection          patchCord16(waveform7, 0, mixer4, 2);
AudioConnection          patchCord17(mixer2, 0, mixer6, 0);
AudioConnection          patchCord18(mixer3, 0, mixer5, 1);
AudioConnection          patchCord19(mixer1, 0, mixer5, 0);
AudioConnection          patchCord20(mixer4, 0, mixer6, 1);
AudioConnection          patchCord21(mixer5, 0, i2s1, 0);
AudioConnection          patchCord22(mixer6, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=192,114
// GUItool: end automatically generated code

Oscillator oscs[NVOICES] = {
  { &waveform1, -1, 0, 0 },
  { &waveform2, -1, 0, 0 },
  { &waveform3, -1, 0, 0 },
  { &waveform4, -1, 0, 0 },
  { &waveform5, -1, 0, 0 },
  { &waveform6, -1, 0, 0 },
  { &waveform7, -1, 0, 0 },
  { &waveform8, -1, 0, 0 },
};

#endif

#define SYNTH_DEBUG
#define IGNORE_OTHERCHANNELS

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

enum PolyMode_t {
  POLY,
  MONO_L,
  MONO_R,
  MONO,
};

uint8_t midiChannel    = 1;
float   tuningPitch    = 440;
float   masterVolume   = 0.3;
uint8_t currentProgram = 3;

PolyMode_t polyMode;
bool       sustainPressed;
float      channelVolume;
float      panorama;
float      pulseWidth;
float      pitchBend;

inline void resetAll() {
  polyMode       = POLY;
  sustainPressed = false;
  channelVolume  = 1.0;
  panorama       = 0.5;
  pulseWidth     = 0.5;
  pitchBend      = 0;

#ifdef SYNTH_FILTER
  for (uint8_t i=0; i < NVOICES; ++i) {
    oscs[i].mix->gain(0,0);
    oscs[i].mix->gain(1,0);
    oscs[i].mix->gain(2,0);
    oscs[i].mix->gain(3,1);
    oscs[i].env->attack(50);
    oscs[i].env->hold(50);
    oscs[i].env->decay(50);
    oscs[i].env->sustain(0.75);
  }
#endif
}

inline void oscOn( Oscillator& osc, int8_t note, uint8_t velocity) {
  // Sets all notes as an offset of A4 (#69)
  int8_t noteNumberAfterOffset = note - 69; 
  osc.wf->frequency(tuningPitch * pow(2,noteNumberAfterOffset/12.+pitchBend));
  osc.wf->amplitude(velocity/127.*channelVolume);
#ifdef SYNTH_FILTER
  osc.env->noteOn();
#endif
  osc.note = note;
  osc.velocity = velocity;
}

inline void oscOff( Oscillator& osc) {
  osc.wf->amplitude(0);
#ifdef SYNTH_FILTER
  osc.env->noteOff();
#endif
  osc.note = -1;
  osc.idx  = 0;
}

inline void allOff() {
  for (uint8_t i=0; i<NVOICES; ++i) {
    oscOff(oscs[i]);
  }
}

inline void updateProgram() {
  for (uint8_t i=0; i<NVOICES; ++i) {
    if (currentProgram==5) {
      oscs[i].wf->pulseWidth(pulseWidth);
    }
    oscs[i].wf->begin(progs[currentProgram]);
  }
}

inline void updatePitch() {
  for (uint8_t i=0; i<NVOICES; ++i) {
    int8_t note = oscs[i].note;
    if (note < 0) continue;
    note -= 69; 
    oscs[i].wf->frequency(tuningPitch * pow(2,note/12.+pitchBend));
  }
}

inline void updateVolume() {
  for (uint8_t i=0; i<NVOICES; ++i) {
    if (oscs[i].note < 0) continue;
    oscs[i].wf->amplitude(oscs[i].velocity/127.*channelVolume);
  }
}

inline void updatePan() {
  for (uint8_t i=0; i<2; ++i) {
    mixer5.gain(i,1-panorama);
    mixer6.gain(i,panorama);
  }
}

void OnNoteOn(uint8_t channel, uint8_t note, uint8_t velocity) {
#ifdef IGNORE_OTHERCHANNELS
  if (channel != midiChannel)
    return;
#endif

#if 0 //#ifdef SYNTH_DEBUG
  Serial1.println("NoteOn");
#endif

  Oscillator* curOsc = 0;
  switch(polyMode) {
    case(POLY):
      for (uint8_t i=0; i<NVOICES; ++i) {
        if (!curOsc && oscs[i].note < 0) {
          curOsc = &oscs[i];
        }
      }
      if (!curOsc) return;
      oscOn( *curOsc, note, velocity);
      break;
    case(MONO):
      curOsc = &oscs[0];
      oscOn( *curOsc, note, velocity);
      break;
    default:
      break;
  }
}

void OnNoteOff(uint8_t channel, uint8_t note, uint8_t velocity) {
#ifdef IGNORE_OTHERCHANNELS
  if (channel != midiChannel)
    return;
#endif

#if 0 //#ifdef SYNTH_DEBUG
  Serial1.println("NoteOff");
#endif
  if (sustainPressed) return;

  Oscillator* curOsc = 0;
  switch(polyMode) {
    case(POLY):
      for (uint8_t i=0; i<NVOICES; ++i) {
        if (oscs[i].note == note) {
          curOsc = &oscs[i];
          break;
        }
      }
      if (!curOsc) return;
      oscOff(*curOsc);
      break;
    case (MONO):
      curOsc = &oscs[0];
      if (curOsc->note == note)
        oscOff(*curOsc);
      break;
    default:
      break;
  }
}

void OnControlChange(uint8_t channel, uint8_t control, uint8_t value) {
#ifdef IGNORE_OTHERCHANNELS
  if (channel != midiChannel)
    return;
#endif

//#ifdef SYNTH_DEBUG
  Serial1.print("ControlChange: channel ");
  Serial1.print(channel);
  Serial1.print(", control ");
  Serial1.print(control);
  Serial1.print(", value ");
  Serial1.println(value);
//#endif

  switch (control) {
    case(0):
      // bank select, do nothing (switch sounds via program change only)
      break;
    case(3):
      // poly mode
      switch (value) {
        case (0):
          polyMode = MONO;
          allOff();
          break;
        case (127):
          polyMode = POLY;
          allOff();
          break;
        default:
          break;
      }  
      break;
    case(7):
      // volume
      channelVolume = value/127.;
      updateVolume();
      break;
    case (10):
      // pan
      panorama = value/127.;
      updatePan();
      break;
    case(64):
      // sustain pedal
      if (value == 127) {
        sustainPressed = true;
      } else {
        sustainPressed = false;
        allOff();
      }
      break;
    case(121):
      // reset controllers
      resetAll();
      break;
    case(123):
      // all notes off
      allOff();
      break;
    default:
      Serial1.print("Unhandled Control Change ");
      Serial1.println(control);
      break;
  }    
}

void OnPitchChange(uint8_t channel, int pitch) {
#ifdef IGNORE_OTHERCHANNELS
  if (channel != midiChannel)
    return;
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
  if (channel != midiChannel)
    return;
#endif

//#ifdef SYNTH_DEBUG
  Serial1.print("ProgramChange: channel ");
  Serial1.print(channel);
  Serial1.print(", program ");
  Serial1.println(program);
//#endif
  if (program <NPROGS) {
    if( program != currentProgram) {
      currentProgram = program;
      updateProgram();
    }
  }
}

void OnAfterTouch(uint8_t channel, uint8_t pressure) {
#ifdef IGNORE_OTHERCHANNELS
  if (channel != midiChannel)
    return;
#endif

//#ifdef SYNTH_DEBUG
  Serial1.print("AfterTouch: channel ");
  Serial1.print(channel);
  Serial1.print(", pressure ");
  Serial1.println(pressure);
//#endif
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

void setup() {
  Serial1.begin(115200);
  
  AudioMemory(AMEMORY);
  sgtl5000_1.enable();
  sgtl5000_1.volume(masterVolume);

  resetAll();
  updateProgram();
  
  for (uint8_t i=0; i<4; ++i) {
    mixer1.gain(i,0.25);
    mixer2.gain(i,0.25);
    mixer3.gain(i,0.25);
    mixer4.gain(i,0.25);
  }
  updatePan();
  delay(1000);
  
  usbMIDI.setHandleNoteOff(OnNoteOff);
  usbMIDI.setHandleNoteOn(OnNoteOn);
  usbMIDI.setHandleControlChange(OnControlChange);
  usbMIDI.setHandlePitchChange(OnPitchChange);
  usbMIDI.setHandleProgramChange(OnProgramChange);
  usbMIDI.setHandleAfterTouch(OnAfterTouch);

  Serial1.println();
  Serial1.println("TeensySynth v0.1");
}

inline void printResources( float cpu, uint8_t mem) {
  Serial1.print( "CPU Usage: ");
  Serial1.print(cpu);
  Serial1.print( "%, Memory: ");
  Serial1.println(mem);
}

void performanceCheck() {
  static unsigned long last = 0;
  static float   lastCpu = 0;
  static uint8_t lastMem = 0;
  unsigned long now = millis();
  if ((now-last) > 1000) {
    last = now;
    float   cpu = AudioProcessorUsageMax();
    uint8_t mem = AudioMemoryUsageMax();
    if( (lastMem != mem) || fabs(lastCpu-cpu) > 0.1) {
      printResources( cpu, mem);
    }   
    AudioProcessorUsageMaxReset();
    AudioMemoryUsageMaxReset();
    last = now;
    lastCpu = cpu;
    lastMem = mem;
  }
}

void loop() {
  usbMIDI.read();
  updateMasterVolume();
#ifdef SYNTH_DEBUG
  performanceCheck();
#endif
}

