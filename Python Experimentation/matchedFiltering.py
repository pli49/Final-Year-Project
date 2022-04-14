'''
    Description:
        This script is meant to test a method of distance measurement using sound.
        The sound produced is made using a linear fm sweep
        The sound is detected using matched filtering
'''
from numpy.core.numeric import convolve
import sounddevice as sd
import matplotlib.pyplot as plt
import numpy as np
import math
import time

FS = 44100

RECORD_DURATION = 4
TONE_DURATION = 0.25
TONE_DELAY = 1

LOW_FREQ = 1000
UPPER_FREQ = 2000
MAX_AMPLITUDE = 1
MATCHED_BOUNDY = 100

MICROPHONE_STARTUP_TIME = 2048
SPEED_OF_SOUND = 343

# myrecording = sd.rec(int(RECORD_DURATION*FS), samplerate=FS, channels=1)
# sd.wait()

tone = [0]*(RECORD_DURATION*FS)

for i in range(int(TONE_DELAY*FS), int((TONE_DURATION + TONE_DELAY)*FS)):

    iZero = i - TONE_DELAY*FS # A version of i that counts from zero
    freqFrac = iZero/(FS*TONE_DURATION)
    currentFreq = (UPPER_FREQ - LOW_FREQ) * freqFrac + LOW_FREQ
    currentPhase = iZero/(FS/currentFreq)

    tone[i] = MAX_AMPLITUDE * math.sin(2*math.pi * currentPhase)


ht = tone[int(TONE_DELAY*FS - MATCHED_BOUNDY):int((TONE_DELAY+TONE_DURATION)*FS + MATCHED_BOUNDY)]



recorded_tone = sd.playrec(tone, FS, channels=1)

sd.wait()



tone_arr = np.array(ht)
rec_array = np.transpose(np.array(recorded_tone))[0]

fig, (ax1, ax2, ax3) = plt.subplots(3,1)
ax1.plot(tone)

start_time = time.time()
convol_arr = np.convolve(np.flip(tone_arr), rec_array)
ax3.plot(convol_arr)

maxpos = np.argmax(convol_arr)


ax2.plot(range(0, len(recorded_tone)), recorded_tone, [maxpos - TONE_DURATION*FS, maxpos - TONE_DURATION*FS], [-.2, .2])

toneStartSpeak = TONE_DELAY*FS

toneStartHear = maxpos - MICROPHONE_STARTUP_TIME - TONE_DURATION*FS

responseTime = (toneStartHear-toneStartSpeak)/FS

measuredDistance = SPEED_OF_SOUND * responseTime

print("Distance: {:.5} mm".format(str(measuredDistance*100)))
print("Time Diff: {}".format(responseTime/10))
print("Took ", time.time()-start_time, " to Process")


plt.show()
