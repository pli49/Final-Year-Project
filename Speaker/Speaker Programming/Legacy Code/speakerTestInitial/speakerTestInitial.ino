// Author: Laurence Prins
// Date: 13/05/2021
// Description: Initial testing of speaker driven from MCU

const byte numChars = 32;
char receivedChars[numChars];   // an array to store the received data
char tempChars[numChars]; 
char messageFromPC[numChars] = {0};

int toneFrequency = 1000; // Tone Frequency, default 1kHz
int toneLength = 1000; // tone duration, defaul 1 second
int pulses = 0; // Number of pulses, default 0

boolean newData = false;

int dataNumber = 0;             // new for this version

static int AUDIO_OUTPUT_1 = 3;

void setup() {
  // put your setup code here, to run once
  Serial.begin(9600);
}

void loop() {
  recvWithStartEndMarkers();
  if (newData == true) {
      strcpy(tempChars, receivedChars);
          // this temporary copy is necessary to protect the original data
          //   because strtok() used in parseData() replaces the commas with \0
      parseData();
      showParsedData();
      newData = false;
      generateBasicTone(toneFrequency, toneLength);
  }
}

void 
generatePulsedTone(int toneFrequency, int toneLength, int noPulses)
{
  for (int i = 0; i <= noPulses; i++) {
    generateBasicTone(toneFrequency, toneLength);
    delay(toneLength);
  }
}

void 
generateBasicTone(int toneFrequency, int toneLength) 
{
    tone(AUDIO_OUTPUT_1, toneFrequency);
    delay(toneLength);
    noTone(AUDIO_OUTPUT_1);
 
}

// Original code for reading from serial developed by Robin2
// source: https://forum.arduino.cc/t/serial-input-basics-updated/382007 
// Edited for use with the speaker code
void parseData() {      // split the data into its parts

    char * strtokIndx; // this is used by strtok() as an index

    strtokIndx = strtok(tempChars,","); // first index
    toneFrequency = atoi(strtokIndx); // convert to an integer
 
    strtokIndx = strtok(NULL, ","); // secondi index
    toneLength = atoi(strtokIndx); // convert to an integer

    strtokIndx = strtok(NULL, ","); // third index
    pulses = atoi(strtokIndx); // convert to an an integer
}

void recvWithStartEndMarkers() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '[';
    char endMarker = ']';
    char rc;
 
    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();

        if (recvInProgress == true) {
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }

        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
}

void showNewData() {
    if (newData == true) {
        Serial.print("This just in ... ");
        Serial.print(sizeof(receivedChars));
        newData = false;
    }
}

void showParsedData() {
    Serial.print("Frequency ");
    Serial.println(toneFrequency);
    Serial.print("Duration ");
    Serial.println(toneLength);
    Serial.print("Number of Pulses ");
    Serial.println(pulses);
}
