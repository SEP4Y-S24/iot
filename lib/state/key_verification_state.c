#include <stdbool.h>
#include <state_coordinator.h>
#include <key_verification_state.h>
#include "key_verification_callback.h"
#include "logger.h"
#include "message.h"
#include "string.h"
#include "ccp_protocol.h"
#include "wifi.h"

static bool key_verified;
static char buffer[CCP_MAX_BODY_LENGTH];

void key_verification_callback_wrapper()
{
    key_verification_callback(buffer);
}


State key_verification_state_switch()
{
    wifi_reassign_callback(key_verification_callback_wrapper, buffer);
    log_debug("Switching to key verification state");
    key_verified = false;

    state_coordinator_wait_for_event(&key_verified);

    char no_message[] = "No message received";
    message_set_message(no_message);
    return WORKING_STATE;
}
#ifndef NATIVE_TESTING
void key_verification_state_set_key_verified(bool waiting)
{
    key_verified = waiting;
}
#endif

void key_verification_state_set_key(char *new_key)
{
    message_set_message(new_key);
}