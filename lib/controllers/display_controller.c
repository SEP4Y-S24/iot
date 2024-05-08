#include <display_controller.h>
#include "periodic_task.h"
#include "clock.h"
#include "message.h"
#include "periodic_task.h"
#include "buttons.h"
#include "logger.h"
static DISPLAY_CONTROLLER_STATE state = DISPLAY_STATE_TIME;

static void update_display()
{
    if (buttons_2_pressed())
    {
        display_controller_switch_state();
    }
    

    switch (state)
    {
    case DISPLAY_STATE_MESSAGE:
        message_display_message();  
        break;
    case DISPLAY_STATE_TIME:
        clock_display_time();
    }
}

void display_controller_init(){
    periodic_task_init_b(update_display, 1000);
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