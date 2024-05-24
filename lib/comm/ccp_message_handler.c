
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
static void ccp_handle_parse_error(CCP_ACTION_TYPE action_type, CCP_PARSING_STATUS parsing_status);

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

static void ccp_handle_parse_error(CCP_ACTION_TYPE action_type, CCP_PARSING_STATUS parsing_status)
{
    if (parsing_status == CCP_PARSING_INVALID_WRONG_FORMAT)
    {
        ccp_message_sender_send_response(action_type, CCP_STATUS_BAD_REQUEST, "Invalid fromat of the request.");
    }
    else if (parsing_status == CCP_PARSING_INVALID_EMPTY_POINTER)
    {
        ccp_message_sender_send_response(action_type, CCP_STATUS_SERVER_ERROR, "Server error occurred.");
    }
}

static void ccp_handle_create_alarm(char *message)
{
    // extract data from message
    request server_request;
    CCP_PARSING_STATUS parsing_status = ccp_parse_request(message, &server_request);

    if (parsing_status != CCP_PARSING_VALID)
    {
        ccp_handle_parse_error(server_request.action_type, parsing_status);
        return;
    }
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
    CCP_PARSING_STATUS parsing_status = ccp_parse_request(message, &server_request);
    if (parsing_status != CCP_PARSING_VALID)
    {
        ccp_handle_parse_error(server_request.action_type, parsing_status);
        return;
    }
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
    CCP_PARSING_STATUS parsing_status = ccp_parse_response(message, &server_response);
    if (parsing_status != CCP_PARSING_VALID)
    {
        ccp_handle_parse_error(server_response.action_type, parsing_status);
        return;
    }
    log_info("Updating time...");

    log_info(server_response.body);
    int hours, minutes;
    char hours_str[3] = {0}, minutes_str[3] = {0};

    // Extract hours and minutes from server response
    for (int i = 0; i < 2; i++)
    {
        hours_str[i] = server_response.body[i];
        minutes_str[i] = server_response.body[i + 2];
    }
    hours = atoi(hours_str);
    minutes = atoi(minutes_str);

    if (hours < 0 || hours > 23 || minutes < 0 || minutes > 59)
    {
        log_info("Invalid time extracted from server response");
        return;
    }

    clock_set_time(hours, minutes);
}

static void ccp_handle_message_at(char *message)
{
    // extract data from message
    request server_request;
    CCP_PARSING_STATUS parsing_status = ccp_parse_request(message, &server_request);
    if (parsing_status != CCP_PARSING_VALID)
    {
        ccp_handle_parse_error(server_request.action_type, parsing_status);
        return;
    }

    buzzer_beep();
    ccp_message_sender_send_response(server_request.action_type, CCP_STATUS_OK, "Message received");
    log_info("Updating message...");
    log_info(server_request.body);
    message_set_message(server_request.body);
}
