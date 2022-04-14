// Author: Laurence Prins
// Date:  25/06/2021
// Description: Processing data code
// Functions are: n = new/create waveform, r = remove/delete waveform, e = edit waveform, d = display waveform with a = all waveforms, p = play waveform, l = loop waveform, c = chain waveforms, cl = chain/loop waveforms

void
processData() // This is a big ugly function for doing each of the listed functions
{
  getFunction();
  // create a new waveform in the next available list node, c(freq, waveperiod, #pulses, waveshape)
  if (strcmp(currFunction, "n") == 0) { 
    int waveFreq;
    int waveTime;
    int waveformPulses;
    char waveShape[numChars] = {0};
    
    char* strtokIndx = strtok(functionInputs, ",");
    if (strtokIndx == NULL) {
      Serial.print("Create waveform must be of the form: c(waveFreq, waveTime, #pulses, waveshape)\n");
      return;
    } else {
      waveFreq = atoi(strtokIndx); // extract frequency
    }

    strtokIndx = strtok(NULL, ",");
    if (strtokIndx == NULL) {
      Serial.print("Create waveform must be of the form: c(waveFreq, waveTime, #pulses, waveshape)\n");
      return;
    } else {
      waveTime = atoi(strtokIndx); // extract wave time
    }

    strtokIndx = strtok(NULL, ",");
    if (strtokIndx == NULL) {
      Serial.print("Create waveform must be of the form: c(waveFreq, waveTime, #pulses, waveshape)\n");
      return;
    } else {
      waveformPulses = atoi(strtokIndx); // extract number of pulses
    }

    strtokIndx = strtok(NULL, ",");
    if (strtokIndx == NULL) {
      Serial.print("Create waveform must be of the form: c(waveFreq, waveTime, #pulses, waveshape)\n");
      return;
    } else {
      strcpy(waveShape, strtokIndx); // extract wave shape
    }    
    createNewWaveform(currIdentifier, waveFreq, waveTime, waveformPulses, *waveShape);
    ++currIdentifier;
  }
  // display the waveform with the given identifier, if given a will display all waveforms. d(i/a) i = identifier
  else if (strcmp(currFunction, "d") == 0) { 
    if (strcmp(functionInputs, "a") == 0) {
      displayWaveforms();
    } else {  
      char* strtokIndx = strtok(functionInputs, ",");
      int waveIdentifier = atoi(strtokIndx);
      displayWaveform(waveIdentifier);
    }
  }
  // remove the waveform with the given identifier, if given a will delete all waveforms. r(i/a) i = identifier
  else if (strcmp(currFunction, "r") == 0) { 
    if (strcmp(functionInputs, "a") == 0) {
      deleteAllWaveforms();
      currIdentifier = 0;
    } else {
      char* strtokIndx = strtok(functionInputs, ",");
      int waveIdentifier = atoi(strtokIndx);
      deleteWaveform(waveIdentifier);
    }
  }
  
  // loop the selected waveform until a new instruction is issued.
  else if (strcmp(currFunction, "l") == 0) { 
    char* strtokIndx = strtok(functionInputs, ",");
    int waveIdentifier = atoi(strtokIndx);
    waveform* waveToPlay = searchFor(waveIdentifier);
    if (waveToPlay == NULL) {
      Serial.print("Waveform does not exist\n");
    } else {
      loopWaveform(waveToPlay);
    }
  }
  
  // plays the selected waveform. p(wave).
  else if (strcmp(currFunction, "p") == 0) { 
    char* strtokIndx = strtok(functionInputs, ",");
    int waveIdentifier = atoi(strtokIndx);
    waveform* waveToPlay = searchFor(waveIdentifier);
    if (waveToPlay == NULL) {
      Serial.print("Waveform does not exist\n");
    } else {
      playWaveform(waveToPlay);
    }
  }

  // chain together the selected waveforms with a delay between them. c(i,d) i = identifier, d = delay.
  else if (strcmp(currFunction, "c") == 0) { 
    char* strtokIndx = strtok(functionInputs, ",");
    int waveIdentifier;
    int chainDelay;
    while (strtokIndx != NULL) {
      waveIdentifier = atoi(strtokIndx);
      waveform* waveToPlay = searchFor(waveIdentifier);
      if (waveToPlay == NULL) {
        Serial.print("Waveform does not exist\n");
      } else {
        playWaveform(waveToPlay);
      }
      
      strtokIndx = strtok(NULL, ",");
      if (strtokIndx == NULL) {
        return;
      } else {
        chainDelay = atoi(strtokIndx); // extract delay
        delay(chainDelay); // wait specified delay
        strtokIndx = strtok(NULL, ",");
      }
    }
  }
  
  // edit the waveform in the given identifier. e(i, property, newvalue) i = identifier. properties are: "freq", "time", "pulses", "shape".
  else if (strcmp(currFunction, "e") == 0) { 
    char* strtokIndx = strtok(functionInputs, ",");
    int identifier = atoi(strtokIndx);
    waveform* waveToEdit = searchFor(identifier);
    if (waveToEdit == NULL) {
        Serial.print("Waveform does not exist\n");
    } else {
      strtokIndx = strtok(NULL, ",");
      while (strtokIndx != NULL) {
        if (strcmp(strtokIndx, "freq") == 0) {
          strtokIndx = strtok(NULL, ",");
          int newFreq = atoi(strtokIndx);
          waveToEdit->waveformFrequency = newFreq;
        } else if (strcmp(strtokIndx, "time") == 0) {
          strtokIndx = strtok(NULL, ",");
          int newTime = atoi(strtokIndx);
          waveToEdit->waveformTime = newTime;
        } else if (strcmp(strtokIndx, "pulses") == 0) {
          strtokIndx = strtok(NULL, ",");
          int newPulses = atoi(strtokIndx);
          waveToEdit->waveformPulses = newPulses;
        } else if (strcmp(strtokIndx, "shape") == 0) {
          char waveShape[numChars] = {0};
          strtokIndx = strtok(NULL, ",");
          strcpy(waveShape, strtokIndx);
          waveToEdit->waveShape = *waveShape;
        } else {
          Serial.print("Invalid waveform property\n");
        }
        strtokIndx = strtok(NULL, ",");
      }
    }
  }
  else {
    Serial.println("please enter a valid command\n");
  }
}

void
getFunction()
{
  // Get the function inputs from the serial input
  char tempChars2[numChars];
  strcpy(tempChars2, tempChars);
  strtok(tempChars2, ")");
  char* functionInput = strstr(tempChars2, "(");
  strcpy(functionInputs, functionInput + 1);

  // Get the function from the serial input
  char * strtokIndx = strtok(tempChars, "(");
  strcpy(currFunction, strtokIndx);
}
