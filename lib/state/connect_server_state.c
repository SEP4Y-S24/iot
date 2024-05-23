#include <state_coordinator.h>
#include <connect_server_state.h>
#include <wifi.h>
#include <stddef.h>
#include <logger.h>
#include <ccp_protocol.h>

void nothing(){
    
}

State connect_server_state_switch(char *ip, int port)
{
    wifi_command_set_mode_to_1();
    log_info("Entered connect server state");
    char buffer[CCP_MAX_MESSAGE_LENGTH];
    wifi_command_create_TCP_connection(ip, port, nothing, buffer);
    /*
    authentication comes here
    */
    return AUTHENTICATION_STATE;
}
