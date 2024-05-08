#pragma once

typedef enum
{
    CCP_STATUS_OK,
    CCP_STATUS_SERVER_ERROR,
    CCP_STATUS_BAD_REQUEST,
    CCP_STATUS_UNAUTHENTICATED,
    CCP_STATUS_NUM_STATUS_CODES
} CCP_STATUS_CODE;

typedef enum{
    CCP_AT_TM,
    CCP_AT_MS,
    CCP_AT_UNKNOWN
} CCP_ACTION_TYPE;

void ccp_create_request(CCP_ACTION_TYPE at, char *body, char *request_buffer);

void ccp_create_response(char *response_buffer, CCP_ACTION_TYPE at, CCP_STATUS_CODE code, char *body);

char *ccp_parse_response(char *response, char *status_buffer, int status_buffer_size);

CCP_ACTION_TYPE ccp_at_from_str(char *action_type);
