% This script file runs the code to minimize the congestion at the depot
% using MILP. The problem is formulated so as to have minimum
% number of vehicles being present at the depot at the same time instant.
% This script uses ONLY slacking to minimize the congestion.

clc; clear; % close all;

M = 10000; % A large number
delta_t = 15; % Size of the time-interval in which minimization of the maximum number of vehicles at the depot is to be done.
load('solution_Uncongestion','T','nk','wFinishTimes_shuffled','td','journeyTimes');
% load('solution_uncogestion_sample');
timeLeverage = 1000; % Additional time leverage on top of the maximum journey time to minimize the congestion at the depot
coef_congestion = 1000;
coef_journeyTime = 1;
maxPersons = 1;

nI = ceil((T+timeLeverage)/delta_t); % Number of time-intervals
T = nI*delta_t; % Maximum journey time

solutionDisplay = 1;

%% Calculation of some more useful variables
dummy = wFinishTimes_shuffled';
t = dummy(dummy>0)'; % time of each route listed in vehicle order (ROW VECTOR) after shuffling

nv = length(nk); % Number of vehicles (=length(nk))
nr = sum(nk); % Number of routes

n_st = nr; % Number of slack time variables
nu = (nr*nI)+nr+1+n_st+1; % Number of all unknowns

% % Unknowns % %
% % nr*nI - Number of y variables
% % nr - Number of completion time variables
% % 1 - It corresponds to n_bar
% % n_st - Number of slack time variables
% % 1 - it corresponds to c_bar
% % % % % % % % %

ub_sumSlackTimes = T-journeyTimes; % Upper bound on sum of slack times for each vehicle
% ub_sumSlackTimes = max(journeyTimes)-journeyTimes; % Upper bound on sum of slack times for each vehicle

ub_slackTimes = zeros(n_st,1); % Upper bound on slack time of every route
for ct=1:nv
    ub_slackTimes(sum(nk(1:ct-1))+1:sum(nk(1:ct))-1) = ub_sumSlackTimes(ct);
    % Note that the upper bound of last route in each journey is forced to
    % be zero as slack time introduction in the last route doesn't help in
    % reduction of congestion.
end

%% Objective function (quantity to be minimized)
% Unknowns - [y^1_1,1... y^1_1,24 y^1_2,1... y^1_2,24 y^2_1,1... y^2_1,24 c^1_1, c^1_2, c^2_1, n_bar, st^1_1, st^1_2, st^2_1, c_bar]
f = [zeros(nr*nI,1);zeros(nr,1);coef_congestion;zeros(nr,1);coef_journeyTime]; 

%% Constraints

% Integer constraints
intcon = [1:nr*nI]; % For MATLAB
ctype(1:nu) = 'C'; % For CPLEX
ctype(1:nr*nI) = 'I';

% Completion time constraints (c-s=t)
Aeq2 = zeros(nr,nu);
beq2 = zeros(nr,1);
for ct=1:nv % For each vehicle
    ct_row = sum(nk(1:ct-1)); % Row count in Aeq2 matrix
        
    % Filling Aeq2 matrix corresponding to slack time variables
    ct_col = (nr*nI)+nr+1+sum(nk(1:ct-1));
    Aeq2(ct_row+1:ct_row+nk(ct),ct_col+1:ct_col+nk(ct)) = -tril(ones(nk(ct),nk(ct)));
    
    % Filling beq2 matrix
    beq2(ct_row+1:ct_row+nk(ct),1) = cumsum(t(ct_row+1:ct_row+nk(ct)))';
end
% Filling Aeq2 matrix corresponding to completion time variables
Aeq2(:,(nr*nI)+1:(nr*nI)+nr) = eye(nr);

% Inequality constraints
A_lhs = zeros(nr*nI,nu);
A_rhs = zeros(nr*nI,nu);
for ct=1:nr
    % LHS constraints
    A_lhs((ct-1)*nI+1:ct*nI,(ct-1)*nI+1:(ct)*nI) = M*eye(nI);
    A_lhs((ct-1)*nI+1:ct*nI,(nr*nI)+ct) = -1;
    
    % RHS constraints
    A_rhs((ct-1)*nI+1:ct*nI,(ct-1)*nI+1:(ct)*nI) = M*eye(nI);
    A_rhs((ct-1)*nI+1:ct*nI,(nr*nI)+ct) = 1;
