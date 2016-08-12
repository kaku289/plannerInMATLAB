%%
clc; clear; 

%% Required Inputs
points = [51.9913069	4.3782904;
          51.9907219	4.3787221]; % [lat lon] of two end points
      
nCustomers = 36; % Number of customers to be created including the above two points

depot = [51.9909563 	4.3781332]; % [lat lon] of the depot

%% Compute intermediate points from the end points
      
E = wgs84Ellipsoid;
p0 = points(1,:);

[xEast,yNorth,~] = geodetic2enu(points(:,1),points(:,2),0,p0(1),p0(2),0,E);

dist = sqrt(diff(xEast).^2+diff(yNorth).^2)/(nCustomers-1);
theta = atan2(diff(yNorth), diff(xEast));

dx = dist*cos(theta);
dy = dist*sin(theta);

C = zeros(nCustomers,2);
C(1,:) = [xEast(1) yNorth(1)];
C(end,:) = [xEast(2) yNorth(2)];

for i=2:nCustomers-1
    C(i,:) = C(i-1,:)+ [dx dy];
end

[lat,lon,~] = enu2geodetic(C(:,1),C(:,2),0,p0(1),p0(2),0,E);

%% Create file containing ENU coordinates of the points (to be used for the purpose of the optimization)
C_lla = [depot; [lat lon]];
[xEast,yNorth,zUp] = geodetic2enu(C_lla(:,1),C_lla(:,2),0,C_lla(1,1),C_lla(1,2),0,E);

fileID = fopen('SS_test_enu.txt','w');
fprintf(fileID,'%12.7f %12.7f\n',[xEast,yNorth]');
fclose(fileID);


fileID = fopen('SS_test_lla.txt','w');
fprintf(fileID,'%12.7f %12.7f\n',C_lla');
fclose(fileID);