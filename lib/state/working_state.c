#include <working_state.h>
#include <state_coordinator.h>
#include <wifi.h>
#include "ccp_message_handler.h"
#include "humidity_temperature.h"
#include "uart.h"
#include "logger.h"
#include "ccp_message_sender.h"
#include "periodic_task.h"
#include "native.h"
#include "co2.h"

static void periodic_tasks_10_minutes();

static char message_buffer[128];

static void tcp_callback()
{
    ccp_message_handler_handle(message_buffer);
}

// I was not able to find any other way to change the tcp_callback, despite it only means reassign a single variable in wifi.c
// This is a workaround, the module tries to connect to the server it is already connected as a result nothing really happens. However, the callback and buffer are changed.
// However it takes 10 seconds
State working_state_switch(char *ip, int port)
{
    wifi_command_create_TCP_connection(ip, port, tcp_callback, message_buffer);

    log_info("Entered working state");

    ccp_message_sender_send_request(CCP_AT_TM, "");
    native_delay_ms(2000);

    periodic_task_init_b(periodic_tasks_10_minutes, 60000);

    while (1)
    {
    }

    return WORKING_STATE;
}

static void periodic_tasks_10_minutes()
{

    humidity_temperature_send();
    native_delay_ms(2000);
    c02_send();
}
