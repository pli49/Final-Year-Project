#include <FIR.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

FIR<float, 35> fir_lp;

// GUItool: begin automatically generated code
AudioInputI2S            i2s2;           //xy=373,144
AudioAnalyzeRMS          rms1;           //xy=789,282
AudioConnection          patchCord1(i2s2, 0, rms1, 0);
// GUItool: end automatically generated code

//Low pass
float coef_lp[35] = {
  357,
  1023,
  1359,
  1360,
  590,
  -390,
  -1003,
  -666,
  370,
  1249,
  1023,
  -393,
  -1947,
  -2004,
  410,
  4697,
  8812,
  10507,
  8812,
  4697,
  410,
  -2004,
  -1947,
  -393,
  1023,
  1249,
  370,
  -666,
  -1003,
  -390,
  590,
  1360,
  1359,
  1023,
  357
};
void setup() {
Serial.begin(115200);
  // Audio connections require memory to work.  For more
  // detailed information, see the MemoryAndCpuUsage example
  AudioMemory(20);
//
//    // For a moving average we want all of the coefficients to be unity.
//  float coef[128] = { 1., 1., 1., 1., 1., 1., 1., 1.,
//  1., 1., 1., 1., 1., 1., 1., 1.,
//  1., 1., 1., 1., 1., 1., 1., 1.,
//  1., 1., 1., 1., 1., 1., 1., 1.,
//  1., 1., 1., 1., 1., 1., 1., 1.,
//  1., 1., 1., 1., 1., 1., 1., 1.,
//  1., 1., 1., 1., 1., 1., 1., 1.,
//  1., 1., 1., 1., 1., 1., 1., 1.,
//  1., 1., 1., 1., 1., 1., 1., 1.,
//  1., 1., 1., 1., 1., 1., 1., 1.,
//  1., 1., 1., 1., 1., 1., 1., 1.,
//  1., 1., 1., 1., 1., 1., 1., 1.,
//  1., 1., 1., 1., 1., 1., 1., 1.,
//  1., 1., 1., 1., 1., 1., 1., 1.,
//  1., 1., 1., 1., 1., 1., 1., 1.,
//  1., 1., 1., 1., 1., 1., 1., 1.};
//
//  // Set the coefficients
//  fir.setFilterCoeffs(coef);
fir_lp.setFilterCoeffs(coef_lp);
//
//  Serial.print("Gain set: ");
//  Serial.println(fir.getGain());

  Serial.print("Low Pass Filter Gain: ");
  Serial.println(fir_lp.getGain());



}

int32_t counter = 0;
float data[5000];


void loop() {
  
  if(counter >= 5000){
    counter = 0;
    for(int32_t i = 0; i < sizeof(data); i++){
      Serial.print(data[i]);

    Serial.print(",400,600");
    Serial.println();
    }
    
  }
  else{
  data[counter] = fir_lp.processReading(10000*rms1.read());
  counter++;}
delayMicroseconds(100);
}
