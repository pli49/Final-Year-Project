// Author: Laurence Prins
// Date: 25/06/2021
// Description: Processing data code
// Functions are: n = new/create waveform, r = remove/delete waveform, e = edit waveform, d = display waveform with a = all waveforms, p = play waveform, l = loop waveform

// Process code setup
#include "Transmitter_Code.h"

// Process code begin
void
processData(char* chars_to_process)
{
  // Extract function and inputs from the serial input
  char* function_and_inputs = (char*)malloc(NUM_CHARS_FUNCTION*sizeof(char) + NUM_CHARS_INPUTS*sizeof(char) + 1);
  strcpy(function_and_inputs, chars_to_process);
  
  char* function = getFunction(function_and_inputs);
  if (function == NULL) {
    Serial.println("Function and inputs must be of form: function(inputs)");
    return;
  }
  
  char* function_inputs = getInputs(function_and_inputs);
  if (function_inputs == NULL) {
    Serial.println("Function and inputs must be of form: function(inputs)");
    return;
  }
  free(function_and_inputs);  

  // Process the function and inputs

  /*
   * Waveform Processing
   */
  // create a new waveform in the next available list node, c(freq, waveperiod, waveshape)
  if (strcmp(function, "n") == 0) {
     processCreateWaveform(function_inputs);
  }
  // Display the waveform with the given identifier, if given a will display all waveforms. d(i/a) i = identifier
  else if (strcmp(function, "d") == 0) {
    processDisplayWaveform(function_inputs);
  }
  // Remove the waveform with the given identifier, if given a will delete all waveforms. r(i/a) i = identifier
  else if (strcmp(function, "r") == 0) {
    processRemoveWaveform(function_inputs);  
  }
  // Play the selected waveform. p(wave).
  else if (strcmp(function, "p") == 0) {
    processPlayWaveform(function_inputs);
  }
  // Loop the selected waveform until a new instruction is issued.
  else if (strcmp(function, "l") == 0) {
    processLoopWaveform(function_inputs);
  }
  // Edit the waveform with the given identifier. e(i, property, newvalue) i = identifier. properties are: "f0", "f1", "time", "shape".
  else if (strcmp(function, "e") == 0) {
    processEditWaveform(function_inputs);
  }
  /*
   * Transmitter Processing
   */
  else if (strcmp(function, "TxCfg") == 0) {
    processConfigureTx(function_inputs);
  }
  else if (strcmp(function, "TxDisp") == 0) {
    processDisplayTx();
  }
  else if (strcmp(function, "Tx") == 0) {
    processTransmitWaveform();
  }
  /*
   * Other Commands
   */
  else if (strcmp(function, "pt") == 0) {
    processPlayTone(function_inputs);
  }
  else if (strcmp(function, "lt") == 0) {
    processLoopTone(function_inputs);
  }
  /*
   * Invalid command
   */
  else {
    Serial.println("please enter a valid command\n");
  }
  /*
   * Free the function and inputs
   */
  free(function);
  free(function_inputs);
}

// Functions for extracting the inputs to the serial
/*
 * Extract the function from the given input. Searches for the open bracket "(" and returns all characters before it
 * Inputs:  char* input_string = pointer to a string of characters to extract the function from
 * Outputs: char* curr_function = pointer to the function
 */
char*
getFunction(char* input_string)
{
  char temp_chars[strlen(input_string)]; // Initialise a char array
  strcpy(temp_chars, input_string); // Copy the input string into a temporary char array
  char * strtok_indx = strtok(temp_chars, "("); // Find the index of the open bracket
  if (strtok_indx == NULL) {
    return NULL;
  }
  
  char* curr_function = (char*)malloc(NUM_CHARS_FUNCTION*sizeof(char) + 1); // Initialise a char pointer
  strcpy(curr_function, strtok_indx); // Copy the input string function to function
  
  return curr_function;
}

/*
 * Extract the function inputs from the given input. Searches for the open bracket "(" and then the closed bracket ")" and returns all characters between the two
 * Inputs:  char* input_string = pointer to a string of characters to extract the inputs from
 * Outputs: char* function_inputs = pointer to the function inputs
 */
char*
getInputs(char* input_string)
{
  char temp_chars[strlen(input_string)];
  strcpy(temp_chars, input_string); // Copy the input string into a temporary char array
  strtok(temp_chars, ")"); // Find the index of the closing bracket

  char* curr_inputs = strstr(temp_chars, "(");
  if (curr_inputs == NULL) {
    return NULL;
  }
  char* function_inputs = (char*)malloc(NUM_CHARS_INPUTS*sizeof(char) + 1); // Initialise a char pointer

  strcpy(function_inputs, curr_inputs + 1);

  return function_inputs;
}

