//Teensy -> SPH0645
//3.3V -> 3V
//GND -> GND
//21 -> BCLK
//20 -> LRCL
//8 -> DOUT
//GND -> SEL
//


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

//global variables for high pass filter
int sensorPin = 0;    //pin number to use the ADC
int sensorValue = 0;  //initialization of sensor variable, equivalent to EMA Y
float EMA_a = 0.3;    //initialization of EMA alpha
int EMA_S = 0;        //initialization of EMA S
int highpass = 0;



void setup() {
Serial.begin(115200);
  // Audio connections require memory to work.  For more
  // detailed information, see the MemoryAndCpuUsage example
  AudioMemory(20);

  //
//  EMA_S = rms1; 

}

void loop() {
  sensorValue = rms1;              //read the sensor value using ADC
  EMA_S = (EMA_a*sensorValue) + ((1-EMA_a)*EMA_S);  //run the EMA
  highpass = sensorValue - EMA_S;                   //calculate the high-pass signal
 
  Serial.println(highpass);
   
  delay(20);                                //20ms delay
