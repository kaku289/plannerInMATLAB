function H = plotWorkDist(ax,w,colorMatrix)
% To plot the work distributed to different vehicles in a stacked bar graph
%
% author: Pulkit Goyal, March 2016
% 
% w - Matrix of weights (route lengths) to be plotted
% size(w) = (n,m)
% n - number of vehicles
% m - Maximum number of routes assigned to a vehicle
% 
% ax = axes handle on which bar graph has to be plotted
% colorMatrix = color matrix

[~,m] = size(w);

H=barh(ax, w, 'stack');
for k=1:m
  set(H(k),'facecolor',colorMatrix(k,:),'LineWidth',2)
end
end