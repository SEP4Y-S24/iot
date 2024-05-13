#pragma once

#define CCP_MAX_BODY_LENGTH 96

typedef enum
{
    CCP_STATUS_OK,
    CCP_STATUS_SERVER_ERROR,
    CCP_STATUS_BAD_REQUEST,
    CCP_STATUS_UNAUTHENTICATED,
    CCP_STATUS_NUM_STATUS_CODES
} CCP_STATUS_CODE;

typedef enum
{
    CCP_AT_TM,
    CCP_AT_MS,
    CCP_AT_CA,
    CCP_AT_DA,
    CCP_AT_UNKNOWN
} CCP_ACTION_TYPE;

typedef struct
{
    CCP_ACTION_TYPE action_type;
    CCP_STATUS_CODE status_code;
    char body[CCP_MAX_BODY_LENGTH];
} response;

typedef struct
{
    CCP_ACTION_TYPE action_type;
    char body[CCP_MAX_BODY_LENGTH];
} request;

void ccp_create_request(CCP_ACTION_TYPE at, char *body, char *request_buffer);

void ccp_create_response(char *response_buffer, CCP_ACTION_TYPE at, CCP_STATUS_CODE code, char *body);

response ccp_parse_response(char *raw_response);

request ccp_parse_request(char *raw_request);

CCP_ACTION_TYPE ccp_at_from_str(char *action_type);
