#include <uart.h>
#include <connect_wifi_state.h>
#include <stddef.h>
#include <wifi.h>
#include <state_coordinator.h>
#include <logger.h>
#include <external_screen.h>
#include <util/delay.h>
#include <display_controller.h>
#include <i2cmaster.h>
#include <display.h>

int main()
{
	display_controller_init();
	external_screen_init();
	log_init();
	display_init();
	i2c_init();

	wifi_init(NULL);
	wifi_command_reset(); // reset the module. Because sometimes it just makes it work -_('o')_-  Software development at its best.
	_delay_ms(5000);

	start();

	while (1)
	{
	}
}