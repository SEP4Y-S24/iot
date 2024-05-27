#include "ccp_protocol.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wifi.h"
#include "../utils/logger.h"
#include "../utils/utils.h"
#include <stdint.h>

const char *LINE_TERMINATOR = "|";
void ccp_at_to_string(CCP_ACTION_TYPE at, char *action_type);
const CCP_STATUS_CODE status_code_from_string(char *code);
const char *status_code_to_string(CCP_STATUS_CODE code);
static void extract_action_type(char *message, CCP_ACTION_TYPE *action_type);
static void extract_status_code(char *message, CCP_STATUS_CODE *status_code);
static CCP_PARSING_STATUS extract_body(char *message, char *body_ptr, int line_terminator_index);
const CCP_STATUS_CODE status_code_from_string(char *code);

CCP_PARSING_STATUS ccp_parse_response(char *raw_response, response *response_pointer)
{
    if (response_pointer == NULL)
        return CCP_PARSING_INVALID_EMPTY_POINTER;

    response response = {CCP_AT_UNKNOWN, CCP_STATUS_BAD_REQUEST, {0}};

    if (raw_response == NULL)
    {
        *response_pointer = response;
        return CCP_PARSING_INVALID_EMPTY_POINTER;
    }

    int num_parts = utils_count_char_in_string(raw_response, LINE_TERMINATOR[0]);

    if (num_parts < 1)
    {
        *response_pointer = response;
        return CCP_PARSING_INVALID_WRONG_FORMAT;
    }

    extract_action_type(raw_response, &response.action_type);

    if (num_parts <= 2)
    {
        *response_pointer = response;
        return CCP_PARSING_INVALID_WRONG_FORMAT;
    }

    extract_status_code(raw_response, &response.status_code);

    CCP_PARSING_STATUS body_parsing_status = CCP_PARSING_VALID;

    if (num_parts >= 4)
    {
        body_parsing_status = extract_body(raw_response, response.body, 2);
    }

    *response_pointer = response;
    return body_parsing_status;
}

CCP_PARSING_STATUS ccp_parse_request(char *raw_request, request *request_pointer)
{
    if (request_pointer == NULL)
        return CCP_PARSING_INVALID_EMPTY_POINTER;

    request request = {CCP_AT_UNKNOWN, {0}};

    if (raw_request == NULL)
    {
        *request_pointer = request;
        return CCP_PARSING_INVALID_EMPTY_POINTER;
    }

    int num_parts = utils_count_char_in_string(raw_request, LINE_TERMINATOR[0]);

    if (num_parts <= 1)
    {
        *request_pointer = request;
        return CCP_PARSING_INVALID_WRONG_FORMAT;
    }

    extract_action_type(raw_request, &request.action_type);
    CCP_PARSING_STATUS body_parsing_status = CCP_PARSING_VALID;

    if (num_parts >= 3)
    {
        body_parsing_status = extract_body(raw_request, request.body, 1);
    }

    *request_pointer = request;

    return body_parsing_status;
}

void ccp_create_request(CCP_ACTION_TYPE at, char *body, char *request_buffer)
{
    int length_of_message = strlen(body);
    char at_str[3];
    ccp_at_to_string(at, at_str);
    char length_string[10];
    sprintf(length_string, "%d", length_of_message);
    strcpy(request_buffer, at_str);
    strcat(request_buffer, LINE_TERMINATOR);
    strcat(request_buffer, length_string);
    strcat(request_buffer, LINE_TERMINATOR);
    strcat(request_buffer, body);
    strcat(request_buffer, LINE_TERMINATOR);
}

void ccp_create_response(char *response_buffer, CCP_ACTION_TYPE at, CCP_STATUS_CODE code, char *body)
{
    char at_str[9];
    ccp_at_to_string(at, at_str);
    int length_of_message = strlen(body);
    char length_string[10];
    sprintf(length_string, "%d", length_of_message);
    strcpy(response_buffer, at_str);
    strcat(response_buffer, LINE_TERMINATOR);
    strcat(response_buffer, status_code_to_string(code));
    strcat(response_buffer, LINE_TERMINATOR);
    strcat(response_buffer, length_string);
    strcat(response_buffer, LINE_TERMINATOR);
    strcat(response_buffer, body);
    strcat(response_buffer, LINE_TERMINATOR);
}

