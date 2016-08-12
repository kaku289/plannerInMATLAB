%% Find end point coordinates for wind and average airspeed estimation

angleWithXaxis = 16*pi/180;
p2 = [-2 2]; % [x y] in meters
Dist = 15; % in meters

[p2(1)+Dist*cos(angleWithXaxis) p2(2)+Dist*sin(angleWithXaxis)]
[p2(1)-Dist*cos(angleWithXaxis) p2(2)-Dist*sin(angleWithXaxis)]

%% Calculation of wind and average airspeed
t1 = 8.05; % in s
t2 = 8.05; % in s
V_K1 = Dist/t1;
V_K2 = Dist/t2;
Vavg = (V_K1 + V_K2)/2 % in m/s
Vwind = abs(V_K1 - V_K2)/2 % in m/s