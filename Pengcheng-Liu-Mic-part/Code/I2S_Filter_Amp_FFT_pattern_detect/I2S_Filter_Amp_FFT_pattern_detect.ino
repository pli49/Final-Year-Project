#include <Audio.h>

// GUItool: begin automatically generated code
AudioInputI2S            i2s1;           //xy=180,111
AudioFilterStateVariable filter1;        //xy=325,101
AudioAmplifier           amp1;           //xy=470,93
AudioAnalyzeFFT1024      fft1024_1;      //xy=616,102
AudioConnection          patchCord1(i2s1, 0, filter1, 0);
AudioConnection          patchCord2(filter1, 2, amp1, 0);
AudioConnection          patchCord3(amp1, fft1024_1);
// GUItool: end automatically generated code

void setup() {
  AudioMemory(50);

//  filter1.frequency(30);
  filter1.frequency(30); // filter out DC & extremely low frequencies
  amp1.gain(100); //try some values
  
}

void loop() {
  if (fft1024_1.available()) {
//    Serial.println(fft1024_1.read(232), 3);
//  }
//    for (int i = 160; i<170;i++){
//      float n = fft1024_1.read(i);
//      if (n >= 0.001) {
//        Serial.print(n, 3);
//        Serial.print(" ");
//      } else {
//        Serial.print("  --  "); // don't print "0.000"
//      }
//    }
//    Serial.println();
//  }
//    float n = fft1024_1.read(209); //9k Hz
    float n = fft1024_1.read(163); //7k Hz
//    Serial.println(n);
    if (n>0.001){
      Serial.println(n,3);
      float m = fft1024_1.read(232); //10k Hz
//      float m = fft1024_1.read(279); //12k Hz
//      Serial.println(m);
      if (m >0.001){
        Serial.println(m, 3);
        Serial.println("detected");
      }
    }
  }

}
