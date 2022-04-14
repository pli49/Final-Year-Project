
int f_0 = 1000; // hz
int f_1 = 2000; // hz
float T = 1000; // ms

static double f_dt = f_0;
static double dt;
double chirpRate = (f_1 - f_0)/(T/1000);

double interruptRate = 1; // us

float n = 1000*(T/interruptRate);
double freqStep = (f_1 - f_0)/n;
int AUDIO_OUT_PIN = 3;

IntervalTimer increaseFreqInterrupt;

void 
setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
}

char incomingByte;

void 
loop() 
{
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    if (incomingByte == 'a') {
      Serial.println(freqStep);
      Serial.print("\n");
      playChirp();
    }
  }
}

void
playChirp()
{
  increaseFreqInterrupt.begin(increaseFreq, interruptRate);
  analogWriteFrequency(AUDIO_OUT_PIN, f_0);
  analogWrite(AUDIO_OUT_PIN,128);
  interrupts();
  delay(T);
  noInterrupts();
  increaseFreqInterrupt.end();
  analogWrite(AUDIO_OUT_PIN,0);
  f_dt = f_0;
}

void
increaseFreq()
{
  f_dt = f_dt + freqStep;
  analogWriteFrequency(AUDIO_OUT_PIN, f_dt);
}
