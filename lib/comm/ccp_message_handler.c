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

    log_info("Received message:");
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
    // extract data from message
    response server_response = ccp_parse_response(message);

    // display_message
    char device_response[30];
    ccp_create_response(device_response, CCP_AT_MS, CCP_STATUS_OK, "Message received");
    uint8_t response_data[30];
    memcpy(response_data, device_response, strlen(device_response));
    wifi_command_TCP_transmit(response_data, 30);
    log_info("updating time");
    clock_set_time(12, 35); // replace harcoded time with a real one
}

void ccp_handle_message_at(char *message)
{
    buzzer_beep();
    message_set_message("I love Mark <3"); // replace the harcoded message
    message_display_message();
    ccp_message_sender_send_response(CCP_AT_MS, CCP_STATUS_OK, "Message received");
    // extract data from message
    response server_response = ccp_parse_response(message);

    // display_message
    char device_response[30];
    ccp_create_response(device_response, CCP_AT_MS, CCP_STATUS_OK, "Message received");
    uint8_t response_data[30];
    memcpy(response_data, device_response, strlen(device_response));
    wifi_command_TCP_transmit(response_data, 30);
}