const char *status_code_strings[] = {
    [CCP_STATUS_BAD_REQUEST] = "0",
    [CCP_STATUS_OK] = "1",
    [CCP_STATUS_SERVER_ERROR] = "2",
    [CCP_STATUS_UNAUTHENTICATED] = "3",
    [CCP_STATUS_NUM_STATUS_CODES] = "Unknown" // Default string for unknown status codes
};

const char *status_code_to_string(CCP_STATUS_CODE code)
{
    if (code >= 0 && code < CCP_STATUS_NUM_STATUS_CODES)
        return status_code_strings[code];
    else
        return status_code_strings[CCP_STATUS_NUM_STATUS_CODES]; // Return the default string
}

const CCP_STATUS_CODE status_code_from_string(char *code)
{
    for (int i = 0; i < CCP_STATUS_NUM_STATUS_CODES; ++i)
    {
        if (strcmp(code, status_code_strings[i]) == 0)
            return (CCP_STATUS_CODE)i;
    }
    return CCP_STATUS_NUM_STATUS_CODES; // Return the default status code for unknown strings
}

CCP_ACTION_TYPE ccp_at_from_str(char *message)
{
    if (strncmp(message, "TM", 2) == 0)
        return CCP_AT_TM;
    else if (strncmp(message, "MS", 2) == 0)
        return CCP_AT_MS;
    else if (strncmp(message, "CA", 2) == 0)
        return CCP_AT_CA;
    else if (strncmp(message, "DA", 2) == 0)
        return CCP_AT_DA;
    else if (strncmp(message, "TH", 2) == 0)
        return CCP_AT_TH;
    else if (strncmp(message, "AU", 2) == 0)
        return CCP_AT_AU;
    else if (strncmp(message, "KV", 2) == 0)
        return CCP_AT_KV;
    else
        return CCP_AT_UNKNOWN;
}

void ccp_at_to_string(CCP_ACTION_TYPE at, char *action_type)
{
    switch (at)
    {
    case CCP_AT_TM:
        strcpy(action_type, "TM");
        break;
    case CCP_AT_MS:
        strcpy(action_type, "MS");
        break;
    case CCP_AT_SK:
        strcpy(action_type, "SK");
        break;
    case CCP_AT_CK:
        strcpy(action_type, "CK");
        break;
    case CCP_AT_CA:
        strcpy(action_type, "CA");
        break;
    case CCP_AT_DA:
        strcpy(action_type, "DA");
        break;
    case CCP_AT_TH:
        strcpy(action_type, "TH");
        break;
    case CCP_AT_AU:
        strcpy(action_type, "AU");
        break;
    case CCP_AT_KV:
        strcpy(action_type, "KV");
        break;
    default:
        strcpy(action_type, "Unknown");
        break;
    }
}

static void extract_action_type(char *message, CCP_ACTION_TYPE *action_type)
{
    char at[3];
    strncpy(at, message, 2);
    at[2] = '\0';
    *action_type = ccp_at_from_str(at);
}

static void extract_status_code(char *message, CCP_STATUS_CODE *status_code_ptr)
{
    char status_code[2];
    int status_code_index = utils_find_nth_char_index_in_string(message, LINE_TERMINATOR[0], 1);
    strncpy(status_code, message + status_code_index + 1, 1);
    status_code[1] = '\0';
    *status_code_ptr = status_code_from_string(status_code);
}

static CCP_PARSING_STATUS extract_body(char *message, char *body_ptr, int line_terminator_index)
{
    char body_length[10];
    int body_length_index = utils_find_nth_char_index_in_string(message, LINE_TERMINATOR[0], line_terminator_index);

    int body_length_segment_length = utils_find_nth_char_index_in_string(message, LINE_TERMINATOR[0], line_terminator_index + 1) - body_length_index - 1;

    if (body_length_segment_length <= 0)
    {
        body_ptr[0] = '\0';
        return CCP_PARSING_INVALID_WRONG_FORMAT;
    }

    strncpy(body_length, message + body_length_index + 1, utils_find_nth_char_index_in_string(message, LINE_TERMINATOR[0], line_terminator_index + 1));
    int body_length_int = atoi(body_length);

    if (body_length_int < 0 || body_length_int > CCP_MAX_BODY_LENGTH)
    {
        body_ptr = "";
        return CCP_PARSING_INVALID_WRONG_FORMAT;
    }

    int body_index = utils_find_nth_char_index_in_string(message, LINE_TERMINATOR[0], line_terminator_index + 1);
    strncpy(body_ptr, message + body_index + 1, body_length_int);
    body_ptr[body_length_int] = '\0';

    return CCP_PARSING_VALID;
}