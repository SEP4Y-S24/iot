#include "periodic_request.h"
#include "periodic_task.h"
#include "humidity_temperature.h"
#include "native.h"
#include "logger.h"
#include "ccp_message_sender.h"
#include "ccp_protocol.h"

static void periodic_request_10_minutes();
static void get_data();
static void send_data();
static char humidity_temperature_buffer[32];

void periodic_request_10_minutes_init()
{
    periodic_task_init_b(periodic_request_10_minutes, 10000);
}

static void periodic_request_10_minutes()
{
    get_data();
    send_data();
}

static void get_data()
{
    humidity_temperature_get_in_string_format(humidity_temperature_buffer);
}

static void send_data()
{
    log_debug("Sending Temperature and Humidity...");
    ccp_message_sender_send_request(CCP_AT_TH, humidity_temperature_buffer);
}

static void periodic_request_nothing()
{
}

void periodic_request_10_minutes_stop()
{
    periodic_task_init_b(periodic_request_nothing, 10000);
}