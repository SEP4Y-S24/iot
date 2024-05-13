#pragma once
#include <stdbool.h>

void alarm_init();
void alarm_create(int hour, int minute);
void alarm_delete();
void alarm_check();

void alarm_stop();
bool alarm_get_is_active();
bool alarm_get_is_created();
bool alarm_get_is_stoped();