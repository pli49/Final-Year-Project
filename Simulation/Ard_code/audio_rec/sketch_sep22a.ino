// FFT Test
//
// Compute a 1024 point Fast Fourier Transform (spectrum analysis)
// on audio connected to the Left Line-In pin.  By changing code,
// a synthetic sine wave can be input instead.
//
// The first 40 (of 512) frequency analysis bins are printed to
// the Arduino Serial Monitor.  Viewing the raw data can help you
// understand how the FFT works and what results to expect when
// using the data to control LEDs, motors, or other fun things!
//
// This example code is in the public domain.

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

const int myInput = AUDIO_INPUT_LINEIN;
const int led = LED_BUILTIN;
//const int myInput = AUDIO_INPUT_MIC;

// Create the Audio components.  These should be created in the
// order data flows, inputs/sources -> processing -> outputs
//
AudioInputI2S          audioInput;         // audio shield: mic or line-in
AudioSynthWaveformSine sinewave;
AudioAnalyzeFFT1024    myFFT;
AudioAnalyzeRMS        rms1;           //xy=789,282
AudioConnection        patchCord2(audioInput, 0, rms1, 0);
AudioOutputI2S         audioOutput;        // audio shield: headphones & line-out

// Connect either the live input or synthesized sine wave
AudioConnection patchCord1(audioInput, 0, myFFT, 0);
//AudioConnection patchCord1(sinewave, 0, myFFT, 0);

void setup() {
  Serial.begin(50000);
  // Audio connections require memory to work.  For more
  // detailed information, see the MemoryAndCpuUsage example
  AudioMemory(12);

  // Configure the window algorithm to use
  myFFT.windowFunction(AudioWindowHanning1024);
  //myFFT.windowFunction(NULL);

  // Create a synthetic sine wave, for testing
  // To use this, edit the connections above
  sinewave.amplitude(0.8);
  sinewave.frequency(1034.007);

  pinMode(led, OUTPUT);
}

void loop() {
  float n;
  int i; 
//  if (myFFT.available() && rms1.available()){
//    //Serial.print(10000*rms1.read());
//    //Serial.print(myFFT.read(4));
//    Serial.println();
//    if (10000*rms1.read()>= 700) {
//      Serial.print(10000*rms1.read());
//      if (myFFT.read(70)>=0.002){
//        Serial.print(myFFT.read(70));
//        Serial.print("yey");
//        
//        digitalWrite(led, HIGH);
//        delayMicroseconds(22);
//      } else {
//        digitalWrite(led, LOW);
//      }
//  }else{
//    digitalWrite(led, LOW);
//  }
//  }
//  if(rms1.available()){
//    Serial.print(10000*rms1.read());
//    Serial.print(",400,600");
//    Serial.println();Ll
//    delayMicroseconds(22);
//  }
  if (myFFT.available()) {
    // each time new FFT data is available
    // print it all to the Arduino Serial Monitor
    Serial.print("FFT: ");
    for (i=40; i<60; i++) {
      n = myFFT.read(i);
      if (n >= 0.005) {
        Serial.print(n);
        Serial.print(" ");
      } else {
        Serial.print("  -  "); // don't print "0.00"
      }
    }
    Serial.println();
  }
}
