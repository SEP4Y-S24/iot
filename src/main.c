#include "../drivers/uart.h"
#include "../drivers/wifi.h"
#include "../drivers/i2cmaster.h"
#include "../drivers/external_screen.h"
#include "../controllers/scheduler.h"
#include "../state/connect_wifi_state.h"
#include "../state/state_coordinator.h"
#include "../controllers/display_controller.h"
#include "../utils/native.h"
#include "../utils/logger.h"
#include <stddef.h>

void nothing_callback(uint8_t data)
{
}

int main()
{
	log_init();
	scheduler_init();
	display_controller_init();
	external_screen_init();
	i2c_init();

	wifi_init(nothing_callback);
	wifi_command_reset(); // reset the module. Because sometimes it just makes it work -_('o')_-  Software development at its best.
	native_delay_ms(2000);
	start();

	while (1)
	{
	}
}