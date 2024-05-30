#include "humidity_temperature.h"
#include "../comm/ccp_message_sender.h"
#include "../drivers/dht11.h"
#include "../utils/logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void humidity_temperature_get_in_string_format(char *message_buffer)
{
    log_debug("Getting Temperature and Humidity...");
    uint8_t humidity_int, humidity_dec, temperature_int, temperature_dec;
    if (dht11_get(&humidity_int, &humidity_dec, &temperature_int, &temperature_dec) == DHT11_OK)
    {
        sprintf(message_buffer, "H-%d.%d-T-%d.%d", humidity_int, humidity_dec, temperature_int, temperature_dec);
    }
    else
    {
        strcpy(message_buffer, "Failed attempt to get data.");
    }
}