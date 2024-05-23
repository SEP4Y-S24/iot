#include "periodic_request.h"
#include "periodic_task.h"
#include "humidity_temperature.h"
#include "native.h"

static void periodic_request_10_minutes();

void periodic_request_10_minutes_init()
{
    periodic_task_init_b(periodic_request_10_minutes, 600000);
}

static void periodic_request_10_minutes()
{
    humidity_temperature_send();
    native_delay_ms(2000);
}