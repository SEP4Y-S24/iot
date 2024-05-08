#include "periodic_task.h" // Include the periodic task header
#include "display.h"       // Include the display header
#include <stdio.h>
#include <stdlib.h>
#include <external_screen.h>

static uint8_t current_hour = 10;   // Current hour (0-23)
static uint8_t current_minute = 10; // Current minute (0-59)

void clock_display_time()
{
    char time_str[6]; // Buffer to store the time string
    // Format the time string as HH:MM
    sprintf(time_str, "%02d:%02d", current_hour, current_minute);
    external_screen_string(time_str);
}


static void clock_update_time()
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

    clock_display_time(); // Update the display
}

void clock_init()
{
    periodic_task_init_c(clock_update_time, 60000); // Set to call `update_time` every minute (60000 ms)
}

void clock_set_time(int hours, int minutes)
{
    current_hour = hours;
    current_minute = minutes;
}