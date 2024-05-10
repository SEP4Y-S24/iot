#pragma once
#include <stdbool.h>

void alarm_init();
void alarm_set(int hour, int minute);
void alarm_unset();
void alarm_check();
void alarm_stop();

bool alarm_get_is_active();
bool alarm_get_is_set();
bool alarm_get_is_stoped();