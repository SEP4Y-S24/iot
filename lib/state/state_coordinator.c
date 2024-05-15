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

void state_coordinator(State state)
{
    char *ip = IP_ADDRESS;
    int port = PORT;

    while (1)
    {
        switch (state)
        {
        case WIFI_CONNECT_STATE:
            state_coordinator(connect_wifi_state_switch(SSID, PASSWORD));
            break;
        case SERVER_CONNECT_STATE:
            state_coordinator(connect_server_state_switch(ip, port));
            break;
        case WORKING_STATE:
            state_coordinator(working_state_switch(ip, port));
            break;
        }
    }
}

void start()
{
    scheduler_init();
    int clock_minute_interval = 60;
    // --- NOTICE ---
    // Can be adjasted to mock time passing quicker. 60s = 1 minute, 1s = 1 second

    // --- NOTICE ---
    // If you want to test the alarm, uncomment the following lines
    alarm_init(clock_minute_interval);
    // alarm_create(10, 11);

    // scheduler_add_task(clock_update_time, clock_minute_interval); -- deprecated
    scheduler_add_task(display_time_from_clock, 60);
    // clock_display_time();

    state_coordinator(WIFI_CONNECT_STATE);
}