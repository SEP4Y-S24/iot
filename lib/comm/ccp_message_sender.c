#include "ccp_protocol.h"
#include "wifi.h"
#include "string.h"
#include <stdio.h>
#include "logger.h"
#include "ccp_message_sender.h"
#include "state_coordinator.h"
#include "ccp_message_handler.h"
#include "cryptorator.h"


static void send_message(char *message);

void ccp_message_sender_send_request(CCP_ACTION_TYPE at, char *body)
{
    char request[CCP_MAX_MESSAGE_LENGTH];
    ccp_create_request(at, body, request);
    send_message(request);
}
void ccp_message_sender_send_response(CCP_ACTION_TYPE at, CCP_STATUS_CODE status_code, char *body)
{
    char response[CCP_MAX_MESSAGE_LENGTH];
    ccp_create_response(response, at, status_code, body);
    send_message(response);
}

static void send_message(char *message)
{

    uint8_t data[CCP_MAX_MESSAGE_LENGTH];
    log_info("Sending message:");
    log_info(message);

    memcpy(data, message, strlen(message));
    #ifndef ENCRYPTION_DISABLED
    cryptorator_encrypt((char **) data);
    #endif
    log_debug("Sending message:");
    log_debug(message);
    if (wifi_command_TCP_transmit(data, strlen(message)) != WIFI_OK)
    {
        state_coordinator_set_error(true, SERVER_CONNECT_STATE);
    }
}