// Functions for processing commands
/*
 * Create a waveform by extracting the values of uint32_t waveform_initial_frequency, 
 * uint32_t waveform_final_frequency, uint32_t waveform_time
 * and char wave_shape = {0} and calling "createNewWaveform()" from the List_Commands module
 * 
 * Inputs:  char* function_inputs = pointer to the function inputs
 */
void
processCreateWaveform(char* function_inputs)
{
  uint32_t waveform_initial_frequency;
  uint32_t waveform_final_frequency;
  uint32_t waveform_time;
  char wave_shape = {0};

  // Extract initial frequency from serial input
  char* strtok_indx = strtok(function_inputs, ",");
  if (strtok_indx == NULL) {
    Serial.print("Create waveform must be of the form: c(waveFreq0, waveFreq1, waveTime, waveshape)\n");
    return;
  } else {
    waveform_initial_frequency = atoi(strtok_indx); // extract frequency
  }

  // Extract final frequency from serial input
  strtok_indx = strtok(NULL, ",");
  if (strtok_indx == NULL) {
    Serial.print("Create waveform must be of the form: c(waveFreq0, waveFreq1, waveTime, waveshape)\n");
    return;
  } else {
    waveform_final_frequency = atoi(strtok_indx); // extract frequency
  }

  // Extract the wave period from serial input
  strtok_indx = strtok(NULL, ",");
  if (strtok_indx == NULL) {
    Serial.print("Create waveform must be of the form: c(waveFreq0, waveFreq1, waveTime, waveshape)\n");
    return;
  } else {
    waveform_time = atoi(strtok_indx); // extract wave time
  }

  // Extract waveshape from serial input
  strtok_indx = strtok(NULL, ",");
  if (strtok_indx == NULL) {
    Serial.print("Create waveform must be of the form: c(waveFreq0, waveFreq1, waveTime, waveshape)\n");
    return;
  } else {
    wave_shape = *strtok_indx;
  }    
  // Create waveform 
  createNewWaveform(waveform_initial_frequency, waveform_final_frequency, waveform_time, wave_shape);
}

/*
 * Displays a waveform in the serial monitor by extracting the value of the identifier from the function_inputs and calling
 * "displayWaveform()" from the List_Commands module. If function_inputs is "a" then the function will display all the 
 * waveforms in the serial monitor by calling "displayWaveforms()" from the List_Commands module.
 * 
 * Inputs:  char* function_inputs = pointer to the function inputs
 */
void 
processDisplayWaveform(char* function_inputs)
{
  if (strcmp(function_inputs, "a") == 0) {
    displayWaveforms();
  } else {  
    char* strtok_indx = strtok(function_inputs, ","); 
    if (strtok_indx == NULL) {
      Serial.print("Display waveform must be of the form: d(waveform)\n");
      return;
    }
    uint16_t waveform_identifier = atoi(strtok_indx);
    displayWaveform(waveform_identifier);
  }
}

/*
 * Deletes a waveform by extracting the value of the waveform identifier from the function_inputs and calling "deleteWaveform()"
 * from the List_Commands module. If function_inputs is "a" then the function will delete all the waveforms in the linked list
 * by calling "deleteWaveforms()"
 * 
 * Inputs:  char* function_inputs = pointer to the function inputs
 */
void
processRemoveWaveform(char* function_inputs)
{
  if (strcmp(function_inputs, "a") == 0) {
    deleteAllWaveforms();
  } else {
    char* strtok_indx = strtok(function_inputs, ","); 
    if (strtok_indx == NULL) {
      Serial.print("Remove waveform must be of the form: r(waveform)\n");
      return;
    }
    uint16_t waveform_identifier = atoi(strtok_indx);
    deleteWaveform(waveform_identifier);
  }
}

/*
 * Plays the selected waveform by extracting the value of the waveform identifier from the function_inputs and calling "playWaveform()"
 * from the Play_Waveforms module. If the waveform does not exist, then the function will print an error into the serial monitor
 * 
 * Inputs:  char* function_inputs = pointer to the function inputs
 */
void
processPlayWaveform(char* function_inputs)
{
  char* strtok_indx = strtok(function_inputs, ","); 
  if (strtok_indx == NULL) {
    Serial.print("Play waveform must be of the form: p(waveform)\n");
    return;
  }
  uint16_t waveform_identifier = atoi(strtok_indx);
  waveform* wave_to_play = searchFor(waveform_identifier);
  playWaveform(wave_to_play);
}

