// Author: Laurence Prins
// Date: 27/06/2021
// Description: module for dealing with the waveform linked list objects and commands

// Waveform setup
struct waveform
{
  uint16_t waveform_identifier; // unique identifier for given waveform
  uint32_t waveform_initial_frequency; // initial frequency [Hz]
  uint32_t waveform_final_frequency; // final frequency [Hz]
  uint32_t waveform_time; // length of the waveform [ms]
  uint32_t waveform_pulses; // number of times to play the waveform
  char wave_shape; // shape of the waveform. s = sine, p = square.
  struct waveform *next; // Pointer to the next waveform in the linked list structure
};

struct waveform *head = NULL;
struct waveform *current = NULL;

int curr_identifier = 0;

// Linked list code begin

/*
 * Create a new "waveform" object and store in the linked list data structure
 * Inputs:  uint32_t waveform_intial_frequency = initial frequency [Hz]
 *          uint32_t waveform_final_frequency = final frequency [Hz]
 *          uint32_t waveform_time = length of the waveform [ms]
 *          uint32_t waveform_pulses = number of times to play the waveform
 *          char wave_shape = shape of the waveform. s = sine, p = square.
 */
void
createNewWaveform(uint32_t waveform_initial_frequency, uint32_t waveform_final_frequency, uint32_t waveform_time, uint32_t waveform_pulses, char wave_shape)
{
  struct waveform *link = (struct waveform*) malloc(sizeof(struct waveform));
  
  link->waveform_identifier = curr_identifier;
  link->waveform_initial_frequency = waveform_initial_frequency;
  link->waveform_final_frequency = waveform_final_frequency;
  link->waveform_time = waveform_time;
  link->waveform_pulses = waveform_pulses;
  link->wave_shape = wave_shape;
  
  ++curr_identifier;
  link->next = head;
  head = link;
}

/*
 * Displays all of the waveforms currently in the linked list data structure and prints them into the serial monitor
 */
void 
displayWaveforms() 
{
  struct waveform *ptr = head;
  
  //start from the beginning
  while(ptr != NULL) {
    displayWaveform(ptr->waveform_identifier);
    ptr = ptr->next;
  } 
}

/*
 * Displays the waveform with input identifier in the serial monitor
 * Inputs:  identifier: waveforms unique identifier
 */
void
displayWaveform(uint32_t identifier)
{
  waveform* wave_to_display = searchFor(identifier);
  
  if (wave_to_display == NULL) {
    Serial.print("Waveform does not exist\n");
    return;
  }
  
  Serial.print("Waveform: ");
  Serial.println(getWaveformIdentifier(wave_to_display));
  
  Serial.print("Initial Frequency: ");
  Serial.println(getWaveformInitialFrequency(wave_to_display));
  
  Serial.print("Final Frequency: ");
  Serial.println(getWaveformFinalFrequency(wave_to_display));
  
  Serial.print("Time: ");
  Serial.println(getWaveformTime(wave_to_display));
  
  Serial.print("Number of Pulses: ");
  Serial.println(getWaveformPulses(wave_to_display));
  
  Serial.print("Wave Shape: ");
  Serial.println(getWaveShape(wave_to_display));
  
  Serial.print("\n");
}

/*
 * Searches the linked list for the waveform with the given identifier
 * Inputs:  int identifier = waveforms unique identifier
 * Outputs: waveform* waveform = pointer to the waveform with the given identifier
 */
struct
waveform* searchFor(uint32_t identifier)
{
  struct waveform* current = head;
  if(head == NULL) {
      return NULL;
   }
   //navigate through list
   while(current->waveform_identifier != identifier) {
 
      if(current->next == NULL) {
         return NULL;
      } else {
         current = current->next;
      }
   }      
  
   return current; //if identifier is found, return the current Link
}

/*
 * Deletes all the waveforms in the linked list
 */
void 
deleteAllWaveforms() 
{

  struct waveform *ptr = head;
  
  //start from the beginning
  while(ptr != NULL) {
    deleteWaveform(ptr->waveform_identifier);
    ptr = ptr->next;
  } 
  curr_identifier = 0;
}

/*
 * Deletes the waveform with the given identifier
 * Inputs:  int identifier = waveforms unique identifier
 * Outputs: waveform* waveform = pointer to the waveform currently at the head of the linked list
 */
