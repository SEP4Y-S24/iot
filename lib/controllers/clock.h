#pragma once

#include <stdint.h>        // For standard integer types
#include "periodic_task.h" // For the periodic task functions

void clock_set_time(int hours, int minutes);

void clock_get_time(int *hours, int *minutes);
