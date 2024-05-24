#include "display_controller.h"
#include "message.h"
#include "scheduler.h"
#include "clock.h"
#include "../drivers/periodic_task.h"
#include "../drivers/buttons.h"
#include "../utils/logger.h"
#include "../drivers/external_screen.h"
#include <stdio.h>

static DISPLAY_CONTROLLER_STATE state = DISPLAY_STATE_TIME;
static void display_time_from_clock_on_external_screen();
static void display_message();
static void update_display()
{
    if (buttons_2_pressed())
    {
        display_controller_switch_state();
    }

    switch (state)
    {
    case DISPLAY_STATE_MESSAGE:
        display_message();
        break;
    case DISPLAY_STATE_TIME:
        display_time_from_clock_on_external_screen();
    }
}

void display_controller_init()
{
    scheduler_add_task(update_display, 1);
}

void display_controller_switch_state()
{
    log_info("changing display state");
    switch (state)
    {
    case DISPLAY_STATE_MESSAGE:
        state = DISPLAY_STATE_TIME;
        break;
    case DISPLAY_STATE_TIME:
        state = DISPLAY_STATE_MESSAGE;
    }
}

static void display_time_from_clock_on_external_screen()
{
    int current_hour, current_minute;
    clock_get_time(&current_hour, &current_minute); // Get the current time from the clock
    char time_str[6];                               // Buffer to store the time string
    // Format the time string as HH:MM

    sprintf(time_str, "%02d:%02d", current_hour, current_minute);
    external_screen_string(time_str);
}

static void display_message()
{
    char *message = message_get_message();
    external_screen_string(message);
}