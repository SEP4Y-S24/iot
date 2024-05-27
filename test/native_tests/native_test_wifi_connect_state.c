#ifdef NATIVE_TEST_WIFI_CONNECT_STATE

#include <string.h>
#include <stdio.h>
#include <unity.h>
#include <unity_internals.h>
#include <stdlib.h>
#include "connect_wifi_state.h"
#include "../fff.h"
#include <wifi.h>
#include <periodic_task.h>
#include <state_coordinator.h>
#include <uart.h>
#include "dht11.h"
#include "logger.h"

FAKE_VOID_FUNC(periodic_task_init_b, PERIODIC_TASK_CALLBACK, uint32_t);
FAKE_VOID_FUNC(ds3231_write_hour, uint8_t);
FAKE_VOID_FUNC(ds3231_write_min, uint8_t);
FAKE_VALUE_FUNC(uint8_t, ds3231_read_hour);
FAKE_VALUE_FUNC(uint8_t, ds3231_read_min);
FAKE_VOID_FUNC(hc_sr04_init);
FAKE_VALUE_FUNC(uint16_t, hc_sr04_takeMeasurement);
FAKE_VOID_FUNC(buttons_init);
FAKE_VALUE_FUNC(uint8_t, buttons_1_pressed);
FAKE_VALUE_FUNC(uint8_t, buttons_2_pressed);
FAKE_VALUE_FUNC(uint8_t, buttons_3_pressed);
FAKE_VOID_FUNC(alarm_create, int, int);
FAKE_VOID_FUNC(alarm_delete, int, int);
FAKE_VOID_FUNC(alarm_init);

FAKE_VALUE_FUNC0(WIFI_ERROR_MESSAGE_t, wifi_command_set_mode_to_1);
FAKE_VALUE_FUNC0(WIFI_ERROR_MESSAGE_t, wifi_command_set_mode_to_2);
FAKE_VALUE_FUNC0(WIFI_ERROR_MESSAGE_t, wifi_command_set_mode_to_3);
FAKE_VALUE_FUNC(WIFI_ERROR_MESSAGE_t, wifi_command_TCP_transmit, uint8_t *, uint16_t);
FAKE_VALUE_FUNC(WIFI_ERROR_MESSAGE_t, wifi_command_create_TCP_connection, char *, uint16_t , WIFI_TCP_Callback_t , char *);
FAKE_VALUE_FUNC2(WIFI_ERROR_MESSAGE_t, wifi_command_join_AP, char *, char *);
FAKE_VALUE_FUNC2(WIFI_ERROR_MESSAGE_t, wifi_command_setup_AP, char *, char *);
FAKE_VALUE_FUNC0(WIFI_ERROR_MESSAGE_t, wifi_command_enable_multiple_connections);
FAKE_VALUE_FUNC0(WIFI_ERROR_MESSAGE_t, wifi_command_reset);
FAKE_VALUE_FUNC2(WIFI_ERROR_MESSAGE_t, wifi_command_setup_server, uint16_t, UART_Callback_t);
FAKE_VOID_FUNC1(wifi_init, UART_Callback_t);
FAKE_VOID_FUNC(wifi_reassign_callback, WIFI_TCP_Callback_t, char *);
FAKE_VALUE_FUNC0(WIFI_AP_CONNECTION, wifi_command_check_AP_connection);
FAKE_VOID_FUNC(authentication_state_set_authenticated, bool);
FAKE_VOID_FUNC(authentication_state_set_waiting_for_key_verification, bool);
FAKE_VOID_FUNC(key_verification_state_set_key_verified, bool);
FAKE_VOID_FUNC(buzzer_beep);
FAKE_VALUE_FUNC(DHT11_ERROR_MESSAGE_t, dht11_get, uint8_t*, uint8_t*, uint8_t*, uint8_t*);
FAKE_VOID_FUNC(log_debug, char *);
FAKE_VOID_FUNC(log_info, char *);

FAKE_VOID_FUNC(periodic_task_init_a, PERIODIC_TASK_CALLBACK, uint32_t);

void starting_with_specified_credentials_finishes_the_state()
{
  wifi_command_check_AP_connection_fake.return_val = CONNECTED;
  State state = connect_wifi_state_switch("ssid", "pass");
  TEST_ASSERT_EQUAL(SERVER_CONNECT_STATE, state);
  RESET_FAKE(wifi_command_check_AP_connection);
}

void starting_with_null_credentials_finishes_the_state_if_is_already_connected_to_wifi()
{
  wifi_command_check_AP_connection_fake.return_val = CONNECTED;
  State state = connect_wifi_state_switch(NULL, NULL);
  TEST_ASSERT_EQUAL(SERVER_CONNECT_STATE, state);
  RESET_FAKE(wifi_command_check_AP_connection);
}

int main(void)
{
  UNITY_BEGIN();
  RUN_TEST(starting_with_specified_credentials_finishes_the_state);
  RUN_TEST(starting_with_null_credentials_finishes_the_state_if_is_already_connected_to_wifi);
  return UNITY_END();
}

void setUp(void)
{
  FFF_RESET_HISTORY();
  RESET_FAKE(wifi_command_set_mode_to_1);
  RESET_FAKE(wifi_command_set_mode_to_2);
  RESET_FAKE(wifi_command_set_mode_to_3);
  RESET_FAKE(wifi_command_join_AP);
  RESET_FAKE(wifi_command_setup_AP);
  RESET_FAKE(wifi_command_enable_multiple_connections);
  RESET_FAKE(wifi_command_reset);
  RESET_FAKE(wifi_command_setup_server);
  RESET_FAKE(wifi_init);
  RESET_FAKE(wifi_command_check_AP_connection);
  RESET_FAKE(log_debug);
  RESET_FAKE(log_info);
  RESET_FAKE(periodic_task_init_a);
}

void tearDown(void)
{
}

#endif