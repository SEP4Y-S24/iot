#include "connect_server_state.h"
#include "state_coordinator.h"
#include "../comm/ccp_protocol.h"
#include "../comm/ccp_message_sender.h"
#include "../drivers/wifi.h"
#include "../utils/native.h"
#include "../utils/logger.h"
#include "../encryption/key_exchange.h"
#include "../encryption/cryptorator.h"
#include <stddef.h>
#include <string.h>

static void handle_key_exchange();

static bool public_key_received = false;
static bool public_key_sent = false;

static char message_buffer[128];

static void copy_key(char *buffer)
{
    strncpy(buffer, message_buffer + 6, 64); // + 6 because SK|64|
    buffer[64] = '\0';
}

void receive_cloud_public_key()
{
    CCP_ACTION_TYPE at = ccp_at_from_str(message_buffer);
    log_debug(message_buffer);
    if (at == CCP_AT_SK)
    {
        char key[65];
        copy_key(key); // extracts the key from the message
        log_debug("Received public key from server");
        log_debug(key);
        uint8_t shared_secret[17];
        key_exchange_generate_shared_secret((uint8_t *)key, shared_secret); //
        public_key_received = true;
        cryptorator_init(shared_secret);
    }
}

State connect_server_state_switch(char *ip, int port)
{
    wifi_command_set_mode_to_1();
    log_info("Entered connect server state");

    char buffer[CCP_MAX_MESSAGE_LENGTH];
    WIFI_ERROR_MESSAGE_t result = WIFI_ERROR_NOT_RECEIVING;
    while (result != WIFI_OK)
    {
        result = wifi_command_create_TCP_connection(ip, port, receive_cloud_public_key, buffer);
        native_delay_ms(2000);
    }

#ifndef ENCRYPTION_DISABLED
    handle_key_exchange();
    while (!public_key_received || !public_key_sent)
    {
        if (!public_key_sent)
        {
            log_info("Sending public key to server");
        }
        if (!public_key_received)
        {
            log_info("Waiting for public key from server");
        }
        native_delay_ms(5000);
    }
#endif

    /*
    authentication comes here
    */
    return AUTHENTICATION_STATE;
}

static void handle_key_exchange()
{
    uint8_t public_key[33];
    key_echange_init();
    key_exchange_generate_keys(); // generates public and private keys
    key_exchange_get_public_key(public_key);
    log_debug("Public key generated:");
    log_debug((char *)public_key);
    ccp_message_sender_send_request(CCP_AT_SK, (char *)public_key); // sends public key to servers
    public_key_sent = true;
}