struct 
waveform* deleteWaveform(uint16_t identifier) 
{
   //start from the first link
   struct waveform* current = head;
   struct waveform* previous = NULL;
  
   //if list is empty
   if(head == NULL) {
      return NULL;
   }

   //navigate through list
   while(getWaveformIdentifier(current) != identifier) {

      //if it is last node
      if(current->next == NULL) {
         return NULL;
      } else {
         //store reference to current link
         previous = current;
         //move to next link
         current = current->next;
      }
   }

   //found a match, update the link
   if(current == head) {
      //change first to point to next link
      head = head->next;
   } else {
      //bypass the current link
      previous->next = current->next;
   }    
  
   return current;
}

/*
 * Sets the identifier of the given waveform
 * Inputs:  waveform* waveform = pointer to the waveform to edit
 *          uint32_t identifier = new identifier given waveform 
 */
void
setWaveformIdentifier(waveform* wave_to_edit, uint32_t waveform_identifier)
{
  wave_to_edit->waveform_identifier = waveform_identifier;
}

/*
 * Returns the identifier of the given waveform
 * Inputs:  waveform* waveform = pointer to a waveform object
 * Outputs: uint32_t identifier = waveform identifier
 */
uint16_t
getWaveformIdentifier(waveform* wave_to_get)
{
  return wave_to_get->waveform_identifier;
}

/*
 * Sets the initial frequency of the given waveform
 * Inputs:  waveform* waveform = pointer to the waveform to edit
 *          uint32_t waveform_initial_frequency = new initial frequency for the given waveform [Hz]
 */
void
setWaveformInitialFrequency(waveform* wave_to_edit, uint32_t waveform_initial_frequency)
{
  wave_to_edit->waveform_initial_frequency = waveform_initial_frequency;
}

/*
 * Returns the current value of the initial frequency of the given waveform
 * Inputs:  waveform* waveform = pointer to a waveform object
 * Outputs: uint32_t waveform_initial_frequency = initial frequency [Hz]
 */
uint32_t
getWaveformInitialFrequency(waveform* wave_to_get)
{
  return wave_to_get->waveform_initial_frequency;
}

/*
 * Sets the final frequency of the given waveform
 * Inputs: waveform* waveform = pointer to the waveform to edit 
 *         uint32_t waveform_final_frequency = new final frequency for the given waveform [Hz]
 */
void
setWaveformFinalFrequency(waveform* wave_to_edit, uint32_t waveform_final_frequency)
{
  wave_to_edit->waveform_final_frequency = waveform_final_frequency;
}

/*
 * Returns the current value of the final frequency of the given waveform
 * Inputs:  waveform* waveform = pointer to a waveform object
 * Outputs: uint32_t waveform_initial_frequency = final frequency [Hz]
 */
int
getWaveformFinalFrequency(waveform* wave_to_get)
{
  return wave_to_get->waveform_final_frequency;
}

/*
 * Sets the time of the given waveform
 * Inputs: waveform* waveform = pointer to the waveform to edit
 *         uint32_t waveform_time = new time for the given waveform
 */
void
setWaveformTime(waveform* wave_to_edit, uint32_t waveform_time)
{
  wave_to_edit->waveform_time = waveform_time;
}

/*
 * Returns the current value of the play time of the given waveform
 * Inputs:  waveform* waveform = pointer to a waveform object
 * Outputs: uint32_t waveform_time = time [ms]
 */
uint32_t
getWaveformTime(waveform* wave_to_get)
{
  return wave_to_get->waveform_time;
}

/*
 * Sets the number of pulses of the given waveform
 * Inputs:  waveform* waveform = pointer to the waveform to edit
 *          uint32_t waveform_pulses = new pulses for the given waveform
 */
void
setWaveformPulses(waveform* wave_to_edit, uint32_t waveform_pulses)
{
  wave_to_edit->waveform_pulses = waveform_pulses;
}

/*
 * Returns the current value of the number of pulses of the given waveform
 * Inputs:  waveform* waveform = pointer to a waveform object
 * Outputs: uint32_t waveform_time = time [ms]
 */
uint32_t
getWaveformPulses(waveform* wave_to_get)
{
  return wave_to_get->waveform_pulses;
}

/*
 * Sets the initial frequency of the given waveform
 * Inputs: waveform* waveform = pointer to the waveform to edit
 *         char wave_shape = new wave shape for the given waveform
 */
void
setWaveShape(waveform* wave_to_edit, char wave_shape)
{
  wave_to_edit->wave_shape = wave_shape;
}

/*
 * Returns the current shape of the given waveform
 * Inputs:  waveform* waveform = pointer to a waveform object
 * Outputs: char wave_shape = wave shape
 */
char
getWaveShape(waveform* wave_to_get)
{
  return wave_to_get->wave_shape;
}
