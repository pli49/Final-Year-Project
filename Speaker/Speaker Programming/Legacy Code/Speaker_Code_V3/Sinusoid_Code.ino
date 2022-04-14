// Author: Laurence Prins
// Date: 15/07/2021
// Description: Code for playing sinusoid waveforms

// Sinusoidal PWM setup

// Define constants
#define COUNTER_MAX         100 // Counter counts to 10 and then increases sinusoidal PWM duty
#define SINE_TABLE_LENGTH   256 // Length of the sine table
#define INTERRUPT_PERIOD    5  // Sinusoidal PWM interrupt period [us]

// Initialise variables
uint8_t sine_table_index;

static double sine_step_size; // Step size, determines frequency
static double sine_step_step_size; // Step step size, for adding to sine_step_size for linear FM chirps

static float count; // Current counter value
static uint8_t sine_index; // Sine index for the sine table

static bool currently_playing = false;

IntervalTimer sine_pwm_interrupt_timer;
IntervalTimer stop_sine_pwm_interrupt_timer;

// 8 bit sine table
uint8_t sine_table_8bit[]=
{
  128, 131, 134, 137, 140, 143, 146, 149, 152, 156, 159, 162, 165, 168, 171, 174,
  176, 179, 182, 185, 188, 191, 193, 196, 199, 201, 204, 206, 209, 211, 213, 216,
  218, 220, 222, 224, 226, 228, 230, 232, 234, 236, 237, 239, 240, 242, 243, 245,
  246, 247, 248, 249, 250, 251, 252, 252, 253, 254, 254, 255, 255, 255, 255, 255,
  255, 255, 255, 255, 255, 255, 254, 254, 253, 252, 252, 251, 250, 249, 248, 247,
  246, 245, 243, 242, 240, 239, 237, 236, 234, 232, 230, 228, 226, 224, 222, 220,
  218, 216, 213, 211, 209, 206, 204, 201, 199, 196, 193, 191, 188, 185, 182, 179,
  176, 174, 171, 168, 165, 162, 159, 156, 152, 149, 146, 143, 140, 137, 134, 131,
  127, 124, 121, 118, 115, 112, 109, 106, 103, 99, 96, 93, 90, 87, 84, 81,
  79, 76, 73, 70, 67, 64, 62, 59, 56, 54, 51, 49, 46, 44, 42, 39,
  37, 35, 33, 31, 29, 27, 25, 23, 21, 19, 18, 16, 15, 13, 12, 10,
  9, 8, 7, 6, 5, 4, 3, 3, 2, 1, 1, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 1, 1, 2, 3, 3, 4, 5, 6, 7, 8,
  9, 10, 12, 13, 15, 16, 18, 19, 21, 23, 25, 27, 29, 31, 33, 35,
  37, 39, 42, 44, 46, 49, 51, 54, 56, 59, 62, 64, 67, 70, 73, 76,
  79, 81, 84, 87, 90, 93, 96, 99, 103, 106, 109, 112, 115, 118, 121, 124
};

// Sinusoidal PWM begin

/*
 * Play the selected waveform through the audio out pin. 
 * starts the interrupt timer and stop interrupt timer and determines if initial freq = final freq. Calculates step size and plays the 
 * waveform.
 * 
 * Inputs:  uint32_t waveform_initial_frequency = initial frequency
 *          uint32_t waveform_final_frequency = final frequency
 *          uint32_t waveform_time = period of waveform
 */
void
playSineWaveform(uint32_t waveform_initial_frequency, uint32_t waveform_final_frequency, uint32_t waveform_time)
{
  if (currently_playing == false) {
    sine_step_size = calcStep(waveform_initial_frequency);
    analogWriteFrequency(AUDIO_OUT_PIN, waveform_final_frequency*SINE_TABLE_LENGTH); //SINE_TABLE_LENGTH*freq);
  
    if (waveform_initial_frequency == waveform_final_frequency) {
      sine_step_step_size = 0;
    } else {
      float sine_step_initial = calcStep(waveform_initial_frequency);
      float sine_step_final = calcStep(waveform_final_frequency);
      Serial.println(sine_step_initial); // Test
      Serial.println(sine_step_final);
      sine_step_step_size = calcStepStep(waveform_initial_frequency, waveform_final_frequency, waveform_time);
      Serial.println(sine_step_step_size);
    } 
      currently_playing = true;
      sine_pwm_interrupt_timer.begin(increasePWM, INTERRUPT_PERIOD); // Start the interrupt timer
      stop_sine_pwm_interrupt_timer.begin(stopSinusoidalPWM, waveform_time*1000); // Start the stop timer
      interrupts(); // Enable interrupts
      delay(waveform_time);
      Serial.println(sine_step_size);
  } else {
    Serial.print("Already playing\n");
  }
}

/*
 * Calculates the rate at which the sinusoidal pwm code increases the step size to control the frequency of the output sine wave.
 * Inputs:  uint32_t waveform_initial_frequency = initial waveform frequency [Hz]
 *          uint32_t waveform_final_frequency = final waveform frequency [Hz]
 *          uint32_t waveform_time = waveform length [ms]
 * Outputs: double step_step_size = how much to increase step size at each interrupt call
 */
double
calcStepStep(uint32_t waveform_initial_frequency, uint32_t waveform_final_frequency, uint32_t waveform_time) 
{
  float number_steps = 1000*(waveform_time/INTERRUPT_PERIOD); // Calculate number of discrete steps between initial and final freq
  double freq_step_initial = calcStep(waveform_initial_frequency); // Calculate the step required for initial freq
  double freq_step_final = calcStep(waveform_final_frequency); // Calculate the step required for final freq
  double step_step_size = (freq_step_final - freq_step_initial)/number_steps; // Calculate the increase in step per interrupt for a linear FM chirp
  return step_step_size;
}

/*
 * Calculates the rate at which the sinusoidal pwm code increases the PWM duty to control the frequency of the frequency of the output sine wave.
 * Inputs:  uint32_t freq = frequency which to use to calculate the step size
 * Outputs: double step_size = rate at which to increase the PWM duty
 */
double
calcStep(uint32_t freq) {
  double step_size = (freq*COUNTER_MAX)*(SINE_TABLE_LENGTH)*(INTERRUPT_PERIOD); // Calculate step for selected frequency
  step_size = (float)step_size*1e-6;
  return step_size;
}

/*
 * Increase the PWM duty cycle. Used by the IntervalTimer sine_pwm_interrupt_timer
 */
void 
increasePWM() 
{
  count = count + sine_step_size;
  sine_step_size += sine_step_step_size;
  for (; count >= COUNTER_MAX; count = count-COUNTER_MAX) {
    sine_table_index = sine_table_8bit[++sine_index];
  }
  if (sine_index > (SINE_TABLE_LENGTH)) {
    sine_index = 0;
  }
  analogWrite(AUDIO_OUT_PIN, sine_table_index);
}

/*
 * Stop both the sine_pwm_interrupt_timer and the stop_sine_pwm_interrupt_timer. Used to get more accurate timers.
 */
void
stopSinusoidalPWM()
{
  sine_pwm_interrupt_timer.end();
  count = 0; // Reset count
  sine_index = 0; // Reset the table index
  sine_table_index = 0;
  analogWrite(AUDIO_OUT_PIN, 0); // Turn off pin
  currently_playing = false;
  stop_sine_pwm_interrupt_timer.end();  
  Serial.println(sine_step_size);
  Serial.print("Stopping\n");
  //noInterrupts();
}
