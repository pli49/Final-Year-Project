

// this is not working



#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputI2S            i2s1;           //xy=298,292
AudioAmplifier           amp1;           //xy=588,274
AudioAnalyzeFFT1024      fft1024_1;      //xy=734,283
AudioConnection          patchCord1(i2s1, 0, amp1, 0);
AudioConnection          patchCord2(amp1, fft1024_1);
// GUItool: end automatically generated code



void setup() {
  AudioMemory(50);

//  filter1.frequency(30);
//  filter1.frequency(30); // filter out DC & extremely low frequencies
  amp1.gain(200); //try some values
  
//  amp1.gain(8.5);        // amplify sign to useful range
}



void loop() {
  if (fft1024_1.available()) {
    // each time new FFT data is available
    // print 20 bins to the Arduino Serial Monitor
    Serial.print("FFT: ");
    for (int i = 220; i < 240; i++) {
      float n = fft1024_1.read(i);
//      float n = fft1024_1.read(232);
      if (n >= 0.001) {
        Serial.print(n, 5);
        Serial.print(" ");
      } else {
        Serial.print("  --  "); // don't print "0.000"
      }
    }
    Serial.println();
  }
}
