// Author: Laurence Prins
// Date: 27/06/2021
// Description: waveform linked list commands. Zombified from https://www.tutorialspoint.com/data_structures_algorithms/linked_list_program_in_c.htm

void 
createInitialWaveform() // create the initial waveform
{
  struct waveform *link = (struct waveform*) malloc(sizeof(struct waveform));

  link->waveformIdentifier = 0;
  link->waveformFrequency = initialFreq;
  link->waveformTime = initialTime;
  link->waveformPulses = initialPulses;
  link->waveShape = initialShape;
  
  link->next = head;
  head = link;
}

void
createNewWaveform(int identifier, int waveFreq, int waveTime, int wavePulses, char waveType)
{
  struct waveform *link = (struct waveform*) malloc(sizeof(struct waveform));

  link->waveformIdentifier = identifier;
  link->waveformFrequency = waveFreq;
  link->waveformTime = waveTime;
  link->waveformPulses = wavePulses;
  link->waveShape = waveType;
  
  link->next = head;
  head = link;
}

void 
displayWaveforms() 
{

  struct waveform *ptr = head;
  
   //start from the beginning
  while(ptr != NULL) {
    displayWaveform(ptr->waveformIdentifier);
    ptr = ptr->next;
  } 
  
}

void
displayWaveform(int identifier)
{
  waveform* waveToDisplay = searchFor(identifier);
  if (waveToDisplay == NULL) {
    Serial.print("Waveform does not exist\n");
    return;
  }
  Serial.print("Waveform: ");
  Serial.println(waveToDisplay->waveformIdentifier);
  Serial.print("Frequency: ");
  Serial.println(waveToDisplay->waveformFrequency);
  Serial.print("Time: ");
  Serial.println(waveToDisplay->waveformTime);
  Serial.print("Number of Pulses: ");
  Serial.println(waveToDisplay->waveformPulses);
  Serial.print("Waveshape: ");
  Serial.println(waveToDisplay->waveShape);
  Serial.print("\n");
}

struct
waveform* searchFor(int identifier)
{
  struct waveform* current = head;
  if(head == NULL) {
      return NULL;
   }
   //navigate through list
   while(current->waveformIdentifier != identifier) {
 
      if(current->next == NULL) {
         return NULL;
      } else {
         current = current->next;
      }
   }      
  
   return current; //if identifier is found, return the current Link
}

void 
deleteAllWaveforms() 
{

  struct waveform *ptr = head;
  
  //start from the beginning
  while(ptr != NULL) {
    deleteWaveform(ptr->waveformIdentifier);
    ptr = ptr->next;
  } 
  
}

struct 
waveform* deleteWaveform(int identifier) 
{
   //start from the first link
   struct waveform* current = head;
   struct waveform* previous = NULL;
  
   //if list is empty
   if(head == NULL) {
      return NULL;
   }

   //navigate through list
   while(current->waveformIdentifier != identifier) {

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
