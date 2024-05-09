/**
 * @file ds3231.h
 * @author Marcus Mitelea
 * @brief DS3231 RTC driver
 * @version 0.1
 * @date 2024-05-09
 *
 * @copyright Copyright (c) 2024
 */

#pragma once

#include <stdint.h>

#define DS3231_ADDRESS 0x68
#define DS3231_ADDR (DS3231_ADDRESS << 1)

////////// Functions //////

/**
 * @brief Read the seconds value from the DS3231 RTC.
 * @return The seconds value.
 */
extern uint8_t read_sec();

/**
 * @brief Read the minutes value from the DS3231 RTC.
 * @return The minutes value.
 */
extern uint8_t read_min();

/**
 * @brief Read the hours value from the DS3231 RTC.
 * @return The hours value.
 */
extern uint8_t read_hour();

/**
 * @brief Read the date value from the DS3231 RTC.
 * @return The date value.
 */
extern uint8_t read_date();

/**
 * @brief Read the month value from the DS3231 RTC.
 * @return The month value.
 */
extern uint8_t read_month();

/**
 * @brief Read the year value from the DS3231 RTC.
 * @return The year value.
 */
extern uint8_t read_year();

/**
 * @brief Write the seconds value to the DS3231 RTC.
 * @param sec The seconds value to write.
 */
extern void write_sec(uint8_t sec);

/**
 * @brief Write the minutes value to the DS3231 RTC.
 * @param min The minutes value to write.
 */
extern void write_min(uint8_t min);

/**
 * @brief Write the hours value to the DS3231 RTC.
 * @param hour The hours value to write.
 */
extern void write_hour(uint8_t hour);

/**
 * @brief Write the date value to the DS3231 RTC.
 * @param date The date value to write.
 */
extern void write_date(uint8_t date);

/**
 * @brief Write the month value to the DS3231 RTC.
 * @param month The month value to write.
 */
extern void write_month(uint8_t month);

/**
 * @brief Write the year value to the DS3231 RTC.
 * @param year The year value to write.
 */
extern void write_year(uint8_t year);