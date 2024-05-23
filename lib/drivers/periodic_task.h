/**
 * @file periodic_task.h
 * @brief Periodic Task Driver for ATmega2560
 *
 * This file provides the API for initializing Timer0 and attaching user functions
 * that will be called at different frequencies.
 *
 * @author Laurits Anesen
 * @date September 2023
 */

#pragma once
#include <stdint.h>

typedef void (*PERIODIC_TASK_CALLBACK)();
/**
 * @brief Initialize Timer0 and attach the first user function
 *
 * This function initializes Timer0 to call the provided function every XX milliseconds.
 *
 * @param user_function_a Pointer to the first function to be executed
 * @param interval_ms_a Time interval in milliseconds for the first function
 */
void periodic_task_init_a(PERIODIC_TASK_CALLBACK, uint32_t interval_ms_a);

/**
 * @brief Attach the second user function
 *
 * This function sets Timer0 to call the provided function every XX milliseconds.
 *
 * @param user_function_b Pointer to the second function to be executed
 * @param interval_ms_b Time interval in milliseconds for the second function
 */
void periodic_task_init_b(PERIODIC_TASK_CALLBACK, uint32_t interval_ms_b);

void periodic_task_init_c(PERIODIC_TASK_CALLBACK, uint32_t interval_ms_c);
void periodic_task_init_d(PERIODIC_TASK_CALLBACK, uint32_t interval_ms_d);
