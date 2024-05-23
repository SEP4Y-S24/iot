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
#define max_alarm_count 32
static alarm_t alarms[max_alarm_count];


static uint8_t alarm_time_hour = 0;
static uint8_t alarm_time_minute = 0;
static uint8_t alarm_time_delay = 0;

static bool alarm_is_created = false;
static bool alarm_is_stoped = false;
void alarm_log_time(int h, int m, bool use_info)

{
    char time[20];
    sprintf(time, "%d:%d", h, m);
    log_info(time);
}

void alarm_init()
{
    buzzer_init();
    buttons_init();
    hc_sr04_init();
    for (int i = 0; i < max_alarm_count; i++)
    {
        alarms[i].hour = -1;
        alarms[i].minute = -1;
        alarms[i].delay = -1;
    }
    log_info("Alarms initialized");
    periodic_task_init_c(alarm_check, 60000);
}

void alarm_create(int hour, int minute)
{
    for (int i = 0; i < max_alarm_count; i++)
    {
        if (alarms[i].hour == hour && alarms[i].minute == minute)
        {
            log_info("Alarm already exists");
            alarm_log_time(hour, minute, true);
            return;
        }
    }

    for (int i = 0; i < max_alarm_count; i++)
    {
        if (alarms[i].hour != -1)
            continue;

        alarms[i].hour = hour;
        alarms[i].minute = minute;
        alarms[i].delay = 0;
        break;
    }

    log_info("Alarm created");
    alarm_log_time(hour, minute, true);
}

void alarm_delete(int hour, int minute)
{
    for (int i = 0; i < max_alarm_count; i++)
    {
        if (alarms[i].hour == hour && alarms[i].minute == minute)
        {
            alarms[i].hour = -1;
            alarms[i].minute = -1;
            alarms[i].delay = -1;
            break;
        }
    }

    log_info("Alarm deleted");
    alarm_log_time(hour, minute, true);
}

void alarm_check()
{
    log_debug("Alarm check");

    log_debug("Current time:");
    int current_hour, current_minute;
    clock_get_time(&current_hour, &current_minute);
    alarm_log_time(current_hour, current_minute, true);

    for (int i = 0; i < max_alarm_count; i++)
    {
        if (alarms[i].hour == -1)
            continue;

        int shifted_hour = (alarms[i].hour + (alarms[i].delay / 60)) % 24;
        int shifted_minute = (alarms[i].minute + alarms[i].delay) % 60;
        log_debug("Alarm time:");
        alarm_log_time(shifted_hour, shifted_minute, false);

        while (shifted_hour == current_hour && shifted_minute == current_minute)
        {
            log_debug("Alarm is active");
            buzzer_beep();

            int distance = hc_sr04_takeMeasurement();
            int button_pressed_1 = buttons_1_pressed();

            if (distance < 100)
            {
                log_debug("Alarm is delayed");
                alarms[i].delay += 1;
                break;
            }

            if (button_pressed_1)
            {
                log_debug("Alarm is stoped");
                break;
            }
        }
    }
}

int alarm_get_alarm_count()
{
    int count = 0;
    for (int i = 0; i < max_alarm_count; i++)
    {
        if (alarms[i].hour != -1)
            count++;
    }
    return count;
}