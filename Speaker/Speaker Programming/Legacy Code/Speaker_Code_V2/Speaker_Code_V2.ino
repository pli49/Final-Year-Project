// Author: Laurence Prins
// Date: 25/06/2021
// Description: General code for speaker

// Serial setup
#define NUM_CHARS_FUNCTION  8   // Number of characters to allocate for the function names
#define NUM_CHARS_INPUTS    60  // Number of characters to allocate for the function inputs

// Initial waveform setup for slot 0

static int initial_initial_freq = 600; 
static int initial_final_freq = 20000; // 1kHz to 1kHz
static int initial_waveform_time = 5000; // 1ms
static int initial_waveform_pulses = 1; // 1 pulse
static char initial_wave_shape = 's'; // square wave with duty of 50\%

// Serial setup
const byte numChars = 32;
char receivedChars[numChars];
char tempChars[numChars];      
boolean newData = false;

// Hardware 
int AUDIO_OUT_PIN = 3;

void 
setup() 
{
  Serial.begin(9600);
  createNewWaveform(initial_initial_freq, initial_final_freq, initial_waveform_time, initial_waveform_pulses, initial_wave_shape);
}

void 
loop() 
{
//  serialFunction();
  recvWithStartEndMarkers();
  if (newData == true) {
    strcpy(tempChars, receivedChars);
        // this temporary copy is necessary to protect the original data
        //  because strtok() used in parseData() replaces the commas with \0
    processData(tempChars); 
    newData = false;
  }
}

void
serialFunction(void)
{
  if (checkSerial()) {
    char* chars_to_process = readSerialInput();
    strcpy(tempChars, chars_to_process);
    processData(tempChars);
    free(chars_to_process);
  }
}
