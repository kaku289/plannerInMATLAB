%clc; clear;
hudps = dsp.UDPSender('RemoteIPPort',4143);
hudpr = dsp.UDPReceiver('LocalIPPort',4142);
tol = 0.001; % Tolerance to check equality of a variable


ac_id = 126;

altChanged = 0;

while ~altChanged
    dataReceived = step(hudpr);
    if ~isempty(dataReceived) && dataReceived(3)==ac_id && dataReceived(4)==47 %9 && dataReceived(5)==4
        val = typecast(dataReceived(5:8), 'single');
        break;
    end
        
%     if ~isempty(dataReceived) && dataReceived(4)==154
%         altChanged = 1;
%         break;
%     end
    pause(0.001);
end

%%
release(hudps)
delete(hudps);
clear hudps
release(hudpr)
delete(hudpr);
clear hudpr

