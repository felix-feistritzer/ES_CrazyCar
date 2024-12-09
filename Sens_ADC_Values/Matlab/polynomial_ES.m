% CREATE A FINE POLYNOME 
clc; clear all; hold off; close all;

table_size = 512;
lut_factor = 4096 / table_size;
sensorOutput = [2.75 2.55 2 1.55 1.25 1.05 0.9 0.8 0.725 0.65 0.6 0.55 0.5 0.495 0.49];        % Just an initial characteristic curve of the infrared sensor
ADCchange = 4096 / max(2.75);
adcOutput_front = [4095 4095 3630 2980 2520 1960 1600 1350 1180 1060 970 890 840,...
    750 700 610 560 525 470 935 850 780 715 690 640 600]./lut_factor;                         % MEASURED ADC Values of your measured distances

relatedDistance_mm_front = [0 2.5 5 7.5 10 15 20 25 30 35 40 45 50 55 60 65 70 75 80 90  100 110 120 130 140 150] * 10; % HERE you could store your measured distance values


[p_front,s_front] = polyfit(adcOutput_front, relatedDistance_mm_front, 9);          % Fits a polynom of order-n to your input values 
x_front = linspace(0,floor(max(adcOutput_front)),table_size);                       % Just create ADC Values in order to plot the results of the polynome

f_front = floor(polyval(p_front,x_front));                                          % Calculates your results, taking into account the measured values and the already stored polynome

% f_front(f_front>512) = 512;                                                       % Just uses ADC lower or equal to 4096
%f_front(x_front<floor(min(adcOutput_front))) = max(relatedDistance_mm_front);     % THERE ARE NO NEGATIVE ADC results
f_front(f_front>max(relatedDistance_mm_front)) = max(relatedDistance_mm_front);

figure(1)
subplot(1,2,1)
plot(adcOutput_front,relatedDistance_mm_front);                 
hold on;
%plot(x_front,f_front,'o')

title('Front Sensor output value');
xlabel('Scaled ADC Values (samples)');
ylabel('Distance (mm)');
grid on; grid minor;

subplot(1,2,2)
plot(adcOutput_front,relatedDistance_mm_front);                 
hold on;
plot(x_front,f_front,'o')

legend('Measured Sensor Values','Approximated Sensor Values');

title('Front Sensor output value');
xlabel('Scaled ADC Values (samples)');
ylabel('Distance (mm)');
grid on; grid minor;
X_front = table(x_front',f_front');

fprintf('unsigned short ir_front[%i] = {', table_size);
for idx = 1:table_size
    fprintf(num2str(f_front(idx)));
    if idx < table_size
        fprintf(',');
    end
end
fprintf('};\n');