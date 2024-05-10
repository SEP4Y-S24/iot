#include <uart.h>
#include <connect_wifi_state.h>
#include <stddef.h>
#include <wifi.h>
#include <state_coordinator.h>
#include <display.h>
#include <clock.h>
#include <logger.h>
#include <external_screen.h>
#include <util/delay.h>
#include <display_controller.h>
#include "scheduler.h"
#include "alarm.h"

void here()
{
}

int main()
{
	display_controller_init();
	external_screen_init(); // ------> makes a weird beeping sound
	log_init();
	display_init();
	scheduler_init();
	// Can be adjasted to mock time passing quicker. 60s = 1 minute, 1s = 1 second
	int clock_minute_interval = 5;
	scheduler_add_task(clock_update_time, clock_minute_interval);
	scheduler_add_task(display_time_from_clock, clock_minute_interval);

	// If you want to test the alarm, uncomment the following lines
	// alarm_init(clock_minute_interval);
	// alarm_set(10, 11);

	wifi_init(NULL);
	wifi_command_reset(); // reset the module. Because sometimes it just makes it work -_('o')_-  Software development at its best.
	_delay_ms(5000);

	start();

	while (1)
	{
	}
}