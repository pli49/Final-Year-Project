float x=0;
float y=0;
const float pi=3.14;
int z=0;
float v=0;
int w=0;

static int AUDIO_OUTPUT_2 = 6;
static int AUDIO_OUTPUT_1 = 3;
int toneLength = 20; // 1 second
int toneFrequency = 1000; // 1kHz


int calculateSinusoidalPwmPulse(int t, int f) 
{
  const float pi=3.14;
  float w = 2*pi*f; // making deg in radians
  float y=sin(w*t);
  int z = y*127; // duty
  if (z < 0) {
    z = -z;
  }
  return (z);
}

void generateSinusoidalPwmPulse(int pin, int f, int pulses)
{
  int T = 1/f;
  int pulse_width;
  
  for (int nIt = 0; nIt < pulses; nIt++) {
    for (int t = 0; t <= T; t = t*(1 + T))
    {
      pulse_width = calculateSinusoidalPwmPulse(t, f); 
      analogWrite(pin, pulse_width);
      delay(T/f);
    }
  }
}

void setup() {
  Serial.begin(9600);
}

  // the loop function runs over and over again forever
void loop() {  
  if(Serial.available()){
    char input = Serial.read();
    Serial.println(input);
    if(input == 'S'){
      for (int i = 0; i <= 10; i++) {   
        tone(AUDIO_OUTPUT_1, toneFrequency);
        delay(toneLength);
        noTone(AUDIO_OUTPUT_1);     // manually stop it
        delay(toneLength);
      } 
    } else if (input == 'P') {
        generateSinusoidalPwmPulse(AUDIO_OUTPUT_1, toneFrequency, 10);
      }
    }
  }
