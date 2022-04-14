// Timing Test

IntervalTimer initialTimer;
IntervalTimer sinusoidalPWMInterruptTimer;
IntervalTimer sinusoidalPWMStopTimer;

void
stopPWMInterrupt()
{
  sinusoidalPWMInterruptTimer.end();
  sinusoidalPWMStopTimer.end();
  Serial.print("Stop");
}

void
PWMInterrupt()
{
  Serial.print("Trigger\n");
}

void setup() {
  // put your setup code here, to run once:
  Serial.print("Start\n");
  noInterrupts();
  sinusoidalPWMInterruptTimer.begin(PWMInterrupt,10000000);
  sinusoidalPWMStopTimer.begin(stopPWMInterrupt,20000000);
  interrupts();
}

void loop() {
  // put your main code here, to run repeatedly:
  
}
