// Author: Laurence Prins, Aryan Srivastava, Bill Liu
// Date: 27/08/2021
// Description: Code for receiving and processing a received waveform

/*
 * TO DO:
 * 1. On edge detection of a pin start recording values for T seconds.
 * 2. Convolve the known waveform with received data array.
 * 3. Find the maximum index within the convolved array.
 * 4. Subtract from the maximum index the tone duration multiplied by Fs to find the element of the start of the waveform.
 * 5. Take the element and divide by Fs to find the time of flight.
 * 6. Multiply time of flight by speed of sound to get measurement.
 * 7. Return or print measurement.
 */
