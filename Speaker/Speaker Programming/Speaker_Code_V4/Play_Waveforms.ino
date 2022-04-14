// Author: Laurence Prins
// Date: 25/07/2021
// Description: Code for playing/looping audio tones.

/*
 * Loop the selected waveform through the audio out pin until told to stop.
 * 
 * Inputs: waveform* wave_to_play = waveform selected to loop
 */
void
loopWaveform(waveform* wave_to_play)
{
  if (wave_to_play == NULL) {
    Serial.print("Waveform does not exist\n");
    return;
  }
  Serial.print("Now Looping Waveform: \n");
  Serial.println(getWaveformIdentifier(wave_to_play));
  uint32_t waveform_initial_frequency = getWaveformInitialFrequency(wave_to_play);
  uint32_t waveform_final_frequency = getWaveformFinalFrequency(wave_to_play);
  uint32_t waveform_time = getWaveformTime(wave_to_play);
  char wave_shape = getWaveShape(wave_to_play);
  loopAudioTone(waveform_initial_frequency, waveform_final_frequency, waveform_time, wave_shape);
}

/*
 * Loop the audio tone through the audio output pin until a new instruction is given to
 * the serial input.
 * 
 * Inputs:  uint32_t waveform_intial_frequency = initial frequency [Hz]
 *          uint32_t waveform_final_frequency = final frequency [Hz]
 *          uint32_t waveform_time = length of the waveform [ms]
 *          char wave_shape = shape of the waveform. s = sine, p = square.
 */
void
loopAudioTone(uint32_t waveform_initial_frequency, uint32_t waveform_final_frequency, uint32_t waveform_time, char wave_shape)
{
  if (waveform_time == 0) {
    return;
  }
  if (wave_shape == 'p' || wave_shape == 's')  {
    recvWithStartEndMarkers();
    while(new_data == false) {
      playAudioTone(waveform_initial_frequency, waveform_final_frequency, waveform_time, wave_shape);
      recvWithStartEndMarkers();
    }
  } else {
    Serial.print("Wave shapes are: s for sine and p for square\n");
    return;
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
  if (wave_to_play == NULL) {
    Serial.print("Waveform does not exist\n");
    return;
  }
  Serial.print("Now Playing Waveform: \n");
  Serial.println(getWaveformIdentifier(wave_to_play));

  /*
   * Extract the waveform properties
   */
  uint32_t waveform_initial_frequency = getWaveformInitialFrequency(wave_to_play);
  uint32_t waveform_final_frequency = getWaveformFinalFrequency(wave_to_play);
  uint32_t waveform_time = getWaveformTime(wave_to_play);
  char wave_shape = getWaveShape(wave_to_play);
  /*
   * Send to play audio tone to deal with
   */
  playAudioTone(waveform_initial_frequency, waveform_final_frequency, waveform_time, wave_shape);
}

/*
 * Play a waveform with the specified properties through the audio out pin.
 * 
 * Inputs:  uint32_t waveform_intial_frequency = initial frequency [Hz]
 *          uint32_t waveform_final_frequency = final frequency [Hz]
 *          uint32_t waveform_time = length of the waveform [ms]
 *          char wave_shape = shape of the waveform. s = sine, p = square.
 */
void
playAudioTone(uint32_t waveform_initial_frequency, uint32_t waveform_final_frequency, uint32_t waveform_time, char wave_shape)
{  
  if (waveform_time == 0) {
    return;
  }
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
