#pragma once

#include <stdint.h>        // For standard integer types
#include "periodic_task.h" // For the periodic task functions

// Function to initialize the clock and periodic task
void clock_init();

// Function to display the current time in HH:MM format
void clock_display_time();

void clock_set_time(int hours, int minutes);