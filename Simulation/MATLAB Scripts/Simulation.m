clear
close all
clc

% Transmitter
T_stop = 1; % Generate signal for T seconds [s]
F_w = 1000; % Frequency of audio wave [Hz] 
F_s = 50*F_w*T_stop ; % Sampling frequency [Hz]
t = linspace(0,T_stop,F_s); % Time matrix [s]
A = 0.2; % Amplitude of generated wave 

y1 = A*sin(2*pi*F_w*t); % Generated wave

% View generated waveform for n periods 
n = 5; % n periods
figure(1)
plot(t, y1);
xlim([0 n*1/F_w]);
