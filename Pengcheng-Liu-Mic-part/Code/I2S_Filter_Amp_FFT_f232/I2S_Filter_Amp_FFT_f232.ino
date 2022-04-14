/* SPH0645 MEMS Microphone Test (Adafruit product #3421)
 *
 * Forum thread with connection details and other info:
 * https://forum.pjrc.com/threads/60599?p=238070&viewfull=1#post238070
 */


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

  filter1.frequency(200); 
  
  // filter out DC & extremely low frequencies


  //try some values 30cm ipad speaker pointing to the mic
  //500 -> 0.278
  //400 -> 0.213
  //300 -> 0.166
  //200 -> 0.084
  //100 -> 0.046
  //50  -> 0.027
  //25  -> 0.014
  //10  -> 0.005
  //5   -> 0.003
  //2   -> 0.001
  //1.5 -> 0
  //1   -> 0
  amp1.gain(10); 
}

void loop() {
  if (fft1024_1.available()) {
    // each time new FFT data is available
    // print column 232 which correspons to the required frequancy
    Serial.print("FFT - time"); 
    Serial.print(millis());
    Serial.print("  ");

    float n = fft1024_1.read(232);
    if (n >= 0.001) {
      Serial.print(n, 3);
    } else {
      Serial.print("--"); // don't print "0.000"
    }
    Serial.println();
  }
}
