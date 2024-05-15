#include "humidity_temperature.h"
#include "ccp_message_sender.h"
#include "dht11.h"
#include "logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    char number_stringified[8];
    if (dht11_get(&humidity_int, &humidity_dec, &temperature_int, &temperature_dec) == DHT11_OK)
    {
        sprintf(number_stringified, "%d.%d", temperature_int, temperature_dec);
        strcpy(message_buffer, "T");
        strcat(message_buffer, number_stringified);
        strcat(message_buffer, "-");
        sprintf(number_stringified, "%d.%d", humidity_int, humidity_dec);
        strcat(message_buffer, "H");
        strcat(message_buffer, number_stringified);
    }
    else
    {
        strcpy(message_buffer, "Failed attempt to get data.");
    }
}