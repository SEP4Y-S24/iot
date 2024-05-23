#include "ccp_protocol.h"
#include "wifi.h"
#include "string.h"
#include <stdio.h>
#include "logger.h"
#include "cryptorator.h"

static const int MESSAGE_LENGTH = 110;
static void send_message(char *message);

void ccp_message_sender_send_request(CCP_ACTION_TYPE at, char *body)
{
    char request[MESSAGE_LENGTH];
    ccp_create_request(at, body, request);
    send_message(request);
}
void ccp_message_sender_send_response(CCP_ACTION_TYPE at, CCP_STATUS_CODE status_code, char *body)
{
    char response[MESSAGE_LENGTH];
    ccp_create_response(response, at, status_code, body);
    send_message(response);
}

static void send_message(char *message)
{
    log_info("Sending message:");
    log_info(message);
    uint8_t data[MESSAGE_LENGTH];
    memcpy(data, message, strlen(message));
    cryptorator_encrypt((char *) data);
    
    log_debug("Sending message:");
    log_debug(message);
    wifi_command_TCP_transmit(data, strlen(message));
}