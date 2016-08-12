%% runMTVRP.m
% 
% This file computes route assignment to m vehicles each of capacity k 
% while minimizing the maximum journey time using MILP.
clc; clear; close all;
%% Add CPLEX path
addpath('E:\Program Files\IBM\ILOG\CPLEX_Studio126\cplex\matlab\x64_win64');

%% Initialize the scenario
Scene;

%% Create routes
runRouteGeneration;
% runHeuristicRouteGeneration;

%% Define some variables
T = 3600; % Time-horizon
tol = 0.001; % Tolerance

%% Declaration of variables
nR = length(t); % Number of routes
nCustomers = size(a,1); % Number of customers
m = D.nDrones; % Number of drones

%% Objective function (quantity to be minimized)
f = [zeros(nR*m,1);1]; %[x...,t_bar]

%% Formulation of constraints

% Integer constraints
% % For MATLAB intlinprog solver
intcon = [1:nR*m];
% % For CPLEX Solver
ctype(1:nR*m) = 'I';
ctype(1+nR*m) = 'C';

% Equality constraints
% Aeq = [repmat(a,1,m) zeros(nCustomers,1)]; %% Don't use repmat, its an
% extremely slow function
Aeq = [kron(ones(1,m),a) zeros(nCustomers,1)];
beq = ones(nCustomers,1);

% Inequality constraints
dummy = kron(eye(m),t);
A1 = [dummy zeros(m,1)];
b1 = T*ones(m,1);

A2 = [dummy -1*ones(m,1)];
b2 = zeros(m,1);

A = [A1;A2];
b = [b1;b2];

%% Bounds
lb = zeros(nR*m+1,1);
ub = [ones(nR*m,1); sum(t)];

%% Solving MILP
% options = optimoptions('intlinprog','IPPreprocess','advanced','MaxTime',300);
% options.AbsoluteGapTolerance = 30;
% options.RelativeGapTolerance = 0.01;
% x = intlinprog(f,intcon,A,b,Aeq,beq,lb,ub,options);

% % With CPLEX
options=cplexoptimset;
options.Display='on';
options.MaxTime=500;
options.parameter2009=.01; % Relative MILP gap teolerance
options.parameter2008=30; % Absolute MILP gap tolerance
% tic;
[x, fval, exitflag, output] = cplexmilp(f, A, b, Aeq, beq,...
      [ ], [ ], [ ], lb, ub, ctype, [ ], options);
display('Time taken for computation (s)');
% display(toc);
%% Plotting - 1

% Plots the depot and customer's location
plotID = 1000;
ax1 = figure(plotID);
sD = scatter(C(1,1),C(1,2),200,'d','MarkerFaceColor',[1 0 0]); hold on; grid;
sC = scatter(C(2:end,1),C(2:end,2),100,'MarkerEdgeColor',[0 .5 .5],...
              'MarkerFaceColor',[0 .7 .7],...
              'LineWidth',2);
set(gca, 'FontSize', 18);
legend([sD sC],{'Depot','Node sites'});
ylabel('Y (m)', 'FontSize', 16);
xlabel('X (m)', 'FontSize', 16);
title('Location of the truck (depot) and node deployment sites (customers)','FontSize', 14);
atext = [0:size(a,1)]'; btext = num2str(atext); ctext = cellstr(btext);
dx = -1; dy = -1; % displacement so the text does not overlay the data points
text(C(:,1)+dx, C(:,2)+dy, ctext,'Color',[0 0.6 0],'FontSize',14);

%% Plotting - 2
T = ceil(x(end)); % Maximum "ceiled" journey time

% Creating weight matrix for all vehicles
X = round(reshape(x(1:end-1),[nR m]))'; % Soution matrix
nR_max = (max(sum(X,2))); % Maximum number of routes assigned to a vehicle
w = zeros(m, 2*nR_max);
wFinishTimes = zeros(m, 2*nR_max);

journeyTimes = zeros(m,1); % Total Journey time for each vehicle

