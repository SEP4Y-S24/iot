#include "ccp_protocol.h"
#include "key_verification_state.h"
#include <stdbool.h>
#include "logger.h"

void key_verification_callback(char *message)
{
    log_debug("Key verification callback");
    request request;
    ccp_parse_request((char *)message, &request);
    if (request.action_type != CCP_AT_KV)
    {
        log_info("Wrong action type");
        return;
    }
    key_verification_state_set_key_verified(true);
}