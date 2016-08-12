% This script file runs the code to minimize the congestion at the depot
% using MILP. The problem is formulated so as to have minimum
% number of vehicles being present at the depot at same time instant.

clc; clear; % close all;

%% Add CPLEX path
addpath('E:\Program Files\IBM\ILOG\CPLEX_Studio126\cplex\matlab\x64_win64');

%%
M = 10000; % A large number
delta_t = 15; % Size of the time-interval in which minimization of maximum number of vehicles present simultaneously at the depot is to be done.
load('solution_MTVRP','T','nk','wFinishTimes','td','journeyTimes');
% load('solution_uncogestion_sample');
nI = ceil(T/delta_t); % Number of time-intervals
T = nI*delta_t; % Maximum journey time

solutionDisplay = 1;
% nk = [10;9]; % Number of jobs/routes assigned to each vehicle

% td = 4; % time units spent at the depot

%% Calculation of some more useful variables
dummy = wFinishTimes';
t = dummy(dummy>0)'; % time of each route listed in vehicle order (ROW VECTOR)

nv = length(nk); % Number of vehicles (=length(nk))
nr = sum(nk); % Number of routes

nx = sum(nk.*nk); % Number of x (assignment) variables
nu = nx+(nr*nI)+nr+1; % Number of all unknowns

%% Objective function (quantity to be minimized)
% Unknowns - [x^1_11 x^1_12 x^1_21 x^1_22 x^2_11 y^1_1,1... y^1_1,24 y^2_2,1... y^1_2,24 y^2_1,1... y^2_1,24 c^1_1 c^1_2 c^2_1 n_bar]
f = [zeros(nx,1);zeros(nr*nI,1);zeros(nr,1);1]; 

%% Constraints

% Integer constraints
intcon = [1:nx+nr*nI]; % For MATLAB
ctype(1:nu) = 'C'; % For CPLEX
ctype(1:nx+nr*nI) = 'I';

% Assignment constraints
Aeq1 = zeros(sum(nk*2),nu);
for ct=1:nv % For each vehicle
    ct_row = sum(2*nk(1:ct-1)); % Row count
    ct_col = sum(nk(1:ct-1).*nk(1:ct-1)); % Column count
    
    % Sum of rows should be 1
    Aeq1(ct_row+1:ct_row+nk(ct),ct_col+1:ct_col+nk(ct)*nk(ct)) = kron(eye(nk(ct)),ones(1,nk(ct)));
    
    % Sum of columns should be 1
    Aeq1(ct_row+nk(ct)+1:ct_row+2*nk(ct),ct_col+1:ct_col+nk(ct)*nk(ct)) = repmat(eye(nk(ct)),1,nk(ct));
end
beq1 = ones(sum(nk*2),1);

% Completion time constraints
Aeq2 = zeros(nr,nu);
for ct=1:nv % For each vehicle
    ct_row = sum(nk(1:ct-1)); % Row count in Aeq1 matrix
    ct_col = sum(nk(1:ct-1).*nk(1:ct-1)); % Column count in Aeq1 matrix
    
    Aeq2(ct_row+1:ct_row+nk(ct),ct_col+1:ct_col+nk(ct)*nk(ct)) = kron(t(ct_row+1:ct_row+nk(ct)),tril(ones(nk(ct),nk(ct))));
end
Aeq2(:,nx+(nr*nI)+1:nx+(nr*nI)+nr) = -eye(nr);
beq2 = zeros(nr,1);

% Inequality constraints
A_lhs = zeros(nr*nI,nu);
A_rhs = zeros(nr*nI,nu);
for ct=1:nr
    % LHS constraints
    A_lhs((ct-1)*nI+1:ct*nI,nx+(ct-1)*nI+1:nx+(ct)*nI) = M*eye(nI);
    A_lhs((ct-1)*nI+1:ct*nI,nx+(nr*nI)+ct) = -1;
    
    % RHS constraints
    A_rhs((ct-1)*nI+1:ct*nI,nx+(ct-1)*nI+1:nx+(ct)*nI) = M*eye(nI);
    A_rhs((ct-1)*nI+1:ct*nI,nx+(nr*nI)+ct) = 1;
end
lhs = M*ones(nI,1)-delta_t*[0:nI-1]';
rhs = (M+td)*ones(nI,1)+delta_t*[1:nI]';
b_lhs = repmat(lhs,nr,1);
b_rhs = repmat(rhs,nr,1);

% Equality constraints on y variables
Aeq3 = zeros(nr,nu);
Aeq3(:,nx+1:nx+nr*nI) = kron(eye(nr),ones(1,nI));
beq3 = (floor(td/delta_t)+1)*ones(nr,1);


% Inequality constraint due to max operation in objective function
Aineq = zeros(nI,nu);
for ct=1:nv
    Aineq(:,nx+sum(nk(1:ct-1))*nI+1:nx+(sum(nk(1:ct))-1)*nI) = kron(ones(1,nk(ct)-1),eye(nI));
end
Aineq(:,end)=-1;
bineq = zeros(nI,1);

%% Collect all inequality constraints
A = [A_lhs;A_rhs;Aineq];
b = [b_lhs;b_rhs;bineq];

%% Collect all equality constraints
Aeq = [Aeq1;Aeq2;Aeq3];
beq = [beq1;beq2;beq3];

%% Lower and Upper bounds
lb = [zeros(nu-1,1); 1];
ub = [ones(nx+nr*nI,1); T*ones(nr,1); nv];

%% Solving the posed problem
% x = intlinprog(f,intcon,A,b,Aeq,beq,lb,ub);

