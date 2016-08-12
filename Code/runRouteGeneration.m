%% runRouteGeneration.m
% 
% This file enumerates all feasible routes (satisfying capacity and 
% battery time constraints).

%% Initialize Drone and Graph structures
G = Graph();
for ct = 1:size(C,1)
    G.add_vertex(ct,C(ct,1),C(ct,2));
end

%% Computation of distance associated with each edge in the graph
Dist = M*eye(size(C,1));
Vk_g = eye(size(C,1)); % Ground speed (Vk) expressed in local ground frame (g)
% Note that Vk_g is not a symmetric matrix but Dist is

Va = D.speed; % Average airspeed of the drone
Vwx = Vw_g(1); % Wind speed in x-direction
Vwy = Vw_g(2); % Wind speed in y-direction

for row = 1:size(C,1)
    for col = row+1:size(C,1)
        Dist(row,col) = sqrt((C(row,1)-C(col,1))^2+(C(row,2)-C(col,2))^2);
        theta = atan2(C(row,2)-C(col,2), C(row,1)-C(col,1));
        Vk_g(col,row) = abs((Vwx^2*cos(theta)^2 - Vwy^2*cos(theta)^2 + Va^2 - Vwx^2 + Vwx*Vwy*sin(2*theta))^(1/2) + Vwx*cos(theta) + Vwy*sin(theta));
        Vk_g(row,col) = abs(Vwx*cos(theta) - (Vwx^2*cos(theta)^2 - Vwy^2*cos(theta)^2 + Va^2 - Vwx^2 + Vwx*Vwy*sin(2*theta))^(1/2) + Vwy*sin(theta));
    end
end
Dist = (Dist+Dist'); % It is a symmetric matrix

Time = Dist./Vk_g; % Time it will take to travel from one node to another
%% Routes enumeration satisying capacity constraints
 
t = []; % Row-vector containing total time of each route (reffered to as weights in the report)
aa = []; % Matrix generated to keep track of the order of visit to the customers in a route (needed to differentiate between routes such as 0 2 3 4 0 from 0 3 2 4 0)

% Note that aa(i,j) > 0 if route j visits customer i

for k = 1:D.capacity % For each possible drone capacity, set of routes are generated
    nPk = permn(2:G.nVertices,k); % Create all possible permutations of choosing k vertices out of 2:G.nVertices
%     nPk = nchoosek(2:G.nVertices,k); % Create all possible combinations of choosing k vertices out of 2:G.nVertices

    % Column-wise calculation of Equality constraint matrix (i.e., for each
    % route)
    dummy1 = zeros(size(C,1),size(nPk,1));
    for ct = 1:size(nPk,1)
        dummy1(nPk(ct,:),ct) = 1:k;
    end
    
    
%     % Row-wise calculations (much smaller for loop)
%     dummy2 = Dist(nPk(:,1))';
%     for ct = 1:size(nPk,2)-1 % because size(nPk,2)<=size(C,1)
%         dummy2 = dummy2+Dist((nPk(:,ct)-1)*size(C,1)+nPk(:,ct+1))';
%     end
%     dummy2 = dummy2 + Dist((nPk(:,end)-1)*size(C,1)+1)'; % Calculates the total distance of all routes enumerated for a particular drone capacity
%     dummy2 = (dummy2/D.speed); % Total time of travel for each route
    
    % Row-wise calculations (much smaller for loop)
    dummy2 = Time((nPk(:,1)-1)*size(C,1)+1)';
    for ct = 1:size(nPk,2)-1 % because size(nPk,2)<=size(C,1)
        dummy2 = dummy2+Time(sub2ind(size(Time),nPk(:,ct),nPk(:,ct+1)))';
    end
    dummy2 = dummy2 + Time(nPk(:,end))'; % Calculates the total distance of all routes enumerated for a particular drone capacity
    
    % Checking Battery-time constraints
    idx = dummy2>D.batteryTime;
    dummy2(idx) = []; % Eliminating routes which violate battery-time constraints
    dummy1(:,idx) = []; % Eliminating routes which violate battery-time constraints
    
    dummy2 = dummy2 + td + k*tdrop; % Calculates the total "route time" for all routes enumerated for a particular drone capacity
    
    aa = [aa dummy1];
    t = [t dummy2];
end
aa(1,:)=[];

a = zeros(size(aa));
a(aa>0)=1; % a(i,j) = 1 if route j visits customer i


clear dummy1 dummy2 nPk idx;