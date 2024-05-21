#include "humidity_temperature.h"
#include "ccp_message_sender.h"
#include "dht11.h"
#include "logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Undeclared them from static so FFF can access them
void humidity_temperature_get(char *message_buffer);

void humidity_temperature_send()
{
    char request_message[30];
    log_debug("Sending Temperature and Humidity...");
    humidity_temperature_get(request_message);
    ccp_message_sender_send_request(CCP_AT_TH, request_message);
}

void humidity_temperature_get(char *message_buffer)
{
    log_debug("Getting Temperature and Humidity...");
    uint8_t temperature_int, temperature_dec, humidity_int, humidity_dec;
    if (dht11_get(&humidity_int, &humidity_dec, &temperature_int, &temperature_dec) == DHT11_OK)
    {
        sprintf(message_buffer, "T%d.%d-H%d.%d", temperature_int, temperature_dec, humidity_int, humidity_dec);
    }
    else
    {
        strcpy(message_buffer, "Failed attempt to get data.");
    }
}