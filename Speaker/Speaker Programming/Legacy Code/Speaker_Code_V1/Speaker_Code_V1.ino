// Author: Laurence Prins
// Date: 25/06/2021
// Description: General code for speaker

// Serial setup
const byte numChars = 32;
char receivedChars[numChars];
char tempChars[numChars];      
char functionInputs[numChars] = {0};  
char currFunction[1] = {0};
boolean newData = false;

// Waveform setup
struct waveform
{
  int waveformIdentifier; // unique identifier for given waveform
  int waveformFrequency; // frequency in Hz
  int waveformTime; // time in ms
  int waveformPulses; // 
  char waveShape; // p = square, s = sine, t = triangle (Add more later)
  struct waveform *next;
};

struct waveform *head = NULL;
struct waveform *current = NULL;

int currIdentifier = 0;

// initial waveform
static int initialFreq = 1000; // 1kHz
static int initialTime = 5000; // 1ms
static int initialPulses = 1; // 1 pulse
static char initialShape = 'p'; // square wave with duty of 50\%

// Sinusoidal PWM
int counterMax = 1000; // Counter counts to 10 and then increases sinusoidal PWM duty
int PWMResolution = 256; // 2^8
float interruptPeriod = 1; // [us] float for extra accuracy.

static double stepSize; // Step size, determines frequency
static double count; // Current counter value
static uint8_t sineIndex; // Sine index for the sine table

IntervalTimer sinusoidalPWMInterruptTimer;
IntervalTimer stopSinusoidalPWMInterruptTimer;

// Hardware
int AUDIO_OUT_PIN = 3;

void 
setup() 
{
  Serial.begin(9600);
  createInitialWaveform();
  ++currIdentifier;
}

void 
loop() 
{
  recvWithStartEndMarkers();
  if (newData == true) {
    strcpy(tempChars, receivedChars);
        // this temporary copy is necessary to protect the original data
        //  because strtok() used in parseData() replaces the commas with \0
    processData(); 
    newData = false;
  }
}

void
loopWaveform(waveform* waveToPlay)
{
  while(newData == false) {
    playWaveform(waveToPlay);
    recvWithStartEndMarkers();
  }
}

void
playWaveform(waveform* waveToPlay)
{
  Serial.print("Now Playing: ");
  Serial.println(waveToPlay->waveformIdentifier);
  
  char waveShape = waveToPlay->waveShape;
  
  if (waveShape == 'p') {
    playSquareWaveform(waveToPlay);
  } 
  else if (waveShape == 's') {
    playSineWaveform(waveToPlay);
  } 
  else {
    return;
  }
}

void
playChirp(waveform* waveToPlay)
{
  
}

void
playSineWaveform(waveform* waveToPlay)
{
  int freq = waveToPlay->waveformFrequency;
  int period = waveToPlay->waveformTime;
  int pulses = waveToPlay->waveformPulses;
  calcStep(freq);
  analogWriteFrequency(AUDIO_OUT_PIN, freq*PWMResolution); //PWMResolution*freq);
  for (int i = 0; i < pulses; ++i) {
    interrupts(); // Enable interrupts
    stopSinusoidalPWMInterruptTimer.begin(stopSinusoidalPWM, period*1000); // Start the stop timer
    sinusoidalPWMInterruptTimer.begin(increasePWM, interruptPeriod); // Start the interrupt timer
    delay(period);
    noInterrupts(); // Disable interrupts
    count = 0; // Reset count
    sineIndex = 0; // Reset the table index
    analogWrite(AUDIO_OUT_PIN, 0); // Turn off pin
    
    if (i >= pulses) {
      delay(period);
    }
  }
}

void
playSquareWaveform(waveform* waveToPlay)
{
  int freq = waveToPlay->waveformFrequency;
  int period = waveToPlay->waveformTime;
  int pulses = waveToPlay->waveformPulses;
  for (int i = 0; i < pulses; ++i) {
    tone(AUDIO_OUT_PIN, freq);
    delay(period);
    noTone(AUDIO_OUT_PIN);
    
    if (i >= pulses) {
      delay(period);
    }
  }
}
