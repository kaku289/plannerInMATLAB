clc; clear;
%%
display('WAY 1')
syms Vk alpha theta Vwx Vwy Va
[sol_Vk, sol_alpha] = solve([Vk*cos(theta)-Vwx-Va*cos(alpha) == 0, Vk*sin(theta)-Vwy-Va*sin(alpha) == 0], [Vk, alpha])

% Result - Not Successful

%% 
display('WAY 2')
syms Vk theta Vwx Vwy Va
[sol_Vk] = solve((Vk*cos(theta)-Vwx)^2 + (Vk*sin(theta)-Vwy)^2-Va^2 == 0, Vk)
simplify(sol_Vk)

% Result - Successful

%% Validation of results from 'WAY 2' method
clc
values = [0 25 0 20];
sol1 = subs((Vwx^2*cos(theta)^2 - Vwy^2*cos(theta)^2 + Va^2 - Vwx^2 + Vwx*Vwy*sin(2*theta))^(1/2) + Vwx*cos(theta) + Vwy*sin(theta),[theta Vwx Vwy Va],values);
sol2 = subs(Vwx*cos(theta) - (Vwx^2*cos(theta)^2 - Vwy^2*cos(theta)^2 + Va^2 - Vwx^2 + Vwx*Vwy*sin(2*theta))^(1/2) + Vwy*sin(theta),[theta Vwx Vwy Va],values);
display(double([sol1 sol2]));