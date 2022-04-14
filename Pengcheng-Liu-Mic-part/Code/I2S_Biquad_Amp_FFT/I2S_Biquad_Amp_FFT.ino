//working fft with biquad filter and amplifier
//please rearrange the fft range to fit different frequency (232 is around 10k Hz)
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputI2S            i2s1;           //xy=166,134
AudioFilterBiquad        biquad1;        //xy=317.00000381469727,130.80000495910645
AudioAmplifier           amp1;           //xy=462.00000762939453,131.4000072479248
AudioAnalyzeFFT1024      fft1024_1;      //xy=613,137
AudioConnection          patchCord1(i2s1, 0, biquad1, 0);
AudioConnection          patchCord2(biquad1, amp1);
AudioConnection          patchCord3(amp1, fft1024_1);
// GUItool: end automatically generated code

void setup() {
  AudioMemory(50);
  
  biquad1.setHighpass(0,30,0.707);// filter out DC & extremely low frequencies
  
  amp1.gain(20); //try some values
  
}

void loop() {
  if (fft1024_1.available()) {
    // each time new FFT data is available
    // print 20 bins to the Arduino Serial Monitor
//    Serial.print("FFT: ");
    for (int i = 275; i < 285; i++) {
      float n = fft1024_1.read(i);
//      float n = fft1024_1.read(232);
      if (n >= 0.001) {
        Serial.print(n, 3);
        Serial.print(" ");
      } else {
        Serial.print("  --  "); // don't print "0.000"
      }
    }
    Serial.println();
  }
}