end
lhs = M*ones(nI,1)-delta_t*[0:nI-1]';
rhs = (M+td)*ones(nI,1)+delta_t*[1:nI]';
b_lhs = repmat(lhs,nr,1);
b_rhs = repmat(rhs,nr,1);

% Equality constraints on y variables
Aeq3 = zeros(nr,nu);
Aeq3(:,1:nr*nI) = kron(eye(nr),ones(1,nI));
beq3 = (floor(td/delta_t)+1)*ones(nr,1);


% Inequality constraint due to max operation (w.r.t n_bar) in objective function
Aineq = zeros(nI,nu);
for ct=1:nv
    Aineq(:,sum(nk(1:ct-1))*nI+1:(sum(nk(1:ct))-1)*nI) = kron(ones(1,nk(ct)-1),eye(nI));
end
Aineq(:,(nr*nI)+nr+1)=-1;
bineq = zeros(nI,1);


% Inequality constraint on sum of slack times for each vehicle
Aineq2 = zeros(nv,nu);
for ct=1:nv
    ct_col = (nr*nI)+nr+1+sum(nk(1:ct-1));
    Aineq2(ct,ct_col+1:ct_col+nk(ct)) = ones(1,nk(ct));
end
bineq2 = ub_sumSlackTimes;


% Inequality constraint due to max operation (w.r.t c_bar) in objective function
Aineq3 = zeros(nv,nu);
for ct=1:nv
    ct_col = (nr*nI)+sum(nk(1:ct));
    Aineq3(ct,ct_col) = 1;
end
Aineq3(:,(nr*nI)+nr+1+n_st+1)=-1;
bineq3 = zeros(nv,1);

%% Collect all inequality constraints
A = [A_lhs;A_rhs;Aineq;Aineq2;Aineq3];
b = [b_lhs;b_rhs;bineq;bineq2;bineq3];

%% Collect all equality constraints
Aeq = [Aeq2;Aeq3];
beq = [beq2;beq3];

%% Lower and Upper bounds
lb = [zeros((nr*nI),1); beq2; 1; zeros(nr,1); max(journeyTimes)];
ub = [ones(nr*nI,1); T*ones(nr,1); maxPersons; ub_slackTimes; T];
% Uncomment the below line to prevent use of slack times
% ub = [ones(nr*nI,1); T*ones(nr,1); nv; zeros(nr,1)] 

%% Solving the posed problem
% x = intlinprog(f,intcon,A,b,Aeq,beq,lb,ub);

% With CPLEX
options=cplexoptimset;
options.Display='on';
options.MaxTime=500;
options.parameter2009=.05;
options.parameter2008=100;
[x_slacked, fval, exitflag, output] = cplexmilp(f, A, b, Aeq, beq,...
      [ ], [ ], [ ], lb, ub, ctype, [ ], options);

  
%% Solution display
if solutionDisplay
    load('solution_Uncongestion','X','x','aa','tol','nR','w_pre', 'C_pre', 'w_post', 'C_post');
    % Pre - Before clearing congestion at the depot
    % Shuffled - After clearing congestion at the depot via runUncongestion.m
    % post - After clearing congestion at the depot via runSlacking.m
    w_shuffled = w_post;
    C_shuffled = C_post;
    Destinations = {};%zeros(nv,ceil(size(w_shuffled,2)/2)*4);
    
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
        Destinations{ct} = nodes_list;