/*
 * Loops the selected waveform by extracting the value of the waveform identifier from the function_inputs and calling "loopWaveform()"
 * from the Play_Waveforms module. If the waveform does not exist, then the function will print an error into the serial monitor
 * 
 * Inputs:  char* function_inputs = pointer to the function inputs
 */
void
processLoopWaveform(char* function_inputs)
{
  char* strtok_indx = strtok(function_inputs, ","); 
  if (strtok_indx == NULL) {
    Serial.print("Loop waveform must be of the form: l(waveform)\n");
    return;
  }
  uint32_t waveform_identifier = atoi(strtok_indx);
  waveform* wave_to_play = searchFor(waveform_identifier);
  loopWaveform(wave_to_play);
}

/*
 * Edits the selected waveform by extracting the value of the waveform identifier from the function_inputs and then extacting the 
 * property to edit and then the new value. Can input multiple properties to edit and values to the limit of the size of function_inputs. 
 * Properties are simplified to reduce typing time: f0 = waveform_initial_frequency
 *                                                  f1 = waveform_final_frequency
 *                                                  time = waveform_time
 *                                                  shape = wave_shape
 * 
 * Inputs:  char* function_inputs = pointer to the function inputs
 */
void
processEditWaveform(char* function_inputs)
{
  char* strtok_indx = strtok(function_inputs, ","); // Find the first position of the ","
  if (strtok_indx == NULL) {
    Serial.print("Edit waveform must be of the form: e(waveform, property, new value)\n");
    return;
  }
  uint32_t waveform_identifier = atoi(strtok_indx);
  waveform* wave_to_edit = searchFor(waveform_identifier);
  if (wave_to_edit == NULL) {
      Serial.print("Waveform does not exist\n");
  } else {
    strtok_indx = strtok(NULL, ","); // Find the next position of the ","
    while (strtok_indx != NULL) {
      if (strcmp(strtok_indx, "f0") == 0) {
        strtok_indx = strtok(NULL, ","); // Find the next position of the ","
        uint32_t waveform_initial_frequency = atoi(strtok_indx);
        setWaveformInitialFrequency(wave_to_edit, waveform_initial_frequency);
        
      } else if (strcmp(strtok_indx, "f1") == 0) {
        strtok_indx = strtok(NULL, ","); // Find the next position of the ","
        uint32_t waveform_final_frequency = atoi(strtok_indx);
        setWaveformFinalFrequency(wave_to_edit, waveform_final_frequency);
        
      } else if (strcmp(strtok_indx, "time") == 0) {
        strtok_indx = strtok(NULL, ","); // Find the next position of the ","
        uint32_t waveform_time = atoi(strtok_indx);
        setWaveformTime(wave_to_edit, waveform_time);
               
      } else if (strcmp(strtok_indx, "shape") == 0) {
        char wave_shape = {0};
        strtok_indx = strtok(NULL, ","); // Find the next position of the ","
        wave_shape = *strtok_indx;
        setWaveShape(wave_to_edit, wave_shape);
        
      } else {
        Serial.print("Invalid waveform property\n");
      }
      
      strtok_indx = strtok(NULL, ","); // Find the next position of the ","
    }
  }
}

/*
 * Configures a transmitter object.
 * Inputs:  char* function_inputs = pointer to the function inputs
 */
void
processConfigureTx(char* function_inputs)
{
  char* strtok_indx = strtok(function_inputs, ","); // Find the first position of the ","
  if (strtok_indx == NULL) {
    Serial.print("Transmit configure must be of form: txCfg(waveform_identifier, pin, wait_time)\n");
    return;
  }
  while (strtok_indx != NULL) {
    if (strcmp(strtok_indx, "pin") == 0) {
      strtok_indx = strtok(NULL, ",");
      uint8_t output_pin = atoi(strtok_indx); // extract pin
      setTxPin(&default_transmitter, output_pin);
    }
    else if (strcmp(strtok_indx, "waveform") == 0) {
      strtok_indx = strtok(NULL, ","); // Find the next position of the ","
      uint16_t waveform_identifier = atoi(strtok_indx);
      waveform* wave_to_play = searchFor(waveform_identifier);
      setTxWaveform(&default_transmitter, wave_to_play);
    }
    else if (strcmp(strtok_indx, "delay") == 0) {
      strtok_indx = strtok(NULL, ",");
      uint32_t wait_time = atoi(strtok_indx); // extract wait time
      setTxDelay(&default_transmitter, wait_time);
    } else {
        Serial.print("Invalid transmitter property\n");
    }
    strtok_indx = strtok(NULL, ","); // Find the next position of the ","
  }
}

