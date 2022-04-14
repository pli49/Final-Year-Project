// Author: Laurence Prins
// Date: 25/07/2021
// Description: Code for playing/looping selected waveforms

/*
 * Loop the selected waveform through the audio out pin until told to stop.
 * 
 * Inputs: waveform* wave_to_play = waveform selected to loop
 */
void
loopWaveform(waveform* wave_to_play)
{
  recvWithStartEndMarkers();
  while(new_data == false) {
    playWaveform(wave_to_play);
    recvWithStartEndMarkers();
  }
}

/*
 * Play the selected waveform through the audio out pin.
 * 
 * Inputs: waveform* wave_to_play = waveform selected to play
 */
void
playWaveform(waveform* wave_to_play)
{
  Serial.print("Now Playing: ");
  Serial.println(getWaveformIdentifier(wave_to_play));
  
  char wave_shape = getWaveShape(wave_to_play);
  uint32_t waveform_initial_frequency = getWaveformInitialFrequency(wave_to_play);
  uint32_t waveform_final_frequency = getWaveformFinalFrequency(wave_to_play);
  uint32_t waveform_time = getWaveformTime(wave_to_play);
  
  if (wave_shape == 'p') {
    playSquareWaveform(waveform_initial_frequency, waveform_final_frequency, waveform_time);
  } 
  else if (wave_shape == 's') {
    playSineWaveform(waveform_initial_frequency, waveform_final_frequency, waveform_time);
  } 
  else {
    Serial.print("Wave shapes are: s for sine and p for square\n");
    return;
  }
}
