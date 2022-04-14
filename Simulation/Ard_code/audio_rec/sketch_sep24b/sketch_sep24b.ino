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

struct audio_buffer{
  int16_t audio;
  //int16_t* pre;
  struct audio_buffer* nxt;
};

struct audio_buffer *head = NULL;
struct audio_buffer *strt = NULL;


void setup() {
  Serial.begin(10000);
  AudioMemory(130);
}


int j = 0;
int k = 0;
int ii = 0;
int p = 0;
int16_t audio_data_buffer[40000];

void loop() {
  if(j == 0){
    queue1.begin(); // start monitoring
    j = 1;    
  }

  
  uint16_t start_time = micros();
  while(1) {
    if (queue1.available())
    {
      int16_t* data = queue1.readBuffer();
      //Print out 1 bit 
      for (int i = 0; i < 128; i++) {
        if (ii > 40000) {
          
          uint16_t stop_time = micros();
          uint16_t run_time = stop_time - start_time;
          if (p == 0) {
            Serial.println(run_time);
            p = 1;
          }
          break;
        }
        Serial.println(data[i]);
      
      
        audio_data_buffer[ii++] = data[i];

    }
//    if (ii > 40000) {
//      break;
//    }
    queue1.freeBuffer();
  }
  }
}
