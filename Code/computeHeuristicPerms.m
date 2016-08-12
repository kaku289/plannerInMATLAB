function Permutations = computeHeuristicPerms(capacity, Distances, searchRadius, searchIncrement, searchLimit)
% To compute all permutations of customers falling within circles of radius
% searchRadius.
%
% author: Pulkit Goyal, June 2016
% 
% size(Permutations,2) = capacity
% Distances(i,j) - Distance of customer i from customer j
% capacity - Maximum number of customers in a set
% searchLimit - The maximum number of customers with which one customer can be paired with
% searchRadius and searchIncrement - Parameters to reach searchLimit for every customer

n = size(Distances,1);
Distances(:,1) = Distances(1,1);
if capacity==1
    Permutations = permn(2:n,1);
else
    Permutations = [];

    for ct10=2:n
        [Dist, iDist] = sort(Distances(ct10,:));
        closeCustomers = iDist(Dist<=searchRadius);
        nCloseCustomers = length(closeCustomers);
        ct11 = 1;
        while nCloseCustomers < searchLimit
           closeCustomers = iDist(Dist<=searchRadius+ct11*searchIncrement);
           nCloseCustomers = length(closeCustomers);
           ct11 = ct11 + 1;
        end
        perms = permn([ct10 closeCustomers],capacity);
        perms = perms(any(perms==ct10,2),:);
        Permutations = [Permutations; perms];
    end

    Permutations = unique(Permutations,'rows');
end


