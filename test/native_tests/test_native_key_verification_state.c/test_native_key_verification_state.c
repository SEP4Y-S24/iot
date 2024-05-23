#include "unity.h"
#include "../fff.h"
#include "../drivers/wifi.h"
#include "../drivers/periodic_task.h"
#include "../comm/ccp_message_sender.h"
#include "../comm/ccp_protocol.h"
#include "../utils/logger.h"
#include "../controllers/alarm.h"
#include "../controllers/message.h"
#include "../state/authentication_callback.h"
#include "../state/key_verification_state.h"
#include "../state/state_coordinator.h"
#include "../state/key_verification_callback.h"

FAKE_VALUE_FUNC(WIFI_ERROR_MESSAGE_t, wifi_command_TCP_transmit, uint8_t *, uint16_t);
FAKE_VOID_FUNC(uart_init, USART_t, uint32_t, UART_Callback_t);
FAKE_VOID_FUNC(uart_send_blocking, USART_t, uint8_t);

FAKE_VOID_FUNC(state_coordinator_wait_for_event, bool *);
FAKE_VOID_FUNC(uart_send_string_blocking, USART_t, char *);
FAKE_VOID_FUNC(log_debug, char *);
FAKE_VOID_FUNC(log_info, char *);
FAKE_VALUE_FUNC0(WIFI_ERROR_MESSAGE_t, wifi_command_set_mode_to_1);
FAKE_VALUE_FUNC0(WIFI_ERROR_MESSAGE_t, wifi_command_set_mode_to_2);
FAKE_VALUE_FUNC0(WIFI_ERROR_MESSAGE_t, wifi_command_set_mode_to_3);
FAKE_VALUE_FUNC2(WIFI_ERROR_MESSAGE_t, wifi_command_join_AP, char *, char *);
FAKE_VALUE_FUNC2(WIFI_ERROR_MESSAGE_t, wifi_command_setup_AP, char *, char *);
FAKE_VALUE_FUNC0(WIFI_ERROR_MESSAGE_t, wifi_command_enable_multiple_connections);
FAKE_VALUE_FUNC0(WIFI_ERROR_MESSAGE_t, wifi_command_reset);
FAKE_VALUE_FUNC2(WIFI_ERROR_MESSAGE_t, wifi_command_setup_server, uint16_t, UART_Callback_t);
FAKE_VOID_FUNC1(wifi_init, UART_Callback_t);
FAKE_VALUE_FUNC0(WIFI_AP_CONNECTION, wifi_command_check_AP_connection);
FAKE_VOID_FUNC(wifi_reassign_callback, WIFI_TCP_Callback_t, char *);
FAKE_VOID_FUNC(authentication_state_set_authenticated, bool);
FAKE_VOID_FUNC(authentication_state_set_waiting_for_key_verification, bool);

FAKE_VOID_FUNC(ccp_message_sender_send_request, CCP_ACTION_TYPE, char *);
FAKE_VOID_FUNC(key_verification_state_set_key_verified, bool);

void key_verification_state_sets_key()
{
    key_verification_state_set_key("hkasdterrhtadsgfdg");
    TEST_ASSERT_EQUAL_STRING("hkasdterrhtadsgfdg", message_get_message());
}

void auth_callback_sets_auth_key()
{
    authentication_callback("AU|3|5|key12|");
    TEST_ASSERT_EQUAL_STRING("key12", message_get_message());
}

void key_verification_callback_stops_waiting()
{
    key_verification_callback("KV|1|0|");
    TEST_ASSERT_EQUAL(1, key_verification_state_set_key_verified_fake.call_count);
    TEST_ASSERT_EQUAL(true, key_verification_state_set_key_verified_fake.arg0_val);
}

void setUp(void)
{
    FFF_RESET_HISTORY();
    RESET_FAKE(wifi_command_TCP_transmit);
    RESET_FAKE(uart_init);
    RESET_FAKE(uart_send_blocking);
    RESET_FAKE(state_coordinator_wait_for_event);
    RESET_FAKE(uart_send_string_blocking);
    RESET_FAKE(log_debug);
    RESET_FAKE(log_info);
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
    RESET_FAKE(wifi_reassign_callback);
    RESET_FAKE(authentication_state_set_authenticated);
    RESET_FAKE(authentication_state_set_waiting_for_key_verification);
    RESET_FAKE(ccp_message_sender_send_request);
    RESET_FAKE(key_verification_state_set_key_verified);
}

void tearDown(void)
{
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(key_verification_state_sets_key);
    RUN_TEST(auth_callback_sets_auth_key);
    RUN_TEST(key_verification_callback_stops_waiting);
    return UNITY_END();
}