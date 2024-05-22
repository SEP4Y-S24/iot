#pragma once
#include <stdbool.h>

typedef enum
{
    WIFI_CONNECT_STATE,
    SERVER_CONNECT_STATE,
    AUTHENTICATION_STATE,
    KEY_VERIFICATION_STATE,
    WORKING_STATE
} State;


void start();


void state_coordinator_wait_for_event(bool* event);