%         [nodes_list,~] = find(rearrangedRoutes==1);
%         nodes_list(nodes_list==size(a,1)+1) = 0; % Replacing the last row number of a matrix with depot notation '0'
        disp(strcat('---- Vehicle ',num2str(ct),' ----'));
        disp(nodes_list');
    end
end

% x_slacked(nr*nI+nr+2:nr*nI+2*nr+1) = [25.5648;0;0;0;44.8930;0;14.8930;0];
%% Plotting
m = max(nk); % Maximum number of routes assigned to a vehicle

% Creating weight matrix after minimizing congestion
w_post = zeros(nv,3*m); % corresponding to [flying time, time at the depot, slack time]
C_post = ones(3*m,3); % Color matrix for plot
C_post(3:3:end,2:3) = 0; % Red color for time spent at the depot
C_post(1:3:end,1:2) = 0; % Blue color for slack time

depotTimes = []; % Time instances the vehicles are present at the depot (To compute congestion)
for ct=1:nv % For each vehicle
    ct_x = sum(nk(1:ct-1).*nk(1:ct-1));
    ct_row = sum(nk(1:ct-1));
    ct_col = nk(ct);
    w_i = t(ct_row+1:ct_row+ct_col); % Weight of each route (flying time + dropping time + service time)
    arriveAtDepot = w_i-td; % flying time + dropping time for each 
    
    ct_st = (nr*nI)+nr+1+sum(nk(1:ct-1)); % count for slack time access in the solution vector x_slacked
    slackTimes = x_slacked(ct_st+1:ct_st+nk(ct))';
    
    w_post(ct,1:3*ct_col) = reshape([slackTimes; arriveAtDepot; td*ones(1,ct_col)],1,3*ct_col); 
    
    
    % To compute congestion
    finishTime = w_i + slackTimes;
    cumFinishTime = cumsum(finishTime);
    dummy = kron(ones(1,td+1), cumFinishTime(1:end-1)')+kron(ones(length(finishTime)-1,1),[0:-1:-td]);
    
%     depotTimes = [depotTimes; dummy(:)]; 
    % % Discarding points corresponding to finishing of service at the depot for plotting
    dummy = dummy(:,2:end);
    depotTimes = [depotTimes; dummy(:)]; 
end

% Max limit of x-axis
apX = max(sum(w_post,2)) + 50;

plotID = 4020;
figure(plotID);
ax1 = subplot(3,1,1);
plotWorkDist(ax1, w_pre, C_pre);
set(gca, 'FontSize', 18);
ylabel('Vehicles', 'FontSize', 16);
title('Before clearing congestion at the depot','FontSize', 16);
xlim([0 apX]);

ax2 = subplot(3,1,2);
plotWorkDist(ax2, w_shuffled, C_shuffled);
set(gca, 'FontSize', 18);
ylabel('Vehicles', 'FontSize', 16);
title('After clearing congestion at the depot (shuffling)','FontSize', 16);
xlim([0 apX]);

ax3 = subplot(3,1,3);
H = plotWorkDist(ax3, w_post, C_post);
set(gca, 'FontSize', 18);
ylabel('Vehicles', 'FontSize', 16);
xlabel('Time (s)', 'FontSize', 16);
% set(findobj('type','axes'),'fontsize',18)
% xt = get(gca, 'XTick');
title('After clearing congestion at the depot (slacking)', 'FontSize', 16);
xlim([0 apX]);
l = cell(1,3);
l{1} = 'Slacking'; l{2} = 'Flying+Delivering'; l{3} = 'Servicing (at depot)';
legend(H,l);

%% Another plot of congestion at the depot
plotID = 4030;
figure(plotID);
ax1 = subplot(2,1,1);
H = plotWorkDist(ax1, w_post, C_post);
set(gca, 'FontSize', 18);
ylabel('Vehicles', 'FontSize', 16);
% xlabel('Time', 'FontSize', 16);
% set(findobj('type','axes'),'fontsize',18)
% xt = get(gca, 'XTick');
title('After clearing congestion at the depot (slacking)', 'FontSize', 16);
xlim([0,apX]);
l = cell(1,3);
l{1} = 'Slacking'; l{2} = 'Flying+Delivering'; l{3} = 'Servicing (at depot)';
% legend(H,l);

ax2 = subplot(2,1,2);
binEdges = 0.5:1:max(depotTimes)+10;
h = histogram(depotTimes, binEdges);
set(gca, 'FontSize', 18);
xlabel('Time (s)', 'FontSize', 16);
ylabel('# of vehicles at depot', 'FontSize', 16);
xlim([0,apX]);
h.EdgeColor = 'none';
h.FaceColor = [0.15 0.5 0];
% N = h.Values; % Gives count in each bin

saveas(plotID,'plannedRoutes.png')
%% Saving Solution
save('solution_Slacking');

%% Create Input for Planner in Simulink
% Read SS-test Scenario
fileID = fopen('../SS_test_enu.txt','r');
formatSpec = '%f %f';
sizeA = [2 Inf];
A = fscanf(fileID,formatSpec,sizeA);
fclose(fileID);
C_enu = A';

fileID = fopen('../SS_test_lla.txt','r');
sizeA = [2 Inf];
A = fscanf(fileID,formatSpec,sizeA);
fclose(fileID);
C_lla = A';

save('plannedRoutes','nk','Destinations','w_post','C_enu','C_lla');