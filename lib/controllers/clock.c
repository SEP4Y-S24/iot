#include "periodic_task.h" // Include the periodic task header
#include "display.h"       // Include the display header
#include <stdio.h>
#include <stdlib.h>

static uint8_t current_hour = 10;   // Current hour (0-23)
static uint8_t current_minute = 10; // Current minute (0-59)

void clock_update_time()
{
    current_minute++; // Increment the minute

    if (current_minute == 60)
    { // Roll over when minute reaches 60
        current_minute = 0;
        current_hour++; // Increment the hour

        if (current_hour == 24)
        { // Roll over when hour reaches 24
            current_hour = 0;
        }
    }
}

void clock_set_time(int hours, int minutes)
{
    current_hour = hours;
    current_minute = minutes;
}

void clock_get_time(int *hours, int *minutes)
{
    *hours = current_hour;
    *minutes = current_minute;
}