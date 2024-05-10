#include "state_coordinator.h"
#include "connect_wifi_state.h"
#include "connect_server_state.h"
#include "working_state.h"
#include <stddef.h>

void state_coordinator(State state)
{
    char *ip = "192.168.43.122";
    int port = 8080;

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
    // clock_display_time();
    state_coordinator(WIFI_CONNECT_STATE);
}