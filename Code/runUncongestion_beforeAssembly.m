% This script file runs the code to minimize the congestion at the depot
% using MILP. The problem is formulated so as to have minimum
% number of vehicles being present at the depot at same time instant.

clc; clear all; close all;

M = 1000; % A large number
T = 100; % Maximum journey time

nk = [10;9]; % Number of jobs/routes assigned to each vehicle
nv = length(nk); % Number of vehicles (=length(nk))
nr = sum(nk); % Number of routes

t = [10*ones(1,10), 10*ones(1,8), 14]; % time of each route listed in vehicle order (ROW VECTOR)
td = 4; % time units spent at the depot

nx = sum(nk.*nk); % Number of x (assignment) variables
nu = nx+(nr*T)+nr+1; % Number of all unknowns

%% Objective function (quantity to be minimized)
% Unknowns - [x^1_11 x^1_12 x^1_21 x^1_22 x^2_11 y^1_1,1... y^1_1,24 y^2_2,1... y^1_2,24 y^2_1,1... y^2_1,24 c^1_1 c^1_2 c^2_1 n_bar]
f = [zeros(nx,1);zeros(nr*T,1);zeros(nr,1);1]; 

%% Constraints

% Integer constraints
intcon = [1:nx+nr*T];

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
Aeq2(:,nx+(nr*T)+1:nx+(nr*T)+nr) = -eye(nr);
beq2 = zeros(nr,1);

% Inequality constraints
A_lhs = zeros(nr*T,nu);
A_rhs = zeros(nr*T,nu);
for ct=1:nr
    % LHS constraints
    A_lhs((ct-1)*T+1:ct*T,nx+(ct-1)*T+1:nx+(ct)*T) = M*eye(T);
    A_lhs((ct-1)*T+1:ct*T,nx+(nr*T)+ct) = -1;
    
    % RHS constraints
    A_rhs((ct-1)*T+1:ct*T,nx+(ct-1)*T+1:nx+(ct)*T) = M*eye(T);
    A_rhs((ct-1)*T+1:ct*T,nx+(nr*T)+ct) = 1;
end
lhs = M*ones(T,1)-[0:T-1]';
rhs = (M+td)*ones(T,1)+[1:T]';
b_lhs = repmat(lhs,nr,1);
b_rhs = repmat(rhs,nr,1);

% Equality constraints on y variables
Aeq3 = zeros(nr,nu);
Aeq3(:,nx+1:nx+nr*T) = kron(eye(nr),ones(1,T));
beq3 = (td+1)*ones(nr,1);


% Inequality constraint due to max operation in objective function
Aineq = zeros(T,nu);
for ct=1:nv
    Aineq(:,nx+sum(nk(1:ct-1))*T+1:nx+(sum(nk(1:ct))-1)*T) = kron(ones(1,nk(ct)-1),eye(T));
end
Aineq(:,end)=-1;
bineq = zeros(T,1);

%% Collect all inequality constraints
A = [A_lhs;A_rhs;Aineq];
b = [b_lhs;b_rhs;bineq];

%% Collect all equality constraints
Aeq = [Aeq1;Aeq2;Aeq3];
beq = [beq1;beq2;beq3];

%% Lower and Upper bounds
lb = zeros(nu,1);
ub = [ones(nx+nr*T,1); T*ones(nr,1); nv];

%% Solving the posed problem
x = intlinprog(f,intcon,A,b,Aeq,beq,lb,ub);
display('--- x ----');
display(x(1:nx)')
% reshape(x(1:nx),[nr 2])'
display('--- n_bar ----');
display((x(end))')

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
for ct=1:nv
    ct_x = sum(nk(1:ct-1).*nk(1:ct-1));
    ct_row = sum(nk(1:ct-1));
    ct_col = nk(ct);
    x_mat = (reshape(x(ct_x+1:ct_x+ct_col*ct_col),ct_col,ct_col))';
    finishTime = t(ct_row+1:ct_row+ct_col)*x_mat;
    arriveAtDepot = finishTime-td;
    w_post(ct,1:2*ct_col) = reshape([arriveAtDepot; td*ones(1,ct_col)],1,2*ct_col); 
end
plotID = 1020;
figure(plotID);
ax1 = subplot(2,1,1);
plotWorkDist(ax1, w_pre, C_pre);
set(gca, 'FontSize', 18);
ylabel('Vehicles', 'FontSize', 16);
title('Before clearing congestion at the depot','FontSize', 16);

ax2 = subplot(2,1,2);
plotWorkDist(ax2, w_post, C_post);
set(gca, 'FontSize', 18);
ylabel('Vehicles', 'FontSize', 16);
xlabel('Time', 'FontSize', 16);
% set(findobj('type','axes'),'fontsize',18)
% xt = get(gca, 'XTick');
title('After clearing congestion at the depot', 'FontSize', 16);