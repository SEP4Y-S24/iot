
#include <state_coordinator.h>
#include <stdbool.h>
#include <ccp_protocol.h>
#include <inttypes.h>
#include <authentication_callback.h>
#include <message.h>
#include "logger.h"
#include "wifi.h"
#include "ccp_message_sender.h"
#include <stddef.h>

static bool authenticated;
static char buffer[CCP_MAX_MESSAGE_LENGTH];
static bool waiting_for_key_verification;

void authenticate_callback_wrapper()
{
    authentication_callback(buffer);
}

State authentication_state_switch(char *auth_key)
{
    authenticated = false;
    waiting_for_key_verification = false;
    log_info("Switching to authentication state");
    wifi_reassign_callback(authenticate_callback_wrapper, buffer);

    if (buffer == NULL)
        ccp_message_sender_send_request(CCP_AT_AU, "");
    else
    {
        ccp_message_sender_send_request(CCP_AT_AU, buffer);
    }

    state_coordinator_wait_for_event(&authenticated);

    if (!waiting_for_key_verification)
    {
        return WORKING_STATE;
    }
    else
    {
        return KEY_VERIFICATION_STATE;
    }
}

#ifndef NATIVE_TESTING

void authentication_state_set_authenticated(bool auth)
{
    authenticated = auth;
}

void authentication_state_set_waiting_for_key_verification(bool waiting)
{
    waiting_for_key_verification = waiting;
}

#endif