#include "periodic_task.h" // Include the periodic task header
#include "display.h"       // Include the display header
#include <stdio.h>
#include <stdlib.h>

#ifndef NO_RTC
#include <ds3231.h> // Include the RTC module

void clock_set_time(int hours, int minutes)
{
    write_hour(hours);
    write_min(minutes);
}

void clock_get_time(int *hours, int *minutes)
{
    *hours = read_hour();
    *minutes = read_min();
}
#endif

#ifdef NO_RTC
static int static_hours;
static int static_minutes;
void clock_set_time(int hours, int minutes)
{
    static_hours = hours;
    static_minutes = minutes;
}

void clock_get_time(int *hours, int *minutes)
{
    *hours = static_hours;
    *minutes = static_minutes;
}

#endif
