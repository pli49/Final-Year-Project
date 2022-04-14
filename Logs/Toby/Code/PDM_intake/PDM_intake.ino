
#define PDM_CLK 23
#define PDM_DATA 22
#define PDM_SELECT 21

IntervalTimer myTimer;

void setup() {
  pinMode(PDM_CLK, OUTPUT);
  pinMode(PDM_SELECT, OUTPUT);
  pinMode(PDM_DATA, INPUT);
  myTimer.begin(clockToggle, 1);
  Serial.begin(115200);
  digitalWrite(PDM_SELECT, LOW);
}

uint8_t toggleBit = 0;
long long dataStorage = 0;
uint8_t currentNumOfBits = 0;

void loop() {
    if((dataStorage>>63) && 1){
        currentNumOfBits--;
      }
    if(digitalReadFast(PDM_DATA)){
      dataStorage = (dataStorage << 1) | 1;
      currentNumOfBits++;
    }

  Serial.println((currentNumOfBits*100)/64);
  delayMicroseconds(100);
}


void clockToggle(){
  toggleBit = !toggleBit;
  digitalWriteFast(PDM_CLK, toggleBit);
}