% With CPLEX
options=cplexoptimset;
options.Display='on';
options.MaxTime=300;
options.parameter2009=.05; % Relative MILP gap teolerance
% options.parameter2008=50; % Absolute MILP gap tolerance
[x, fval, exitflag, output] = cplexmilp(f, A, b, Aeq, beq,...
      [ ], [ ], [ ], lb, ub, ctype, [ ], options);

  
%% Solution display
if solutionDisplay==1
    load('solution_MTVRP','X','aa','tol','nR');
%     dummy_a = [aa; ones(1,nR)];
    for ct=1:size(nk,1) % For each vehicle
        ct_route = find(abs(X(ct,:)-1)<=tol);
        dummy = aa(:,ct_route);
        
        ct_x = sum(nk(1:ct-1).*nk(1:ct-1));
        ct_col = nk(ct);
        x_mat = (reshape(x(ct_x+1:ct_x+ct_col*ct_col),ct_col,ct_col))';
        rearrangedRoutes = dummy*round(x_mat);
        
        [~,idx] = sort(rearrangedRoutes,1);
        nodes_list = [0];
        nCustomers = sum(rearrangedRoutes>0,1);
        for ct1=1:length(ct_route) % For each route 
            nodes_list = [nodes_list; idx(end-nCustomers(ct1)+1:end,ct1); 0];
        end
%         [nodes_list,~] = find(rearrangedRoutes==1);
%         nodes_list(nodes_list==size(a,1)+1) = 0; % Replacing the last row number of a matrix with depot notation '0'
        disp(strcat('---- Vehicle ',num2str(ct),' ----'));
        disp(nodes_list');
    end
%     display('--- x ----');
%     display(x(1:nx)')
%     % reshape(x(1:nx),[nr 2])'
%     display('--- n_bar ----');
%     display((x(end))')
end

%% Plotting
m = max(nk); % Maximum number of routes assigned to a vehicle

% Creating weight matrix before clearing congestion
w_pre = zeros(nv,2*m);
C_pre = ones(2*m,3);%linspecer(m); % To generate distinguishable colors
C_pre(2:2:end,2:3) = 0; % Red color of time spent at the depot
for ct=1:nv
    ct_row = sum(nk(1:ct-1));
    ct_col = nk(ct);
    finishTime = t(ct_row+1:ct_row+ct_col);
    arriveAtDepot = finishTime-td;
    w_pre(ct,1:2*ct_col) = reshape([arriveAtDepot; td*ones(1,ct_col)],1,2*ct_col);
end

% Creating weight matrix after minimizing congestion
w_post = zeros(nv,m);
C_post = (C_pre);
wFinishTimes_shuffled = zeros(nv,m);

depotTimes = []; % Time instances the vehicles are present at the depot (To compute congestion)
for ct=1:nv
    ct_x = sum(nk(1:ct-1).*nk(1:ct-1));
    ct_row = sum(nk(1:ct-1));
    ct_col = nk(ct);
    x_mat = (reshape(x(ct_x+1:ct_x+ct_col*ct_col),ct_col,ct_col))';
    finishTime = t(ct_row+1:ct_row+ct_col)*x_mat;
    arriveAtDepot = finishTime-td;
    w_post(ct,1:2*ct_col) = reshape([arriveAtDepot; td*ones(1,ct_col)],1,2*ct_col); 
    
    % To save shuffled route lengths
    wFinishTimes_shuffled(ct,1:ct_col) = finishTime;
    
    % To compute congestion
    cumFinishTime = cumsum(finishTime);
    dummy = kron(ones(1,td+1), cumFinishTime(1:end-1)')+kron(ones(length(finishTime)-1,1),[0:-1:-td]);
    depotTimes = [depotTimes; dummy(:)];
end
plotID = 1020;
figure(plotID);
ax1 = subplot(2,1,1);
plotWorkDist(ax1, w_pre, C_pre);
set(gca, 'FontSize', 18);
ylabel('Vehicles', 'FontSize', 16);
title('Before clearing congestion at the depot','FontSize', 16);

ax2 = subplot(2,1,2);
H = plotWorkDist(ax2, w_post, C_post);
set(gca, 'FontSize', 18);
ylabel('Vehicles', 'FontSize', 16);
xlabel('Time (s)', 'FontSize', 16);
% set(findobj('type','axes'),'fontsize',18)
% xt = get(gca, 'XTick');
title('After clearing congestion at the depot', 'FontSize', 16);
l = cell(1,2);
l{1} = 'Flying+Delivering'; l{2} = 'Servicing (at depot)';
legend(H,l);

%% Another plot of congestion at the depot
plotID = 1030;
figure(plotID);
ax1 = subplot(2,1,1);
H = plotWorkDist(ax1, w_post, C_post);
set(gca, 'FontSize', 18);
ylabel('Vehicles', 'FontSize', 16);
% xlabel('Time', 'FontSize', 16);
% set(findobj('type','axes'),'fontsize',18)
% xt = get(gca, 'XTick');
% title('After clearing congestion at the depot', 'FontSize', 16);
xlim([0,T]);
l = cell(1,2);
l{1} = 'Flying+Delivering'; l{2} = 'Servicing (at depot)';
legend(H,l);

ax2 = subplot(2,1,2);
binEdges = 0.5:1:max(depotTimes)+10;
h = histogram(depotTimes, binEdges);
set(gca, 'FontSize', 18);
xlabel('Time (s)', 'FontSize', 16);
ylabel('# of vehicles at depot', 'FontSize', 16);
xlim([0,T]);
h.EdgeColor = 'none';
h.FaceColor = [0.15 0.5 0];
% N = h.Values; % Gives count in each bin

%% Saving Solution
save('solution_Uncongestion');
