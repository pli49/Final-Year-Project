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

#define SIZE 124750


void setup() {
Serial.begin(1000);
  // Audio connections require memory to work.  For more
  // detailed information, see the MemoryAndCpuUsage example
  AudioMemory(20);
}


void loop() {
  
  int16_t *buff = (int16_t *)malloc(sizeof(int16_t)*SIZE); 
  Serial.println("Buffer read----------------------------");
  for (int i = 0; i < SIZE; i++){
    if(rms1.available()){
      buff[i] = rms1.read();
      delayMicroseconds(50);
    }

  }
  Serial.println("Buffer is Full--------------------------");
  for (int j = 0; j<SIZE; j++){
    Serial.println(buff[j]);
  }
  Serial.println("Buffer free--------------------------");
  free(buff);
    


}
