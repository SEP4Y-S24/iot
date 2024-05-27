#pragma once
#include "state_coordinator.h"

State authentication_state_switch(char *auth_key);

void authentication_state_set_authenticated(bool auth, char * auth_key);

void authentication_state_set_waiting_for_key_verification(bool waiting);