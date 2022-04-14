//doesn't work without the amplifier

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputI2S            i2s1;           //xy=166,134
AudioFilterStateVariable filter1;        //xy=364,131
AudioAnalyzeFFT1024      fft1024_1;      //xy=613,137
AudioConnection          patchCord1(i2s1, 0, filter1, 0);
AudioConnection          patchCord2(filter1, 0, fft1024_1, 0);
// GUItool: end automatically generated code


void setup() {
  AudioMemory(50);

//  filter1.frequency(30);
  filter1.frequency(30); // filter out DC & extremely low frequencies

  
}

void loop() {
  if (fft1024_1.available()) {
    // each time new FFT data is available
    // print 20 bins to the Arduino Serial Monitor
    Serial.print("FFT: ");
    for (int i = 0; i < 20; i++) {
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
