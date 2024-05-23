#include "state_coordinator.h"
#include "connect_wifi_state.h"
#include "connect_server_state.h"
#include "working_state.h"
#include <stddef.h>
#include <clock.h>
#include <display.h>
#include "scheduler.h"
#include "alarm.h"
#include "env_variables.h"
#include "native.h"
#include "authentication_state.h"
#include "logger.h"
#include "key_verification_state.h"

static bool error;
static State error_state;

static void state_coordinator(State state)
{
    char *ip = IP_ADDRESS;
    int port = PORT;

    while (1)
    {
        if (error)
        {
            state = error_state;
            error = false;
            error_state = WIFI_CONNECT_STATE;
        }
        switch (state)
        {
        case WIFI_CONNECT_STATE:
            state_coordinator(connect_wifi_state_switch(SSID, PASSWORD));
            break;
        case SERVER_CONNECT_STATE:
            state_coordinator(connect_server_state_switch(ip, port));
            break;
        case AUTHENTICATION_STATE:
            state_coordinator(authentication_state_switch(NULL));
            break;
        case KEY_VERIFICATION_STATE:
            state_coordinator(key_verification_state_switch());
            break;
        case WORKING_STATE:
            state_coordinator(working_state_switch(ip, port));
            break;
        }
    }
}

void start()
{
    error = false;
    error_state = WIFI_CONNECT_STATE;
    // --- NOTICE ---
    // Can be adjasted to mock time passing quicker. 60s = 1 minute, 1s = 1 second

    // --- NOTICE ---
    // If you want to test the alarm, uncomment the following lines
    alarm_init();
    // alarm_create(10, 11);

    // scheduler_add_task(clock_update_time, clock_minute_interval); -- deprecated
    //scheduler_add_task(display_time_from_clock, 60);
    // clock_display_time();

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