/*
 * Displays the current values within the transmitter 'object'
 */
void
processDisplayTx(void)
{
  Serial.print("Transmitter\n");
  Serial.print("Pin:");
  Serial.println(getTxPin(&default_transmitter));
  Serial.print("Waveform:");
  Serial.println(getWaveformIdentifier(getTxWaveform(&default_transmitter)));
  Serial.print("Delay (ms):");
  Serial.println(getTxDelay(&default_transmitter));
  Serial.print("\n");
  
}

/*
 * Transmit. Calls the transmitWaveform function from transmitter code
 */
void
processTransmitWaveform(void)
{
  transmitWaveform(&default_transmitter);
}

/*
 * Play a wave with an initial frequeny, final frequency, time and shape.
 * Inputs:  char* function_inputs = pointer to the function inputs
 */
void
processPlayTone(char* function_inputs)
{
  uint32_t waveform_initial_frequency;
  uint32_t waveform_final_frequency;
  uint32_t waveform_time;
  char wave_shape;
  char* strtok_indx = strtok(function_inputs, ","); // Find the first position of the ","
  if (strtok_indx == NULL) {
    Serial.print("Play tone must be of the form: pt(f0,f1,time,shape)\n");
    return;
  }
    // Extract initial frequency from serial input
  if (strtok_indx == NULL) {
    Serial.print("Play tone must be of the form: pt(f0,f1,time,shape)\n");
    return;
  } else {
    waveform_initial_frequency = atoi(strtok_indx); // extract frequency
  }

  // Extract final frequency from serial input
  strtok_indx = strtok(NULL, ",");
  if (strtok_indx == NULL) {
    Serial.print("Play tone must be of the form: pt(f0,f1,time,shape)\n");
    return;
  } else {
    waveform_final_frequency = atoi(strtok_indx); // extract frequency
  }

  // Extract the wave period from serial input
  strtok_indx = strtok(NULL, ",");
  if (strtok_indx == NULL) {
    Serial.print("Play tone must be of the form: pt(f0,f1,time,shape)\n");
    return;
  } else {
    waveform_time = atoi(strtok_indx); // extract wave time
  }

  // Extract waveshape from serial input
  strtok_indx = strtok(NULL, ",");
  if (strtok_indx == NULL) {
    Serial.print("Play tone must be of the form: pt(f0,f1,time,shape)\n");
    return;
  } else {
    wave_shape = *strtok_indx;
  }    
  // Create waveform 
  playAudioTone(waveform_initial_frequency, waveform_final_frequency, waveform_time, wave_shape);
}

/*
 * Loop a wave with an initial frequeny, final frequency, time and shape.
 * Inputs:  char* function_inputs = pointer to the function inputs
 */
void
processLoopTone(char* function_inputs)
{
  uint32_t waveform_initial_frequency;
  uint32_t waveform_final_frequency;
  uint32_t waveform_time;
  char wave_shape;
  char* strtok_indx = strtok(function_inputs, ","); // Find the first position of the ","
  if (strtok_indx == NULL) {
    Serial.print("Loop tone must be of the form: lt(f0,f1,time,shape)\n");
    return;
  }
  // Extract initial frequency from serial input
  if (strtok_indx == NULL) {
    Serial.print("Loop tone must be of the form: lt(f0,f1,time,shape)\n");
    return;
  } else {
    waveform_initial_frequency = atoi(strtok_indx); // extract frequency
  }

  // Extract final frequency from serial input
  strtok_indx = strtok(NULL, ",");
  if (strtok_indx == NULL) {
    Serial.print("Loop tone must be of the form: lt(f0,f1,time,shape)\n");
    return;
  } else {
    waveform_final_frequency = atoi(strtok_indx); // extract frequency
  }

  // Extract the wave period from serial input
  strtok_indx = strtok(NULL, ",");
  if (strtok_indx == NULL) {
    Serial.print("Loop tone must be of the form: lt(f0,f1,time,shape)\n");
    return;
  } else {
    waveform_time = atoi(strtok_indx); // extract wave time
  }

  // Extract waveshape from serial input
  strtok_indx = strtok(NULL, ",");
  if (strtok_indx == NULL) {
    Serial.print("Loop tone must be of the form: lt(f0,f1,time,shape)\n");
    return;
  } else {
    wave_shape = *strtok_indx;
  }    
  // Create waveform 
  loopAudioTone(waveform_initial_frequency, waveform_final_frequency, waveform_time, wave_shape);
}
