// Author: Laurence Prins
// Date: 25/06/2021
// Description: General code for speaker

#include "Transmitter_Code.h"

// Serial setup
#define NUM_CHARS_FUNCTION  8   // Number of characters to allocate for the function names
#define NUM_CHARS_INPUTS    60  // Number of characters to allocate for the function inputs

// Initial waveform setup for slot 0

static int initial_initial_freq = 1000; 
static int initial_final_freq = 3000; // 1kHz to 1kHz
static int initial_waveform_time = 250; // 1ms
static char initial_wave_shape = 's'; // square wave with duty of 50\%

// Serial setup
const byte num_chars = NUM_CHARS_FUNCTION + NUM_CHARS_INPUTS;
char received_chars[num_chars];
char temp_chars[num_chars];      
boolean new_data = false;

// Transmitter setup
TX default_transmitter;
uint8_t default_output_pin = 5;
uint32_t default_wait_time = 5000; // Wait 5 seconds AFTER transmitting
uint16_t default_waveform = 0;

// Hardware 
int AUDIO_OUT_PIN = 3;

void 
setup() 
{
  Serial.begin(9600);
  createNewWaveform(initial_initial_freq, initial_final_freq, initial_waveform_time, initial_wave_shape);
  txConfig(&default_transmitter, searchFor(default_waveform), default_output_pin, default_wait_time);
}

void 
loop() 
{
  recvWithStartEndMarkers();
  if (new_data == true) {
    strcpy(temp_chars, received_chars);
    new_data = false;
    processData(temp_chars); 
  }
}
