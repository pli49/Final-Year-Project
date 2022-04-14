//Teensy -> SPH0645
//3.3V -> 3V
//GND -> GND
//21 -> BCLK
//20 -> LRCL
//8 -> DOUT
//GND -> SEL

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputI2S            i2s2;           //xy=373,144
AudioAnalyzeRMS          rms1;           //xy=789,282
AudioConnection          patchCord1(i2s2, 0, rms1, 0);
// GUItool: end automatically generated code
void setup() {
Serial.begin(50000);
  // Audio connections require memory to work.  For more
  // detailed information, see the MemoryAndCpuUsage example
  AudioMemory(20);

}

void loop() {
  if(rms1.available()){
    Serial.print(1000*rms1.read());
    Serial.print(",400,600"); //stable the plotting
    Serial.println();
  }
}
