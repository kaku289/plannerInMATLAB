function dataSent = construct_BLOCK_message(block_id, ac_id)
    message_id = 5;
    dataL_overhead = 4 + 2; % Number of bytes (unint8) required
    dataL_payload = 2; % Payload here is BLOCK message in datalink
    dataSent = [uint8(153) uint8(dataL_overhead+dataL_payload) uint8(0) uint8(message_id) ...
            uint8(block_id) uint8(ac_id)];
    ck_a = 0;
    ck_b = 0;
    for i=2:dataSent(2)-2
        ck_a = uint8(rem(uint16(ck_a)+uint16(dataSent(i)),uint16(256)));
        ck_b = uint8(rem(uint16(ck_b)+uint16(ck_a),uint16(256)));
    end
    dataSent = typecast([dataSent ck_a ck_b],'uint8');
%     dataSent = [dataSent ck_a ck_b];
%     dataSent = typecast(dataSent,'uint8');
end