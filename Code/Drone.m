classdef Drone < handle
   properties
       nTypes = 1; % Types of drones (1 means homogenous swarm)
       batteryTime = 20*60; % Battery time [s]
       capacity = 2; % Capacity of each drone [number of nodes each drone can carry]
       nDrones = 4; % Number of drones present in the fleet
       speed = 15; % Average speed of drone [m/s]
   end
   methods
       
   end
end