#include <state_coordinator.h>
#include <connect_server_state.h>
#include <wifi.h>
#include <stddef.h>
#include <logger.h>
#include <ccp_protocol.h>
#include "native.h"

void nothing(){
    
}

State connect_server_state_switch(char *ip, int port)
{
    wifi_command_set_mode_to_1();
    log_info("Entered connect server state");
    char buffer[CCP_MAX_MESSAGE_LENGTH];
    WIFI_ERROR_MESSAGE_t result = WIFI_ERROR_NOT_RECEIVING;
    while (result != WIFI_OK)
    {
        result = wifi_command_create_TCP_connection(ip, port, nothing, buffer);
        native_delay_ms(2000);
    }
    /*
    authentication comes here
    */
    return AUTHENTICATION_STATE;
}
