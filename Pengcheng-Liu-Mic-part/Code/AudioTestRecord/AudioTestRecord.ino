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
#include <stdint.h>

// GUItool: begin automatically generated code
AudioInputI2S            i2s1;           //xy=279.00000381469727,691.7999973297119
AudioRecordQueue         queue1;         //xy=562.0000076293945,690.0000104904175
AudioConnection          patchCord1(i2s1, 1, queue1, 0);
// GUItool: end automatically generated code

void setup() {
Serial.begin(50000);
  // Audio connections require memory to work.  For more
  // detailed information, see the MemoryAndCpuUsage example
  queue1.begin();
  AudioMemory(360);
}

void loop() {
  if (queue1.available()>0){
    int16_t* A = queue1.readBuffer();
    Serial.println(*A);
    queue1.freeBuffer();
    if (queue1.available() == 52){
      queue1.clear();
    }
  }
}
