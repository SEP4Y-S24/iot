#include "uart.h"
#include "ccp_protocol.h"
#include "buzzer.h"
#include <stdlib.h>
#include <string.h>
#include "logger.h"
#include "wifi.h"
#include "clock.h"
#include "ccp_message_sender.h"
#include "message.h"

void ccp_handle_time_at(char *message);
void ccp_handle_message_at(char *message);

void ccp_message_handler_handle(char *message)
{
    CCP_ACTION_TYPE at = ccp_at_from_str(message);
    log_info("recived message:");
    log_info(message);

    switch (at)
    {
    case CCP_AT_TM:
        ccp_handle_time_at(message);
        break;
    case CCP_AT_MS:
        ccp_handle_message_at(message);
    default:
    log_info("uknown at");
        break;
    }
}

void ccp_handle_time_at(char *message)
{
    log_info("updating time");
    clock_set_time(12, 35); //replace harcoded time with a real one
}

void ccp_handle_message_at(char *message)
{
    buzzer_beep();
    message_set_message("I love Mark <3"); //replace the harcoded message
    message_display_message();
    ccp_message_sender_send_response(CCP_AT_MS, CCP_STATUS_OK, "Message received");
}
