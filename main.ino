#include "config.h"
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include <synth_simple_drum.h>

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthSimpleDrum     drum2;          //xy=399,244
AudioSynthSimpleDrum     drum3;          //xy=424,310
AudioSynthSimpleDrum     drum1;          //xy=431,197
AudioSynthSimpleDrum     drum4;          //xy=464,374
AudioMixer4              mixer1;         //xy=737,265
AudioOutputI2S           i2s1;           //xy=979,214
AudioConnection          patchCord1(drum2, 0, mixer1, 1);
AudioConnection          patchCord2(drum3, 0, mixer1, 2);
AudioConnection          patchCord3(drum1, 0, mixer1, 0);
AudioConnection          patchCord4(drum4, 0, mixer1, 3);
AudioConnection          patchCord5(mixer1, 0, i2s1, 0);
AudioConnection          patchCord6(mixer1, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=930,518
// GUItool: end automatically generated code

static uint32_t next;

void setup() {
  //setup the accelerametor
  setup_ADXL343();
  setup_DistanceSensor();
  //setup_i2c_scanner();
  

  //set up the audio shield drum 
  Serial.begin(115200);

  // audio library init
  AudioMemory(15);

  next = millis() + 1000;

  AudioNoInterrupts();

  drum1.frequency(60);
  drum1.length(1500);
  drum1.secondMix(0.0);
  drum1.pitchMod(0.55);
  
  drum2.frequency(60);
  drum2.length(300);
  drum2.secondMix(0.0);
  drum2.pitchMod(1.0);
  
  drum3.frequency(3000);
  drum3.length(200);
  drum3.secondMix(1.0);
  drum3.pitchMod(0.5);

  drum4.frequency(1200);
  drum4.length(150);
  drum4.secondMix(0.0);
  drum4.pitchMod(0.0);
  
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);

  AudioInterrupts();

}

void detectDrum(int acceleration) {
  if (acceleration == 10) {
    drum1.noteOn();
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  runADXL343();
  //i2c_scanner();
  run_DistanceSensor();

  static uint32_t num = 0;
    
    Serial.print("drum1Sel = ");
    Serial.println(drum1Sel);
    
    if (distance <= 15) {
      if (Y1 == 0) {
        drum1.noteOn();
      } else {
        drum2.noteOn();
      }
    }
    
//    Serial.print("Diagnostics: ");
//    Serial.print(AudioProcessorUsageMax());
//    Serial.print(" ");
//    Serial.println(AudioMemoryUsageMax());
    AudioProcessorUsageMaxReset();
    
}
