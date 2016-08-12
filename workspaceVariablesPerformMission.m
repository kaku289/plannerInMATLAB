clc; clear;
load('plannedRoutes.mat');
%% Required Inputs
depot = [51.9908873	4.3782441;
         51.9908873	4.3782441;
         51.9908873	4.3782441;
         51.9908873	4.3782441];
     
%%
nv = length(nk); % No. of vehicles
listDestinations = Destinations;
C_lla(1,:) = [];
% C_lla = round(C_lla*10^7)/10^7;

for ct=1:nv
    listDestinations{ct} = C_lla(Destinations{ct}(Destinations{ct}~=0),:);
end

destinations1 = [depot(1,:);
                listDestinations{1}];
            
destinations2 = [depot(2,:);
                listDestinations{2}];      
            
destinations3 = [depot(3,:);
                listDestinations{3}];
            
destinations4 = [depot(4,:);
                listDestinations{4}];
            
Q = 3;  
wp_ids = [4 5 6 7];
