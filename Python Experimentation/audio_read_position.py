import pyaudio
import matplotlib.pyplot as plt
import numpy as np
from scipy.signal import butter, lfilter
from scipy.signal import freqz
import scipy.fft

CHUNK = 100
FORMAT = pyaudio.paInt16
CHANNELS = 1
RATE = 44100
RECORD_SECONDS = 6
TARGET_BAND = 1000
RMS_LENGTH = int(RATE/(TARGET_BAND))

'''------------------------------------------------------------------------------
Setting Up Filters
'''

#------------------------------------------------------------
def butter_bandpass(lowcut, highcut, fs, order=5):
    nyq = 0.5 * fs
    low = lowcut / nyq
    high = highcut / nyq
    b, a = butter(order, [low, high], btype='band')
    return b, a

def butter_bandpass_filter(data, lowcut, highcut, fs, order=5):
    b, a = butter_bandpass(lowcut, highcut, fs, order=order)
    y = lfilter(b, a, data)
    return y

def rmsCalculator(data, samplesCount, rmsAvgLen):
    rmsData = []
    for i in range(rmsAvgLen, samplesCount):
        rmsData.append(0)
        for j in range(0, rmsAvgLen):
            rmsData[-1] += data[i - j]**2
        rmsData[-1] = np.sqrt(rmsData[-1]/samplesCount)
    return rmsData

#------------------------------------------------------------

lowcut = TARGET_BAND - 1
highcut = TARGET_BAND + 1
order = 1

b, a = butter_bandpass(lowcut, highcut, RATE, order=order)
w, h = freqz(b, a, worN=2000)
'''
plt.figure(1)
plt.plot((RATE * 0.5 / np.pi) * w, abs(h), label="order = %d" % order)
plt.xlabel('Frequency (Hz)')
plt.ylabel('Gain')
plt.grid(True)
plt.legend(loc='best')
'''
'''------------------------------------------------------------------------------
Recodring Sound
'''
p = pyaudio.PyAudio()

stream = p.open(format=FORMAT,
                channels=CHANNELS,
                rate=RATE,
                input=True,
                frames_per_buffer=CHUNK)

print("* recording")

frames = []
loggedFrames = []
for i in range(0, int(RATE / CHUNK * RECORD_SECONDS)):
    data = stream.read(CHUNK)
    frames.append(np.frombuffer(data, dtype ="int16"))


print("* done recording")

stream.stop_stream()
stream.close()
p.terminate()


frames = [item for sublist in frames for item in sublist]

'''------------------------------------------------------------------------------
Filtering noisy Sound
'''

y = butter_bandpass_filter(frames, lowcut, highcut, RATE, order=order)
x = [i/RATE for i in range(0, len(frames))]


movingAvgLen = 150

for i in range(0, len(y)-movingAvgLen):
    sum = 0
    for j in range(0, movingAvgLen):
        sum += abs(y[i+j])
    y[i] = sum/movingAvgLen


yf = scipy.fft.fft(frames)
xf = scipy.fft.fftfreq(RATE*RECORD_SECONDS, 1/RATE)[:(RATE*RECORD_SECONDS)//2]

fig, axs = plt.subplots(3)


axs[0].semilogy(xf[1:(RATE*RECORD_SECONDS)//2], 2/(RATE*RECORD_SECONDS) * np.abs(yf[1:(RATE*RECORD_SECONDS//2)]))
axs[0].set_title("Fast Forurier Transform")


axs[1].plot(x, frames)
axs[1].plot(x, y)
axs[1].set_title("Raw Data and Band Pass at " + str(TARGET_BAND) + "Hz")

'''
loggedFrames = [20*np.log10(abs(item)) for item in rmsCalculator(y, RATE*RECORD_SECONDS, RMS_LENGTH)]

# Plotting bandpass rms and finding start point
largestValueYet = 0

soundStartPoint = 0
offsetSize = 100

for i in range(offsetSize, len(loggedFrames)):
    if(loggedFrames[i] > loggedFrames[largestValueYet]):
        largestValueYet = i
#        for j in range(i, offsetSize, -1):
#            if(loggedFrames[j] > loggedFrames[j-offsetSize]):
#                soundStartPoint = j
#                break

soundStartPoint = largestValueYet

axs[2].plot(x[RMS_LENGTH:], loggedFrames)
axs[2].plot([x[soundStartPoint], x[soundStartPoint]], [-10, -80])
axs[2].set_title("Un-tuned dB of " +str(TARGET_BAND) + "Hz")
'''

print(len(x))
maxIndex = np.argmax(y)
maxVal = y[maxIndex]

percentEdge = 0.5

edgePos = 0

for i in range(maxIndex, 0, -1):
    if(y[i] < maxVal*percentEdge):
        edgePos = i
        break

numSperation = 1000
flatBoundry = 1 # Degrees


for i in range(edgePos, 0, -1):
    slope = np.degrees(np.arctan((y[i]-y[i-numSperation])/(numSperation)))
    print(slope)
    if(slope < flatBoundry):
        edgePos = i
        break


axs[2].plot(x, y)
axs[2].plot([x[edgePos], x[edgePos]], [0, maxVal*1.1])

plt.show()
