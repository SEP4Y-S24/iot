
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
#include "cryptorator.h"


static void ccp_handle_time_at(char *message);
static void ccp_handle_message_at(char *message);
static void ccp_handle_create_alarm(char *message);
static void ccp_handle_delete_alarm(char *message);

void ccp_message_handler_handle(char *message)
{
    #ifndef ENCRYPTION_DISABLED
    cryptorator_decrypt(message); 
    #endif

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
    case CCP_AT_CA:
        ccp_handle_create_alarm(message);
        break;
    case CCP_AT_DA:
        ccp_handle_delete_alarm(message);
        break;
    default:
        log_info("Unknown Action Type...");
        break;
    }
}

static void ccp_handle_create_alarm(char *message)
{
    // extract data from message
    request server_request;
    ccp_parse_request(message, &server_request);

    ccp_message_sender_send_response(server_request.action_type, CCP_STATUS_OK, "Alarm received");
    log_info("Setting alarm...");

    char hour_str[3] = {server_request.body[0], server_request.body[1], '\0'};
    char minute_str[3] = {server_request.body[2], server_request.body[3], '\0'};

    int hour = atoi(hour_str);
    int minute = atoi(minute_str);
    alarm_create(hour, minute);
}

static void ccp_handle_delete_alarm(char *message)
{
    request server_request;
    ccp_parse_request(message, &server_request);
    char hour_str[3] = {server_request.body[0], server_request.body[1], '\0'};
    char minute_str[3] = {server_request.body[2], server_request.body[3], '\0'};

    int hour = atoi(hour_str);
    int minute = atoi(minute_str);
    alarm_delete(hour, minute);
    ccp_message_sender_send_response(server_request.action_type, CCP_STATUS_OK, "Alarm deleted");
}

static void ccp_handle_time_at(char *message)
{
    // extract data from message
    response server_response;
    ccp_parse_response(message, &server_response);

    log_info("Updating time...");

    log_info(server_response.body);
    int hours, minutes;
    char hours_str[3], minutes_str[3];

    // Extract hours and minutes from server response
    for (int i = 0; i < 2; i++)
    {
        hours_str[i] = server_response.body[i];
        minutes_str[i] = server_response.body[i + 2];
    }
    hours_str[2] = minutes_str[2] = '\0';
    hours = atoi(hours_str);
    minutes = atoi(minutes_str);

    clock_set_time(hours, minutes);
}

static void ccp_handle_message_at(char *message)
{
    // extract data from message
    request server_request;
    ccp_parse_request(message, &server_request);

    buzzer_beep();
    ccp_message_sender_send_response(server_request.action_type, CCP_STATUS_OK, "Message received");
    log_info("Updating message...");
    log_info(server_request.body);
    message_set_message(server_request.body);
}
