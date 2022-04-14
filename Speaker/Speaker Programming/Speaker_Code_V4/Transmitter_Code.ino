// Author: Laurence Prins
// Date: 24/08/2021
// Description: Code for transmitting

#include "Transmitter_Code.h"

/*
 * Configure a TX object.
 * Inputs:  TX* tx = pointer to a TX object
 *          waveform* wave_to_play = pointer to a waveform object
 *          uint8_t output_pin = pin to pull high
 *          uint32_t delay_period = time to wait
 */
void
txConfig(TX* tx, waveform* wave_to_play, uint8_t output_pin, uint32_t delay_period)
{
  tx->wave_to_play = wave_to_play;
  tx->delay_period = delay_period;
  tx->output_pin = output_pin;
}

/*
 * Transmits. 1. pull line high, 2. play waveform, 3. wait, 4. pull line low.
 * Inputs:  TX* tx = pointer to a TX object
 */
void
transmitWaveform(TX* tx)
{
   pinMode(tx->output_pin, OUTPUT);
   digitalWrite(tx->output_pin, HIGH);
   playWaveform(tx->wave_to_play);
   delay(tx->delay_period);
   digitalWrite(tx->output_pin, LOW);
}

/*
 * Set the waveform for the transmitter to play
 * Inputs:  TX* tx = pointer to a TX object
 *          waveform* wave_to_play = pointer to a waveform object
 */
void
setTxWaveform(TX* tx, waveform* wave_to_play)
{
  tx->wave_to_play = wave_to_play;
}

/*
 * Get the waveform that is currently set for the selected transmitter
 * Inputs:  TX* tx = pointer to a TX object
 * Outputs: waveform* wave_to_play = pointer to a waveform object
 */
waveform*
getTxWaveform(TX* tx)
{
  return tx->wave_to_play;
}

/*
 * Set the pin which the transmitter will pull high before transmitting
 * Inputs:  TX* tx = pointer to a TX object
 *          uint8_t output_pin = pin to pull high
 */
void
setTxPin(TX* tx, uint8_t output_pin)
{
  tx->output_pin = output_pin;
}

/*
 * Returns what pin the transmitter will pull high before transmitting
 * Inputs:  TX* tx = pointer to a TX object
 * Outputs: uint8_t output_pin = pin to pull high
 */
uint8_t
getTxPin(TX* tx)
{
  return tx->output_pin;
}

/*
 * Set the delay which the transmitter will wait for after transmitting
 * Inputs:  TX* tx = pointer to a TX object
 *          uint32_t delay_period = time to wait
 */
void
setTxDelay(TX* tx, uint32_t delay_period)
{
  tx->delay_period = delay_period;
}

/*
 * Returns the time that the transmitter waits after transmitting
 * Inputs:  TX* tx = pointer to a TX object
 * Outputs: uint32_t delay_period = time to wait
 */
uint32_t
getTxDelay(TX* tx)
{
  return tx->delay_period;
}
