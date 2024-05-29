#include "key_verification_callback.h"
#include "key_verification_state.h"
#include "../comm/ccp_protocol.h"
#include "../utils/logger.h"
#include <stdbool.h>
#include <../encryption/cryptorator.h>

void key_verification_callback(char *message)
{
#ifndef ENCRYPTION_DISABLED
    cryptorator_decrypt(message);
#endif
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