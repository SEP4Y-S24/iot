#pragma once
#include <stdbool.h>

typedef struct alarm
{
    int hour;
    int minute;
    int delay;
} alarm_t;

void alarm_init();
void alarm_create(int hour, int minute);
void alarm_delete(int hour, int minute);
void alarm_check();
int alarm_get_alarm_count();
