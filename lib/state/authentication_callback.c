#include "authentication_callback.h"
#include "authentication_state.h"
#include "key_verification_state.h"
#include "../comm/ccp_protocol.h"
#include "../utils/logger.h"
#include <string.h>
#include <stddef.h>

void authentication_callback(char *message)
{
#ifndef ENCRYPTION_DISABLED
    cryptorator_decrypt(message);
#endif
    response response;
    ccp_parse_response((char *)message, &response);

    if (response.action_type != CCP_AT_AU)
    {
        log_info("Wrong action type");
        return;
    }
    if (response.status_code == CCP_STATUS_OK)
    {
        log_debug("Authenticated");
        authentication_state_set_authenticated(true, NULL);
        authentication_state_set_waiting_for_key_verification(false);
    }
    else if (response.status_code == CCP_STATUS_UNAUTHENTICATED)
    {
        response.status_code = CCP_STATUS_UNAUTHENTICATED;
        log_info("Unauthenticated");
        authentication_state_set_waiting_for_key_verification(true);
        authentication_state_set_authenticated(true, response.body);
        key_verification_state_set_key(response.body);
    }
    else
    {
        log_info("Server error");
    }
}
