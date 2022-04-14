// Author: Laurence Prins
// Date: 5/08/2021
// Description: Code for playing square waveforms

// Square wave chirp setup

// Define constants
#define SQUARE_CHIRP_INTERRUPT_PERIOD 10  // rate at which to increase the square wave duty cycle [us]

// Initialise variables
static float square_chirp_freq;
static float square_chirp_duty_step; 

IntervalTimer increase_freq_interrupt;

// Square wave code begin

/*
 * Play a square waveform.
 * Inputs:  waveform* wave_to_play = pointer to the waveform object to play
 */
void
playSquareWaveform(uint32_t waveform_initial_frequency, uint32_t waveform_final_frequency, uint32_t waveform_time, uint32_t waveform_pulses)
{
  if (waveform_initial_frequency == waveform_final_frequency) {
    for (uint32_t i = 0; i < waveform_pulses; ++i) {
      tone(AUDIO_OUT_PIN, waveform_initial_frequency);
      delay(waveform_time);
      noTone(AUDIO_OUT_PIN);
      if (i >= waveform_pulses) {
        delay(waveform_time);
      }
    }
  } else {
    calcFreqStep(waveform_initial_frequency, waveform_final_frequency, waveform_time);
    for (uint32_t i = 0; i < waveform_pulses; ++i) {
      playSquareChirp(waveform_initial_frequency, waveform_final_frequency, waveform_time);
    }
  }
}

/*
 * Play a square chirp waveform.
 * Inputs:  waveform* wave_to_play = pointer to the waveform object to play
 */
void
playSquareChirp(uint32_t waveform_initial_frequency, uint32_t waveform_final_frequency, uint32_t period)
{
  analogWriteFrequency(AUDIO_OUT_PIN, waveform_initial_frequency);
  analogWrite(AUDIO_OUT_PIN,128);
  increase_freq_interrupt.begin(increaseSquareFreq, SQUARE_CHIRP_INTERRUPT_PERIOD);
  interrupts();
  delay(period);
  noInterrupts();
  increase_freq_interrupt.end();
  analogWrite(AUDIO_OUT_PIN,0);
  square_chirp_freq = waveform_initial_frequency;
}

/*
 * Calculate the rate at which the square chirp increases the frequency.
 * Inputs:  uint32_t waveform_initial_frequency = initial waveform frequency [Hz]
 *          uint32_t waveform_final_frequency = final waveform frequency [Hz]
 *          uint32_t waveform_time = waveform length [ms]
 */
void
calcFreqStep(uint32_t waveform_initial_frequency,uint32_t waveform_final_frequency,uint32_t waveform_time)
{
  float number_steps = 1000*(waveform_time/SQUARE_CHIRP_INTERRUPT_PERIOD);
  square_chirp_duty_step = (waveform_final_frequency - waveform_initial_frequency)/number_steps;
}

/*
 * Increase the square wave frequency. Used by the IntervalTimer increase_freq_interrupt
 */
void
increaseSquareFreq()
{
  square_chirp_freq = square_chirp_freq + square_chirp_duty_step;
  analogWriteFrequency(AUDIO_OUT_PIN, square_chirp_freq);
}
