% Creates sample data for different problems
clc; clear;
nk = [5;4]; % Number of jobs/routes assigned to each vehicle
td = 4; % time units spent at the depot
T = 60;
wFinishTimes = [9*ones(1,nk(1)); 9*ones(1,nk(2)-1), 14, 0];
save('solution_uncogestion_sample');