#include "ccp_protocol.h"
#include "wifi.h"
#include "string.h"
#include "logger.h"
#include "ccp_message_sender.h"

void ccp_request_maker_tm()
{
    ccp_message_sender_send_request(CCP_AT_TM, "");
}