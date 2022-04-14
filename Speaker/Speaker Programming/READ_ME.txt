Code now works by creating "waveforms" with the following features:
 - identifier: For the linked list structure, this is unique to each waveform.
 - initial frequency: initial waveform frequency in Hz.
 - final frequency: final waveform frequency in Hz.
 - time: how long the wave will play for in ms.
 - waveshape: the shape of the wave, options are: square (p), sine (s) and triangle (t). Last two are yet to be
 implemented.

The waveforms are stored in a linked list structure. The following functions are used to interact with the 
created waveforms. The code only reads from serial inputs between pointy brackets <___>.

NEW WAVEFORM:
<n(f0,f1,t,s)> 

f0 = initial frequency, f1 = final frequency, t = time, and s = wave shape = p, s or t.

Will spit out an error into serial if not given 4 valid inputs.
This function creates a waveform with the specified properties and inserts it in the next free slot in the 
linked list.


EDIT WAVEFORM:
<e(i,property,new_value)>

i = waveform identifier, property = f0,f1,time, or shape, new_value = new value for specified property.

Can edit multiple properties at once. If waveform or property does not exist then will spit out an error.
This function edits the waveform with the specified new value.


DELETE WAVEFORM:
<r(i)>

i = waveform identifier. Can input i = a to remove all waveforms from the linked list.

Removes the waveform from the linked list. If waveform does not exist then will spit out an error.


DISPLAY WAVEFORM:
<d(i)>

i = waveform identifier. Can input i = a to display all waveforms in the linked list. If waveform does not exist then will spit out an error.


PLAY WAVEFORM:
<p(i)>

i = waveform identifier. If waveform does not exist, will spit out an error.	

Plays the specified waveform through the AUDIO_OUTPUT pin.


LOOP WAVEFORM:
<l(i)>

i = waveform identifier. If waveform does not exist, will spit out an error.	

Loops the specified waveform through the AUDIO_OUTPUT pin. Can stop the loop by inputting a new command.

Display Transmitter Properties:
<TxDisp()>

Configure Transmitter:
<TxCfg(waveform_identifier, output_pin, wait_time)>

Transmit:
<Tx()>

