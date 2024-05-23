/**
 * @file wifi.h
 * @author Laurits Ivar
 * @brief ESP8266 WiFi module interface using UART.
 * @version 0.1
 * @date 2023-08-23
 *
 * @copyright Copyright (c) 2023
 *
 */
#pragma once
#include <stdint.h>
#include "uart.h"
#include <stdbool.h>

/**
 * @brief Define which USART module is used for WiFi communication.
 *
 */
#define USART_WIFI USART_2

/**
 * @brief Enumerated list of possible error messages from the WiFi module.
 *
 */
typedef enum
{
    WIFI_OK,                     /**< Command successful. */
    WIFI_FAIL,                   /**< General failure or operation not successful. */
    WIFI_ERROR_RECEIVED_ERROR,   /**< Received an error message from the module. */
    WIFI_ERROR_NOT_RECEIVING,    /**< No data received from the module. */
    WIFI_ERROR_RECEIVING_GARBAGE /**< Received unintelligible data from the module. */
} WIFI_ERROR_MESSAGE_t;

typedef enum
{
    NO_AP,
    CONNECTED,
    UKNOWN
} WIFI_AP_CONNECTION;

/**
 * @brief Type definition for WiFi TCP data received callback.
 *
 */
typedef void (*WIFI_TCP_Callback_t)();

/**
 * @brief Type definition for WiFi server data received callback.
 *
 */
typedef void (*WIFI_SERVER_CALLBACK_t)(uint8_t data);
/**
 * @brief Initialize the WiFi module. After it have been initialized it can take up to 4 seconds before its ready.
 *
 */
void wifi_init(UART_Callback_t callback_state);

/**
 * @brief Send an AT command to the WiFi module to check if it's responsive.
 *
 * @return WIFI_ERROR_MESSAGE_t Error message based on the response from the module.
 */
WIFI_ERROR_MESSAGE_t wifi_command_AT();

/**
 * @brief Command the WiFi module to join a specific Access Point (AP). Also set the AP to default.
 *
 * @param ssid Network SSID to join.
 * @param password Password for the SSID.
 * @return WIFI_ERROR_MESSAGE_t Error message based on the response from the module.
 */
WIFI_ERROR_MESSAGE_t wifi_command_join_AP(char *ssid, char *password);

/**
 * @brief Disable echo from the WiFi module.
 *
 * @return WIFI_ERROR_MESSAGE_t Error message based on the response from the module.
 */
WIFI_ERROR_MESSAGE_t wifi_command_disable_echo();

/**
 * @brief Set the WiFi module to mode 1.
 *
 * @return WIFI_ERROR_MESSAGE_t Error message based on the response from the module.
 */
WIFI_ERROR_MESSAGE_t wifi_command_set_mode_to_1();

/**
 * @brief Set the WiFi module to mode 2.
 *
 * @return WIFI_ERROR_MESSAGE_t Error message based on the response from the module.
 */
WIFI_ERROR_MESSAGE_t wifi_command_set_mode_to_2();

/**
 * @brief Set the WiFi module to operate in single connection mode.
 *
 * @return WIFI_ERROR_MESSAGE_t Error message based on the response from the module.
 */
WIFI_ERROR_MESSAGE_t wifi_command_set_to_single_Connection();

/**
 * @brief Getting the ip based on the url. The user should provide a string with the URL and a buffer for the response
 *
 * @param url // The url
 * @param ip_address // a buffer for the IP, which the command returns
 * @return WIFI_ERROR_MESSAGE_t
 */
WIFI_ERROR_MESSAGE_t wifi_command_get_ip_from_URL(char *url, char *ip_address);
/**
 * @brief Establish a TCP connection using the WiFi module.
 *
 * @param IP IP address to connect to.
 * @param port Port number to use for the connection.
 * @param callback_when_message_received Callback executed when a message is received.
 * @param received_message_buffer Buffer to hold the received message.
 * @return WIFI_ERROR_MESSAGE_t Error message based on the response from the module.
 */
WIFI_ERROR_MESSAGE_t wifi_command_create_TCP_connection(char *IP, uint16_t port, WIFI_TCP_Callback_t callback_when_message_received, char *received_message_buffer);

/**
 * @brief Transmit data over an established TCP connection.
 *
 * @param data Pointer to the data to transmit.
 * @param length Length of the data to transmit.
 * @return WIFI_ERROR_MESSAGE_t Error message based on the response from the module.
 */
WIFI_ERROR_MESSAGE_t wifi_command_TCP_transmit(uint8_t *data, uint16_t length);

/**
 * @brief Disconnect from the current Access Point (AP).
 *
 * @return WIFI_ERROR_MESSAGE_t Error message based on the response from the module.
 */
WIFI_ERROR_MESSAGE_t wifi_command_quit_AP();

WIFI_ERROR_MESSAGE_t wifi_command(const char *str, uint16_t timeOut_s);
/**
 * @brief  Closes thhe TCP connection
 * @return WIFI_ERROR_MESSAGE_t Error message based on the response from the module.
 */
WIFI_ERROR_MESSAGE_t wifi_command_close_TCP_connection();

/*
 * @brief Setup the WiFi module as an Access Point (AP) (creates a hotspot)
 *
 * @param ssid Network SSID to create.
 * @param password Password for the SSID.
 * @return WIFI_ERROR_MESSAGE_t Error message based on the response from the module.
 */

WIFI_ERROR_MESSAGE_t wifi_command_setup_AP(char *ssid, char *password);

/**
 * @brief Enable multiple connections on the WiFi module.
 *
 * @return WIFI_ERROR_MESSAGE_t Error message based on the response from the module.
 */
WIFI_ERROR_MESSAGE_t wifi_command_enable_multiple_connections();

/*
 * @brief Setup the WiFi module as a server
 *
 * @param port Port number to use for the server.
 * @param callback_when_message_received Callback executed when a message is received.
 * @return WIFI_ERROR_MESSAGE_t Error message based on the response from the module.
 */
WIFI_ERROR_MESSAGE_t wifi_command_setup_server(uint16_t port, UART_Callback_t callback_when_message_received);

WIFI_AP_CONNECTION wifi_command_check_AP_connection();

WIFI_ERROR_MESSAGE_t wifi_command_reset();

WIFI_ERROR_MESSAGE_t wifi_command_set_mode_to_3();

void wifi_reassign_callback(WIFI_TCP_Callback_t new_callback, char *new_buffer);