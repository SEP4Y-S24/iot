#pragma once

#include <stdint.h>        // For standard integer types
#include "periodic_task.h" // For the periodic task functions

// Function to display the current time in HH:MM format
void clock_display_time();

void clock_set_time(int hours, int minutes);

void clock_get_time(int *hours, int *minutes);

void clock_update_time();