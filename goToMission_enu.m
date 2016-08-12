%% 
clc; clear;
hudps = dsp.UDPSender('RemoteIPPort',4043);
hudpr = dsp.UDPReceiver('LocalIPPort',4042);
tol = 0.0001;
%%

% % Initialization of some variables for communication using UDP
dataL_overhead = 4 + 2; 
dataL_payload = 2 + 4*3; % Payload here is MOVE_WP message in datalink

ac_id = 127;
block_id = 3;
    
% % Listen to find if route is finished
pause(10) % To stay clear of lagging messages 
isRouteFinished = 1;
while isRouteFinished
    dataReceived = step(hudpr);
    if ~isempty(dataReceived) && dataReceived(4)==217
        val = typecast(dataReceived(5:8), 'single');
        if abs(val)<tol
            isRouteFinished = 0;
            break;
        else
            % % Go Through the route
            dataSent = construct_BLOCK_message(block_id, ac_id);
            dataSent = typecast(dataSent,'uint8');
            step(hudps,dataSent)
        end
    end
    pause(0.01)
end
    

%%
release(hudps)
delete(hudps);
clear hudps
release(hudpr)
delete(hudpr);
clear hudpr
