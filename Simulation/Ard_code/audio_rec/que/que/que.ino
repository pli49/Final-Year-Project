#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputI2S            i2s;           //xy=566,356
AudioRecordQueue         queue1;         //xy=567,313
AudioFilterStateVariable filter1;        //xy=325,101
AudioAmplifier           amp1;           //xy=470,93

AudioConnection          patchCord1(i2s, 0, filter1, 0);
AudioConnection          patchCord2(filter1, 2, amp1, 0);
AudioConnection          patchCord3(amp1, 0, queue1, 0);
// GUItool: end automatically generated code

void setup() {
  Serial.begin(115200);
  AudioMemory(130);
  filter1.frequency(30); // filter out DC & extremely low frequencies
  amp1.gain(8.5);        // amplify sign to useful range
}

void loop() {
  queue1.begin(); // start monitoring
  while (1) {
    if (queue1.available()){
      int16_t* data = queue1.readBuffer();
      //Print out 1 bit 
        for (int i = 0; i < 128; i++){
          Serial.println(data[i]);
        }
    }
      queue1.freeBuffer();
    }
    
}
