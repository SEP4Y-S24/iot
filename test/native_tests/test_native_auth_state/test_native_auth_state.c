#include "unity.h"
#include "../fff.h"
#include "../drivers/wifi.h"
#include "../drivers/periodic_task.h"
#include "../drivers/ds3231.h"
#include "../controllers/alarm.h"
#include "../controllers/display_controller.h"
#include "../comm/ccp_message_sender.h"
#include "../comm/ccp_protocol.h"
#include "../state/authentication_state.h"
#include "../state/authentication_callback.h"
#include "../state/state_coordinator.h"
#include "../utils/logger.h"
#include "../drivers/buttons.h"

DEFINE_FFF_GLOBALS;

char *external_screen_string = NULL;

FAKE_VALUE_FUNC(WIFI_ERROR_MESSAGE_t, wifi_command_TCP_transmit, uint8_t *, uint16_t);
FAKE_VOID_FUNC(uart_init, USART_t, uint32_t, UART_Callback_t);
FAKE_VOID_FUNC(uart_send_blocking, USART_t, uint8_t);
FAKE_VOID_FUNC(state_coordinator_wait_for_event, bool *);
FAKE_VOID_FUNC(uart_send_string_blocking, USART_t, char *);
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
FAKE_VOID_FUNC2(authentication_state_set_authenticated, bool, char *);
FAKE_VOID_FUNC(authentication_state_set_waiting_for_key_verification, bool);
FAKE_VOID_FUNC(key_verification_state_set_key_verified, bool);
FAKE_VOID_FUNC(log_debug, char *);
FAKE_VOID_FUNC(log_info, char *);
FAKE_VOID_FUNC(ccp_message_sender_send_request, CCP_ACTION_TYPE, char *);

FAKE_VOID_FUNC0(buzzer_beep);
FAKE_VOID_FUNC0(buzzer_init);
FAKE_VOID_FUNC0(buzzer_on);
FAKE_VOID_FUNC0(buzzer_off);
FAKE_VOID_FUNC2(periodic_task_init_c, PERIODIC_TASK_CALLBACK, uint32_t);
FAKE_VOID_FUNC1(ds3231_write_hour, uint8_t);
FAKE_VOID_FUNC1(ds3231_write_min, uint8_t);
FAKE_VALUE_FUNC0(uint8_t, ds3231_read_hour);
FAKE_VALUE_FUNC0(uint8_t, ds3231_read_min);
FAKE_VOID_FUNC0(hc_sr04_init);
FAKE_VALUE_FUNC0(uint16_t, hc_sr04_takeMeasurement);
FAKE_VOID_FUNC0(buttons_init);
FAKE_VALUE_FUNC0(uint8_t, buttons_1_pressed);
FAKE_VALUE_FUNC0(uint8_t, buttons_2_pressed);
FAKE_VALUE_FUNC0(uint8_t, buttons_3_pressed);
FAKE_VOID_FUNC3(ccp_message_sender_send_response, CCP_ACTION_TYPE, CCP_STATUS_CODE, char *);
FAKE_VOID_FUNC2(alarm_create, int, int);
FAKE_VOID_FUNC2(alarm_delete, int, int);
FAKE_VOID_FUNC0(alarm_init);

// Mock periodic_task_init_a
FAKE_VOID_FUNC2(periodic_task_init_a, PERIODIC_TASK_CALLBACK, uint32_t);

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

void setUp(void)
{
    FFF_RESET_HISTORY();

    RESET_FAKE(wifi_command_TCP_transmit);
    RESET_FAKE(uart_init);
    RESET_FAKE(uart_send_blocking);
    RESET_FAKE(state_coordinator_wait_for_event);
    RESET_FAKE(uart_send_string_blocking);
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
    RESET_FAKE(key_verification_state_set_key_verified);
    RESET_FAKE(log_debug);
    RESET_FAKE(log_info);
    RESET_FAKE(ccp_message_sender_send_request);

    RESET_FAKE(buzzer_beep);
    RESET_FAKE(buzzer_init);
    RESET_FAKE(buzzer_on);
    RESET_FAKE(buzzer_off);
    RESET_FAKE(periodic_task_init_c);
    RESET_FAKE(ds3231_write_hour);
    RESET_FAKE(ds3231_write_min);
    RESET_FAKE(ds3231_read_hour);
    RESET_FAKE(ds3231_read_min);
    RESET_FAKE(hc_sr04_init);
    RESET_FAKE(hc_sr04_takeMeasurement);
    RESET_FAKE(buttons_init);
    RESET_FAKE(buttons_1_pressed);
    RESET_FAKE(buttons_2_pressed);
    RESET_FAKE(buttons_3_pressed);
    RESET_FAKE(ccp_message_sender_send_response);
    RESET_FAKE(alarm_create);
    RESET_FAKE(alarm_delete);
    RESET_FAKE(alarm_init);
    RESET_FAKE(periodic_task_init_a); 
}

void tearDown(void)
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