depotTimes = []; % Time instances for which the vehicles are present at the depot (To compute congestion)
for k=1:m
    ct_route = find(abs(X(k,:)-1)<=tol); 
    finishTime = t(ct_route);
    arriveAtDepot = finishTime-td;
    w(k,1:2*length(ct_route)) = reshape([arriveAtDepot; td*ones(1,length(ct_route))],1,2*length(ct_route));
    wFinishTimes(k,1:length(ct_route)) = finishTime;
    
    % Total journey time for each vehicle
    journeyTimes(k) = sum(finishTime);
    
    % To compute congestion
    cumFinishTime = cumsum(finishTime);
    dummy = kron(ones(1,td+1), cumFinishTime(1:end-1)')+kron(ones(length(finishTime)-1,1),[0:-1:-td]);
    depotTimes = [depotTimes; dummy(:)];
end
colorMatrix = ones(2*nR_max,3);%linspecer(m); % To generate distinguishable colors
colorMatrix(2:2:end,2:3) = 0; % Red color of time spent at the depot

plotID = 1010;
figure(plotID);
ax1 = subplot(2,1,1);
H = plotWorkDist(ax1, w, colorMatrix);
set(gca, 'FontSize', 18);
ylabel('Vehicles', 'FontSize', 16);
title('Route distribution for different vehicles','FontSize', 16);
xlim([0,T]);
l = cell(1,2);
l{1} = 'Flying+Delivering'; l{2} = 'Servicing (at depot)';
legend(H,l);

% Find congestion

ax2 = subplot(2,1,2);
binEdges = 0:1:max(depotTimes)+10;
if ~isempty(depotTimes)
    h = histogram(depotTimes, binEdges);
end
set(gca, 'FontSize', 18);
xlabel('Time (s)', 'FontSize', 16);
ylabel('# of vehicles at depot', 'FontSize', 16);
xlim([0,T]);
h.EdgeColor = 'none';
h.FaceColor = [0.15 0.5 0];
% h.EdgeAlpha = 0.1;
% N = h.Values; % Gives count in each bin

%% Solution display
nk = sum(X,2); % Number of jobs/routes assigned to each vehicle
% dummy_a = [aa; ones(1,nR)];
for ct=1:size(nk,1) % For each vehicle
    ct_route = find(abs(X(ct,:)-1)<=tol); % Indexes for routes which are assigned to vehicle 'ct'
    dummy = aa(:,ct_route);
    [~,idx] = sort(dummy,1);
    nodes_list = [0];
    for ct1=1:length(ct_route) % For each route
        nodes_list = [nodes_list; idx(end-sum(a(:,ct_route(ct1)))+1:end,ct1); 0];
    end
%     [nodes_list,~] = find(dummy>0);
%     nodes_list(nodes_list==size(a,1)+1) = 0; % Replacing the depot with zero
    
    % Nodes are now 
    
    disp(strcat('---- Vehicle ',num2str(ct),' ----'));
    disp(nodes_list');
end
disp('---- Maximum Journey Time (s) ----');
disp(x(end));

%% Saving Solution
save('solution_MTVRP');

%% Plot for Report
% figure(111);
% ax1 = subplot(2,1,2);
% H = plotWorkDist(ax1, w, colorMatrix);
% set(gca, 'FontSize', 18);
% ylabel('Vehicles', 'FontSize', 16);
% title('Route distribution for different vehicles','FontSize', 16);
% xlim([0,T]);
% l = cell(1,2);
% l{1} = 'Flying+Delivering'; l{2} = 'Servicing (at depot)';
% legend(H,l);
% xlabel('Time (s)', 'FontSize', 16);
% 
% subplot(2,1,1);
% sD = scatter(C(1,1),C(1,2),200,'d','MarkerFaceColor',[1 0 0]); hold on; grid;
% sC = scatter(C(2:end,1),C(2:end,2),100,'MarkerEdgeColor',[0 .5 .5],...
%               'MarkerFaceColor',[0 .7 .7],...
%               'LineWidth',2);
% set(gca, 'FontSize', 18);
% legend([sD sC],{'Depot','Node sites'});
% ylabel('Y (m)', 'FontSize', 16);
% xlabel('X (m)', 'FontSize', 16);
% title('Location of the truck (depot) and node deployment sites (customers)','FontSize', 14);
% atext = [0:size(a,1)]'; btext = num2str(atext); ctext = cellstr(btext);
% dx = -2; dy = -5.5; % displacement so the text does not overlay the data points
% text(C(:,1)+dx, C(:,2)+dy, ctext,'Color',[0 0.6 0],'FontSize',14);
