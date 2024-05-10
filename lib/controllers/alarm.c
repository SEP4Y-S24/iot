#include "alarm.h"
#include "buzzer.h"
#include "tone.h"
#include "hc_sr04.h"
#include "clock.h"

uint8_t alarm_hour = -1;
uint8_t alarm_minute = -1;

void alarm_init(void)
{
    tone_init();
    hc_sr04_init();
}

void alarm_set_time(int hour, int minute)
{
    alarm_hour = hour;
    alarm_minute = minute;
}

void alarm_disable()
{
    alarm_hour = -1;
    alarm_minute = -1;
}

void alarm_check()
{
    if (alarm_hour == -1 || alarm_minute == -1)
    {
        return;
    }

    int clock_hour, clock_minute;
    clock_get_time(&clock_hour, &clock_minute);

    if (alarm_hour == clock_hour && alarm_minute == clock_minute)
    {
        alarm_on();
    }
    else
    {
        alarm_off();
    }
}

void alarm_on()
{
    tone_play_starwars();
    // tone_play_despacito();
    // while (1)
    // {
    //     // buzzer_beep();
    // }

    // buzzer_beep();
}

void alarm_off()
{
}