#ifndef TRANSMITTER_CODE_H_
#define TRANSMITTER_CODE_H_

typedef struct
{
  uint8_t output_pin;
  uint32_t delay_period; 
  struct waveform* wave_to_play; 
}TX;

void txConfig(TX* tx, waveform* wave_to_play, uint32_t delay_period, uint8_t output_pin);
void transmitWaveform(TX* tx);
void setTxWaveform(TX* tx, waveform* wave_to_play);
waveform* getTxWaveform(TX* tx);
void setTxPin(TX* tx, uint8_t output_pin);
uint8_t getTxPin(TX* tx);
void setTxDelay(TX* tx, uint32_t delay_period);
uint32_t getTxDelay(TX* tx);

#endif
