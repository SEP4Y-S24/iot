#ifdef TEST_MESSAGE_HANDLER
#include "ccp_message_handler.h"
#include <fff.h>
#include <unity.h>
#include <logger.h>
#include <wifi.h>
#include <message.h>
#include <buzzer.h>
#include <ds3231.h>
#include <periodic_task.h>
#include <hc_sr04.h>
#include <buttons.h>
#include <ccp_protocol.h>
#include <alarm.h>
#include <ccp_message_sender.h>
FAKE_VOID_FUNC(log_info, char *);
FAKE_VOID_FUNC(log_debug, char *);
FAKE_VALUE_FUNC(WIFI_ERROR_MESSAGE_t, wifi_command_TCP_transmit, uint8_t *, uint16_t);
FAKE_VOID_FUNC(buzzer_beep);
FAKE_VOID_FUNC(buzzer_init);
FAKE_VOID_FUNC(buzzer_on);
FAKE_VOID_FUNC(buzzer_off);
FAKE_VOID_FUNC(periodic_task_init_c, PERIODIC_TASK_CALLBACK, uint32_t);
FAKE_VOID_FUNC(write_hour, uint8_t);
FAKE_VOID_FUNC(write_min, uint8_t);
FAKE_VALUE_FUNC(uint8_t, read_hour);
FAKE_VALUE_FUNC(uint8_t, read_min);
FAKE_VOID_FUNC(hc_sr04_init);
FAKE_VALUE_FUNC(uint16_t, hc_sr04_takeMeasurement);
FAKE_VOID_FUNC(buttons_init);
FAKE_VALUE_FUNC(uint8_t, buttons_1_pressed);
FAKE_VALUE_FUNC(uint8_t, buttons_2_pressed);
FAKE_VALUE_FUNC(uint8_t, buttons_3_pressed);
FAKE_VOID_FUNC(ccp_message_sender_send_response, CCP_ACTION_TYPE, CCP_STATUS_CODE, char *);
FAKE_VOID_FUNC(alarm_create, int, int);
FAKE_VALUE_FUNC(alarm_delete, int, int);
FAKE_VOID_FUNC(alarm_init);

void test_ms_message_clock_message_is_set_and_response_is_sent_buzzer_beeps()
{
    char message[] = "MS|4|helo";
    ccp_message_handler_handle(message);
    TEST_ASSERT_EQUAL_STRING("helo", message_get_message());
    TEST_ASSERT_EQUAL(1, ccp_message_sender_send_response_fake.call_count);
    TEST_ASSERT_EQUAL(CCP_AT_MS, ccp_message_sender_send_response_fake.arg0_val);
    TEST_ASSERT_EQUAL(CCP_STATUS_OK, ccp_message_sender_send_response_fake.arg1_val);
    TEST_ASSERT_EQUAL(1, buzzer_beep_fake.call_count);
}

void test_tm_message_time_is_set()
{
    char message[] = "TM|1|4|1234";
    ccp_message_handler_handle(message);
    TEST_ASSERT_EQUAL(12, write_hour_fake.arg0_val);
    TEST_ASSERT_EQUAL(34, write_min_fake.arg0_val);
}

void test_handle_alarm_message()
{
    char message[] = "CA|4|1234";
    ccp_message_handler_handle(message);
    TEST_ASSERT_EQUAL(1, ccp_message_sender_send_response_fake.call_count);
    TEST_ASSERT_EQUAL(CCP_AT_CA, ccp_message_sender_send_response_fake.arg0_val);
    TEST_ASSERT_EQUAL(CCP_STATUS_OK, ccp_message_sender_send_response_fake.arg1_val);
    TEST_ASSERT_EQUAL(1, alarm_create_fake.call_count);
    TEST_ASSERT_EQUAL(12, alarm_create_fake.arg0_val);
    TEST_ASSERT_EQUAL(34, alarm_create_fake.arg1_val);
}

void test_handle_delete_alarm_message()
{
    char message[] = "DA|0||";
    ccp_message_handler_handle(message);
    TEST_ASSERT_EQUAL(1, ccp_message_sender_send_response_fake.call_count);
    TEST_ASSERT_EQUAL(CCP_AT_DA, ccp_message_sender_send_response_fake.arg0_val);
    TEST_ASSERT_EQUAL(CCP_STATUS_OK, ccp_message_sender_send_response_fake.arg1_val);
    TEST_ASSERT_EQUAL(1, alarm_delete_fake.call_count);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_ms_message_clock_message_is_set_and_response_is_sent_buzzer_beeps);
    RUN_TEST(test_tm_message_time_is_set);
    RUN_TEST(test_handle_alarm_message);
    RUN_TEST(test_handle_delete_alarm_message);
    return UNITY_END();
}

void setUp(void)
{
    RESET_FAKE(ccp_message_sender_send_response);
    RESET_FAKE(log_info);
    RESET_FAKE(buzzer_beep);
    RESET_FAKE(write_hour);
    RESET_FAKE(write_min);
    RESET_FAKE(alarm_create);
    RESET_FAKE(alarm_delete);
}

void tearDown(void)
{
}

#endif
