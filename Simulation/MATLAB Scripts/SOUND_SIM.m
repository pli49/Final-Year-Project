clear
clc

SPL_2 = zeros(150, 1);
SPL_1 = 90;
R_1 = 0.1;
R_2 = (1:1:150);
for i = 1:1:150
    SPL_2(i, 1) = SPL_1 - 20*log10(R_2(1, i)/R_1);
end

plot(R_2, SPL_2)
SPL_2;



f_Hz = [125, 250, 500, 1000, 2000, 4000 8000];
humid70 = [0.3, 1.1, 2.8, 5, 9, 22.9, 76.6]/100;
carpet = [0.01 ; 0.02 ; 0.06 ; 0.15 ; 0.25 ; 0.45];
plywood = [0.38 ; 0.24 ; 0.17 ; 0.1 ; 0.08 ; 0.08];
SPL_3 = SPL_2(10)* ones(1, length(f_Hz)) - humid70;
SPL_4 = SPL_2(100)* ones(1, length(f_Hz)) - humid70 * 10;

figure(1)
subplot(211)
plot(f_Hz(1:end-1), plywood)
title("Affect of Frequency on Plywood")
xlabel("Frequency (Hz)")
ylabel("Attenuation Coeffecient")
subplot(212)
plot(f_Hz(1:end-1), carpet)
title("Affect of Frequency on Carpet")
xlabel("Frequency (Hz)")
ylabel("Attenuation Coeffecient")

figure(2)
plot(R_2, SPL_2)
title("Affect of Distance on SPL")
xlabel("Distance (m)")
ylabel("SPL (dB)")

figure(3)
plot(f_Hz, humid70)
title("Affect of frequency on Attenuation")
xlabel("Frequency (Hz")
ylabel("Attenuation loss (dB/10m)")

figure(4)
plot(f_Hz, SPL_3)
title("Cummulative affect of frequency and distance at 10m")
xlabel("Frequency (Hz")
ylabel("SPL (dB)")


