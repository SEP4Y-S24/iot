#include "state_coordinator.h"
#include "connect_wifi_state.h"
#include "connect_server_state.h"
#include "working_state.h"
#include <stddef.h>
#include <clock.h>
#include <display.h>
#include "scheduler.h"

void state_coordinator(State state)
{
    char *ip = "192.168.43.130";
    int port = 13000;

    while (1)
    {
        switch (state)
        {
        case WIFI_CONNECT_STATE:
            state_coordinator(connect_wifi_state_switch("hi123", "kacenka123"));
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
    // --- NOTICE ---
    // If you want to test the alarm, uncomment the following lines
    // alarm_init(clock_minute_interval);
    // alarm_set(10, 11);
    scheduler_add_task(display_time_from_clock, 60);
    // clock_display_time();
    state_coordinator(WIFI_CONNECT_STATE);
}