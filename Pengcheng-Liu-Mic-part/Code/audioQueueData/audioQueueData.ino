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
AudioInputI2S            i2s2;           //xy=233.00000381469727,163.00000190734863
AudioRecordQueue         queue1;         //xy=470,163
AudioConnection          patchCord1(i2s2, 0, queue1, 0);
// GUItool: end automatically generated code



void setup() {
  // put your setup code here, to run once:
  Serial.begin(1000);
  // Audio connections require memory to work.  For more
  // detailed information, see the MemoryAndCpuUsage example
  AudioMemory(60);
}


void loop() {
  queue1.begin();
  if (queue1.available() >= 2) {
    Serial.println("someting available");
    byte buffer[498];
    // Fetch 2 blocks from the audio library and copy
    // into a 512 byte buffer.  The Arduino SD library
    // is most efficient when full 512 byte sector size
    // writes are used.
    memcpy(buffer, queue1.readBuffer(), 249);
    Serial.println(*queue1.readBuffer());
    queue1.freeBuffer();
    memcpy(buffer+249, queue1.readBuffer(), 249);
    queue1.freeBuffer();

    for (int j = 0; j<498; j++){
      Serial.println(buffer[j]);
    }

  }
}
