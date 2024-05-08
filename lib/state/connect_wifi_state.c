#ifndef NATIVE_TESTING
#include <util/delay.h>
#endif

#include "connect_wifi_state.h"
#include "wifi.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <utils.h>
#include <stdbool.h>
#include <state_coordinator.h>
#include <periodic_task.h>
#include "logger.h"

static char recieveBuffer[128];
static uint8_t recieveBufferIndex;
static bool wifi_connected = false;

static char ssid_static[32];
static char password_static[32];

// Define a function pointer type for the callback
typedef void (*RecieveDataCallback)(uint8_t);
typedef void (*DataRecievedCallback)(void);

static DataRecievedCallback data_recieved_callback_static;

void setup_server(RecieveDataCallback callback, DataRecievedCallback data_recieve_callback);
void connect_to_wifi();
void data_recieve_callback(uint8_t data);
void clear_buffer();
void wifi_check_buffer_callback();

void connect_to_wifi()
{
    log_debug(ssid_static);
    log_debug(password_static);
    WIFI_ERROR_MESSAGE_t result = wifi_command_join_AP(ssid_static, password_static);
    if (result != WIFI_OK)
    {
        setup_server(data_recieve_callback, wifi_check_buffer_callback);
    }
    else
    {
        wifi_connected = true;
    }
}

void setup_server(RecieveDataCallback callback, DataRecievedCallback data_recieve_callback)
{
    wifi_command_setup_AP("SEP4-SmartClock", "MHDK2024");
    wifi_command_enable_multiple_connections();
    recieveBufferIndex = 0;
    wifi_command_setup_server(80, callback);
    data_recieved_callback_static = data_recieve_callback;
}

void data_recieve_callback(uint8_t data)
{
    static enum { IDLE,
                  MATCH_PREFIX,
                  LENGTH,
                  DATA } state = IDLE;
    static int length = 0, index = 0;
    char *prefix = "data:";
    char terminator = ';';
    switch (state)
    {
    case IDLE:
        if (data == 'd')
        {
            state = MATCH_PREFIX;
            index++;
        }
        break;
    case MATCH_PREFIX:
        if (data == prefix[index])
        {
            index++;
            if (index == 5)
            {
                state = LENGTH;
                index = 0;
            }
        }
        else
        {
            state = IDLE;
            index = 0;
        }
        break;
    case LENGTH:
        if (data >= '0' && data <= '9')
        {
            length = length * 10 + (data - '0');
        }
        else if (data == terminator)
        {
            state = DATA;
            index = 0; // reset index to start storing data
        }
        else
        {
            // not the expected character, reset to IDLE
            state = IDLE;
            length = 0;
        }
        break;
    case DATA:
        recieveBuffer[recieveBufferIndex] = data;
        recieveBufferIndex++;
        if (recieveBufferIndex == length)
        {
            data_recieved_callback_static();
            recieveBuffer[recieveBufferIndex] = 0;
            recieveBufferIndex = 0;
            state = IDLE;
            length = 0;
            index = 0;
        }
        break;
    default:
        break;
    }
}

void clear_buffer()
{
    for (uint16_t i = 0; i < 128; i++)
        recieveBuffer[i] = 0;
    recieveBufferIndex = 0;
}

// checks the buffer for ssid and pass and then sends the command to connect to the AP
void wifi_check_buffer_callback()
{
    char *ssidString = strstr((char *)recieveBuffer, "ssid:");
    char *passString = strstr((char *)recieveBuffer, "pass:");

    log_debug((char *)recieveBuffer);
    if (ssidString != NULL && passString != NULL)
    {
        log_debug("ssid and pass found");
        int lengthTerminatorIndex = utils_find_char_index_in_string(ssidString, ';');
        int passTerminatorIndex = utils_find_char_index_in_string(passString, ';');

        char ssidLengthString[lengthTerminatorIndex + 1];
        char passLengthString[passTerminatorIndex + 1];

        for (size_t i = 5; i < lengthTerminatorIndex; i++)
        {
            ssidLengthString[i - 5] = ssidString[i];
        }
        ssidLengthString[lengthTerminatorIndex] = '\0';

        for (size_t i = 5; i < passTerminatorIndex; i++)
        {
            passLengthString[i - 5] = passString[i];
        }
        passLengthString[passTerminatorIndex] = '\0';

        int ssidLength = atoi(ssidLengthString);
        int passLength = atoi(passLengthString);

        char ssid[ssidLength + 1];
        char pass[passLength + 1];

        memcpy(ssid, ssidString + lengthTerminatorIndex + 1, ssidLength);
        memcpy(pass, passString + passTerminatorIndex + 1, passLength);
        ssid[ssidLength] = '\0';
        pass[passLength] = '\0';

        strcpy(ssid_static, ssid);
        strcpy(password_static, pass);
        connect_to_wifi();
    }
    clear_buffer();
}

State connect_wifi_state_switch(char *ssid, char *pass)
{
    log_info("Entered connect wifi state");
    wifi_init(NULL);

    // wifi_command_reset();
    //_delay_ms(5000);

    wifi_command_set_mode_to_3();
    // If ssid and pass are not NULL, then the device tries to connect to the wifi
    if (ssid != NULL && pass != NULL)
    {
        wifi_command_join_AP(ssid, pass);
        strcpy(ssid_static, ssid);
        strcpy(password_static, pass);
    }

    // Check if the device is already connected to the AP
    if (wifi_command_check_AP_connection() == CONNECTED)
    {
        log_debug("Connected to wifi");
        return SERVER_CONNECT_STATE;
    }
    // If not connected to an AP, start a server and wait for ssid and pass
    else
    {
        setup_server(data_recieve_callback, wifi_check_buffer_callback);
        periodic_task_init_a(connect_to_wifi, 60000);
    }

    while (!wifi_connected)
    {
    }
    periodic_task_init_a(NULL, 60000);
    log_debug("Connected to wifi");

    return SERVER_CONNECT_STATE;
}
