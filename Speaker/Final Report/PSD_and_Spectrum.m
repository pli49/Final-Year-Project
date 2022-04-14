close all
clear
clc

%% Import audio
% y = imported audio data
% Fs = sampling frequency
[y_tone, F_s] = audioread('10k_tone.mp4'); % Extract // and sampling frequency from signal

% Use flute data for main demonstrations
y_1 = y_tone(:, 1); % Select first channel if stereo
F_s = F_s;

m_order = 100; % Order
nOutputs=5020; % Smoothing

%% Time domain audio signal
audoClipLength = length(y_1)/F_s;  % Find the length of the audio clip
T_s = 1/F_s; % Find the sampling period
timeVector = [0 : T_s : audoClipLength - T_s]'; % Create a time vector with length equal to the audio clip length and intervals of sampling period

figure(1)
plot(timeVector, y_1); % Plot Y against time
set(gcf, 'Name', 'Time Domain Signal')

%% Compute and plot the FFT of the signal
Y_FFT = fft(y_1); % FFT of Y
L = length(y_1); % Length of Y vector

P2 = abs(Y_FFT/L); % Double ended spectrum of Y_s
P1 = P2(1:floor(L/2)+1); 
P1(2:end-1) = 2*P1(2:end-1); % Single sided spectrum of Y_s
freqVect = F_s*(0:(L/2))/L; % Create a frequency vector of the same length of P1

figure(2)
plot(freqVect/1000,P1) % Plot the spectrum
xlabel('Frequency (kHz)', 'FontSize', 34)
ylabel('|Y_f(f)|', 'FontSize', 34)
set(gcf, 'Name', 'Spectrum')
set(gca,'FontSize',34)
grid on

%% Yule Walker
[Pxx_yw,F] = pyulear(y_1,m_order,nOutputs,F_s);

figure(8)
plot(F/1000,20*log10(Pxx_yw/0.00002))
grid on
xlabel('Frequency (kHz)', 'FontSize', 34)
ylabel('Power (dB)', 'FontSize', 34)
set(gca,'FontSize',34)
set(gcf, 'Name', 'Yule-Walker Method')
