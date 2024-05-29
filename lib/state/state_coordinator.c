#include "state_coordinator.h"
#include "connect_wifi_state.h"
#include "connect_server_state.h"
#include "key_verification_state.h"
#include "working_state.h"
#include "authentication_state.h"
#include "../controllers/clock.h"
#include "../controllers/scheduler.h"
#include "../controllers/alarm.h"
#include "../env/env_variables.h"
#include "../utils/native.h"
#include "../utils/logger.h"
#include <stddef.h>

static bool error;
static State error_state;
static State next_state;

static void state_coordinator()
{
    while (1)
    {
        if (error)
        {
            next_state = error_state;
            error = false;
            error_state = WIFI_CONNECT_STATE;
        }
        switch (next_state)
        {
        case WIFI_CONNECT_STATE:
            next_state = connect_wifi_state_switch(SSID, PASSWORD);
            break;
        case SERVER_CONNECT_STATE:
            next_state = connect_server_state_switch(IP_ADDRESS, PORT);
            break;
        case AUTHENTICATION_STATE:
            next_state = authentication_state_switch(NULL);
            break;
        case KEY_VERIFICATION_STATE:
            next_state = (key_verification_state_switch());
            break;
        case WORKING_STATE:
            next_state = (working_state_switch());
            break;
        }
    }
}

void start()
{
    error = false;
    error_state = WIFI_CONNECT_STATE;
    next_state = WIFI_CONNECT_STATE;

    alarm_init();
    state_coordinator(WIFI_CONNECT_STATE);
}

void state_coordinator_wait_for_event(bool *event)
{
    while (!(*event) && !error)
    {
        native_delay_ms(100);
    }
    log_debug("I am free now!");
}

void state_coordinator_set_error(bool err, State new_error_state)
{
    error = err;
    error_state = new_error_state;
}