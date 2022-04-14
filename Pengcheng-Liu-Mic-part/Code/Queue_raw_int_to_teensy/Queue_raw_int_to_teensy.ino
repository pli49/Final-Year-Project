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
AudioInputI2S            i2s;           //xy=566,356
AudioRecordQueue         queue1;         //xy=567,313
AudioConnection          patchCord1(i2s, 0, queue1, 0);
// GUItool: end automatically generated code

void setup() {
  Serial.begin(10000);
  AudioMemory(130); //assign memory for queue function
}
int j = 0;
void loop() {
  //only initialise once
  if(j == 0){
    queue1.begin(); // start monitoring
    j = 1;
  }

  while (1) {
    if (queue1.available())
    {
      int16_t* data = queue1.readBuffer();
      //Print out 1 bit 
      for (int i = 0; i < 128; i++)
        Serial.println(data[i]);

      queue1.freeBuffer();

    }
  }
}
