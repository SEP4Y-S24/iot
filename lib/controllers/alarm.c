#include "native.h"
#include "hc_sr04.h"
#include "buzzer.h"
#include <stdio.h>
#include <stdbool.h>
#include "alarm.h"
#include "clock.h"
#include "periodic_task.h"
#include "logger.h"
#include "buttons.h"

static uint8_t alarm_time_hour = 0;
static uint8_t alarm_time_minute = 0;
static uint8_t alarm_time_delay = 0;

static bool alarm_is_created = false;
static bool alarm_is_stoped = false;

void alarm_log_time(int h, int m)
{
    char time[20];
    sprintf(time, "%d:%d", h, m);
    log_info(time);
}

void alarm_init(int clock_minute_interval)
{
    buzzer_init();
    buttons_init();
    hc_sr04_init();
    log_info("Alarm initialized");
    periodic_task_init_c(alarm_check, clock_minute_interval * 1000);
}

void alarm_create(int hour, int minute)
{
    alarm_time_hour = hour;
    alarm_time_minute = minute;
    alarm_time_delay = 0;
    alarm_is_created = true;
    alarm_is_stoped = false;
    log_info("Alarm created");
    alarm_log_time(alarm_time_hour, alarm_time_minute);
}

void alarm_delete()
{
    alarm_time_hour = 0;
    alarm_time_minute = 0;
    alarm_time_delay = 0;
    alarm_is_created = false;
    log_info("Alarm deleted");
}

void alarm_check()
{
    log_debug("Alarm check");

    log_debug("Current time:");
    int current_hour, current_minute;
    clock_get_time(&current_hour, &current_minute);
    alarm_log_time(current_hour, current_minute);

    log_debug("Alarm time:");
    int shifted_hour = (alarm_time_hour + (alarm_time_delay / 60)) % 24;
    int shifted_minute = (alarm_time_minute + alarm_time_delay) % 60;
    alarm_log_time(shifted_hour, shifted_minute);

    while (shifted_hour == current_hour && shifted_minute == current_minute && alarm_is_created)
    {
        log_debug("Alarm is active");
        buzzer_beep();

        int distance = hc_sr04_takeMeasurement();
        int button_pressed_1 = buttons_1_pressed();

        if (distance < 100)
        {
            alarm_is_stoped = false;
            log_debug("Alarm is delayed");
            alarm_time_delay += 5;
            break;
        }

        if (button_pressed_1)
        {
            alarm_is_stoped = true;
            log_debug("Alarm is stoped");
            alarm_time_delay = 0;
            break;
        }
    }
}

bool alarm_get_is_created()
{
    return alarm_is_created;
}

bool alarm_get_is_stoped()
{
    return alarm_is_stoped;
}