#pragma once
#include "ccp_protocol.h"

void ccp_message_sender_send_request(CCP_ACTION_TYPE at, char* body);
void ccp_message_sender_send_response(CCP_ACTION_TYPE at, CCP_STATUS_CODE status_code, char* body);