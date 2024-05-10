#include "native.h"
#include "hc_sr04.h"
#include "buzzer.h"
#include <stdio.h>
#include <stdbool.h>
#include "alarm.h"
#include "clock.h"
#include "periodic_task.h"
#include "logger.h"

static uint8_t alarm_hour = 0;
static uint8_t alarm_minute = 0;
static uint8_t alarm_delay = 0;
static bool alarm_is_set = false;
static bool alarm_is_active = false;
static bool alarm_is_stoped = false;

void alarm_init(int clock_minute_interval)
{
    hc_sr04_init();
    log_info("Alarm initialized");
    periodic_task_init_c(alarm_check, clock_minute_interval * 1000);
}

void alarm_set(int hour, int minute)
{

    log_info("Alarm set to: ");
    alarm_hour = hour;
    alarm_minute = minute;
    alarm_is_set = true;
    alarm_is_active = true;

    char time[9];
    time[0] = alarm_hour / 10 + '0';
    time[1] = alarm_hour % 10 + '0';
    time[2] = ':';
    time[3] = alarm_minute / 10 + '0';
    time[4] = alarm_minute % 10 + '0';
    time[5] = '|';
    time[6] = alarm_is_set + '0';
    time[7] = alarm_is_active + '0';
    time[8] = '\0';
    log_info(time);
}

void alarm_unset()
{
    alarm_is_set = false;
    alarm_is_active = false;
    log_info("Alarm unset");
}

void alarm_stop()
{
    alarm_is_active = false;
    alarm_is_stoped = true;
    log_info("Alarm stopped");
}

void alarm_check()
{
    // log_info("Checking alarm");

    int clock_hour;
    int clock_minute;
    clock_get_time(&clock_hour, &clock_minute);

    int shifted_hour = alarm_hour;
    int shifted_minute = alarm_minute + alarm_delay;

    while (shifted_minute >= 60)
    {
        shifted_hour++;
        shifted_minute -= 60;
    }
    shifted_hour = shifted_hour % 24;

    while (alarm_is_set && alarm_is_active && clock_hour == shifted_hour && clock_minute == shifted_minute)
    {
        // log_info("Alarm is now");
        buzzer_beep();
        int distance = hc_sr04_takeMeasurement();

        char distance_info[30];

        sprintf(distance_info, "Distance: %d", distance);
        log_info(distance_info);
        if (distance < 100)
        {
            alarm_stop();
        }

        native_delay_ms(50);
    }

    if (alarm_is_stoped && clock_hour != shifted_hour && clock_minute != shifted_minute)
    {
        alarm_is_stoped = false;
        alarm_is_active = true;
    }
}

bool alarm_get_is_active()
{
    return alarm_is_active;
}

bool alarm_get_is_set()
{
    return alarm_is_set;
}

bool alarm_get_is_stoped()
{
    return alarm_is_stoped;
}