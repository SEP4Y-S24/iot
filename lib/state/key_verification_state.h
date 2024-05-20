#pragma once
#include <state_coordinator.h>

State key_verification_state_switch(char* key);

void key_verification_state_set_waiting_for_key_verification(bool waiting);

void key_verification_state_set_key(char* key);