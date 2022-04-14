hardware connection:
//3.3V -> 3V
//GND -> GND
//21 -> BCLK
//20 -> LRCL
//8 -> DOUT
//GND -> SEL

File name strating with audio was some primary testing files.

File name strating with I2S are the files that for fft testing and applied highpass filter and/or amplifier to the signal.

  //try some amplifier values 30cm away with ipad speaker pointing to the mic
  //500 gain -> 0.278 amplitude of the detected 10k Hz sound
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

File named Queue_raw_int_to_teensy generated the text file with raw mic output data.

I heard from somebody else that PLATFORM.io is much better then arduino IDE 3 days before the project hand in time and havent been able to try it out. 


 