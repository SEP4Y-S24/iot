#pragma once
#include <state_coordinator.h>

State key_verification_state_switch();

void key_verification_state_set_key_verified(bool waiting);

void key_verification_state_set_key(char* key);