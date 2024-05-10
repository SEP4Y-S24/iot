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
#include "alarm.h"

void ccp_handle_time_at(char *message);
void ccp_handle_message_at(char *message);
void ccp_handle_set_alarm_at(char *message);
void ccp_handle_delete_alarm_at(char *message);

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
    case CCP_AT_SA:
        ccp_handle_set_alarm_at(message);
    case CCP_AT_DA:
        ccp_handle_delete_alarm_at(message);
    default:
        log_info("uknown at");
        break;
    }
}

void ccp_handle_time_at(char *message)
{
    log_info("updating time");
    clock_set_time(12, 35); // replace harcoded time with a real one
}

void ccp_handle_set_alarm_at(char *message)
{
    char hour_str[3] = {message[0], message[1], '\0'};   // char hour_str[3]
    char minute_str[3] = {message[3], message[4], '\0'}; // char minute_str[3]

    int hour = atoi(hour_str);
    int minute = atoi(minute_str);
    alarm_set(hour, minute);
}

void ccp_handle_delete_alarm_at(char *message)
{
    alarm_unset();
}

void ccp_handle_message_at(char *message)
{
    buzzer_beep();
    message_set_message("I love Mark <3"); // replace the harcoded message
    message_display_message();
    ccp_message_sender_send_response(CCP_AT_MS, CCP_STATUS_OK, "Message received");
}
