// Author: Laurence Prins
// Date: 25/06/2021
// Description: Code for reading commands from the serial line

// Serial code setup
char start_marker = '<';
char end_marker = '>';

// Serial code begin
/*
 * Checks to see if serial is avaiable then checks the input for the start marker
 * Outputs: 1 if there is data to be read
 *          0 if there is no data to be read
 */
bool
checkSerial()
{
  if (Serial.available() > 0) {
    char rc = Serial.read();
    if (rc == start_marker) {
      return 1;
    } 
  }
  return 0;
}

/*
 * Reads serial until it detects the end marker.
 * Outputs: char* read_data = pointer to a character array containing everything before the end marker
 */
char*
readSerialInput()
{
  uint32_t curr_index = 0;
  char read_char;
  char serial_data[(NUM_CHARS_FUNCTION + NUM_CHARS_INPUTS)] = {0};
  while(Serial.available() > 0) {
    read_char = Serial.read();
    if (read_char != end_marker) {
      serial_data[curr_index] = read_char;
      ++curr_index;
      if (curr_index >= (NUM_CHARS_FUNCTION + NUM_CHARS_INPUTS)) {
        curr_index = (NUM_CHARS_FUNCTION + NUM_CHARS_INPUTS) - 1;
      }
    } else {
      serial_data[curr_index] = '\0';
    }
  }
  char* read_data = (char*)malloc((NUM_CHARS_FUNCTION + NUM_CHARS_INPUTS)*sizeof(char) + 1);
  strcpy(read_data, serial_data);
  return read_data;
}

void 
recvWithStartEndMarkers() 
{
  static boolean recvInProgress = false;
  static byte ndx = 0;
  char startMarker = '<';
  char endMarker = '>';
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
