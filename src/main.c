#include <uart.h>
#include <connect_wifi_state.h>
#include <stddef.h>
#include <wifi.h>
#include <state_coordinator.h>
#include <display.h>
#include "clock.h"
#include <logger.h>
#include <external_screen.h>
#include <util/delay.h>
#include <display_controller.h>
#include <alarm.h>
#include <scheduler.h>

int main()
{
	// display_controller_init();
	// external_screen_init();
	// log_init();
	display_init();
	display_setValues(0, 1, 2, 3);

	// clock_display_time();
	// wifi_init(NULL);
	// wifi_command_reset(); // reset the module. Because sometimes it just makes it work -_('o')_-  Software development at its best.
	// _delay_ms(5000);

	alarm_init();
	// alarm_set_time(10, 14);
	// alarm_on();

	scheduler_init();
	scheduler_add_task(clock_update_time, 1);
	scheduler_add_task(display_from_time_from_clock, 1);
	scheduler_add_task(alarm_on, 30);

	// scheduler_add_task(alarm_on, 1);

	while (1)
	{
	}

	return 0;
}