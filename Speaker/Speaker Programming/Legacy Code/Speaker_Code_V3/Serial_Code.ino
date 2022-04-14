// Author: Laurence Prins
// Date: 25/06/2021
// Description: Code for reading commands from the serial line

// Serial code setup
char start_marker = '<';
char end_marker = '>';

// Serial code begin
/*
 * Reads serial until it detects the end marker 
 */
void 
recvWithStartEndMarkers() 
{
  boolean recv_in_progress = false;
  uint32_t curr_index = 0;
  char rc;

  while (Serial.available() > 0 && new_data == false) {
    rc = Serial.read();

    if (recv_in_progress == true) {
        if (rc != end_marker) {
            received_chars[curr_index] = rc;
            curr_index++;
            if (curr_index >= num_chars) {
                curr_index = num_chars - 1;
            }
        }
        else {
            received_chars[curr_index] = '\0'; // terminate the string
            recv_in_progress = false;
            curr_index = 0;
            new_data = true;
        }
    }

    else if (rc == start_marker) {
        recv_in_progress = true;
    }
  }
}
