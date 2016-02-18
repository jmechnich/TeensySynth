#ifndef SYNTHARCH_H
#define SYNTHARCH_H

#include <Audio.h>

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

#endif
