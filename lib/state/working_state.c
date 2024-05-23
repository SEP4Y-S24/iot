#include "working_state.h"
#include "state_coordinator.h"
#include "wifi.h"
#include "ccp_message_handler.h"
#include "periodic_request.h"
#include "logger.h"
#include "ccp_message_sender.h"
#include "native.h"

static void periodic_tasks_10_minutes();

static char message_buffer[CCP_MAX_MESSAGE_LENGTH];

static bool error;

static void nothing()
{
}

static void tcp_callback()
{
    ccp_message_handler_handle(message_buffer);
}

// I was not able to find any other way to change the tcp_callback, despite it only means reassign a single variable in wifi.c
// This is a workaround, the module tries to connect to the server it is already connected as a result nothing really happens. However, the callback and buffer are changed.
// However it takes 10 seconds
State working_state_switch(char *ip, int port)
{
    error = false;
    wifi_reassign_callback(tcp_callback, message_buffer);

    log_info("Entered working state");

    ccp_message_sender_send_request(CCP_AT_TM, "");
    native_delay_ms(2000);

    periodic_task_init_b(periodic_tasks_10_minutes, 10000);

    while (1)
    {
    }

    periodic_task_init_b(nothing, 10000);
    return WORKING_STATE; //Does not matter cause it only return in case of error 
}

static void periodic_tasks_10_minutes()
{

    humidity_temperature_send();
    native_delay_ms(2000);
    // c02_send();
}
