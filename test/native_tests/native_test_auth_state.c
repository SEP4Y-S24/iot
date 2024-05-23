#ifdef NATIVE_TEST_AUTH_STATE

#include "authentication_state.h"
#include "fff.h"
#include "ccp_protocol.h"
#include "unity.h"
#include "wifi.h"
#include "periodic_task.h"
#include "alarm.h"
#include "ccp_message_sender.h"
#include "authentication_callback.h"
#include "logger.h"
#include "state_coordinator.h"

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
FAKE_VOID_FUNC(key_verification_state_set_key_verified, bool);


FAKE_VOID_FUNC(ccp_message_sender_send_request, CCP_ACTION_TYPE, char *);

void auth_state_send_request()
{
    authentication_state_switch(NULL);
    TEST_ASSERT_EQUAL(ccp_message_sender_send_request_fake.call_count, 1);
    TEST_ASSERT_EQUAL(CCP_AT_AU, ccp_message_sender_send_request_fake.arg0_val);
}

void auth_callback_sets_auth()
{
    authentication_callback("AU|1|0||");
    TEST_ASSERT_EQUAL(1, authentication_state_set_authenticated_fake.call_count);
    TEST_ASSERT_EQUAL(true, authentication_state_set_authenticated_fake.arg0_val);
    TEST_ASSERT_EQUAL(1, authentication_state_set_waiting_for_key_verification_fake.call_count);
    TEST_ASSERT_EQUAL(false, authentication_state_set_waiting_for_key_verification_fake.arg0_val);
}

void auth_callback_unauthenticated_sets_key_verification_to_true()
{
    authentication_callback("AU|3|0||");
    TEST_ASSERT_EQUAL(authentication_state_set_waiting_for_key_verification_fake.call_count, 1);
    TEST_ASSERT_EQUAL(true, authentication_state_set_waiting_for_key_verification_fake.arg0_val);
}

void setUp()
{
    RESET_FAKE(authentication_state_set_authenticated);
    RESET_FAKE(authentication_state_set_waiting_for_key_verification);
}

void tearDown()
{
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(auth_state_send_request);
    RUN_TEST(auth_callback_sets_auth);
    RUN_TEST(auth_callback_unauthenticated_sets_key_verification_to_true);
    return UNITY_END();
}

#endif // TEST_AUTH_STATE