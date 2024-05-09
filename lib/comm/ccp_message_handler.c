#include "uart.h"
#include "ccp_protocol.h"
#include "buzzer.h"
#include <stdlib.h>
#include <string.h>
#include "logger.h"
#include "wifi.h"
#include "clock.h"
#include "leds.h"
#include "ccp_message_sender.h"
#include "message.h"

void ccp_handle_time_at(char *message);
void ccp_handle_message_at(char *message);

void ccp_message_handler_handle(char *message)
{
    CCP_ACTION_TYPE at = ccp_at_from_str(message);

    log_info("Received message:");
    log_info(message);

    switch (at)
    {
    case CCP_AT_TM:
        ccp_handle_time_at(message);
        break;
    case CCP_AT_MS:
        ccp_handle_message_at(message);
        break;
    default:
        log_info("Unknown Action Type...");
        break;
    }
}

void ccp_handle_time_at(char *message)
{
    // extract data from message
    response server_response = ccp_parse_response(message);

    // Display Time if Status Code is OK
    if (server_response.status_code == CCP_STATUS_OK)
    {
        int hours, minutes;
        char *token;
        token = strtok(server_response.body, ":");
        hours = atoi(token);
        token = strtok(NULL, ":");
        minutes = atoi(token);

        ccp_message_sender_send_response(server_response.action_type, CCP_STATUS_OK, "Time received");
        log_debug("Updating time...");
        clock_set_time(hours, minutes);
    }
}

void ccp_handle_message_at(char *message)
{
    // extract data from message
    response server_response = ccp_parse_response(message);

    // Display Message if Status Code is OK
    if (server_response.status_code == CCP_STATUS_OK)
    {
        buzzer_beep();
        leds_init();
        leds_turnOn(1);
        _delay_ms(3);
        leds_turnOff(1);
        ccp_message_sender_send_response(server_response.action_type, CCP_STATUS_OK, "Message received");
        log_debug("Updating message...");
        message_set_message(server_response.body);
        message_display_message();
    }
}
