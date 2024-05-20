#pragma once
#include <stdbool.h>

typedef struct alarm
{
    uint8_t hour;
    uint8_t minute;
    uint8_t delay;
} alarm_t;

void alarm_init();
void alarm_create(int hour, int minute);
void alarm_delete(int hour, int minute);
void alarm_check();
int alarm_get_alarm_count();
