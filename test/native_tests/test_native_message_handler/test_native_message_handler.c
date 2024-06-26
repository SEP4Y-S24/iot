#include "unity.h"
#include "../fff.h"
#include "../comm/ccp_message_handler.h"
#include "../comm/ccp_message_sender.h"
#include "../comm/ccp_protocol.h"
#include "../utils/logger.h"
#include "../controllers/message.h"
#include "../controllers/alarm.h"
#include "../drivers/wifi.h"
#include "../drivers/buzzer.h"
#include "../drivers/dht11.h"
#include "../drivers/periodic_task.h"
#include "../drivers/hc_sr04.h"
#include "../drivers/buttons.h"

DEFINE_FFF_GLOBALS;

FAKE_VOID_FUNC1(log_info, char *);
FAKE_VOID_FUNC1(log_debug, char *);
FAKE_VALUE_FUNC2(WIFI_ERROR_MESSAGE_t, wifi_command_TCP_transmit, uint8_t *, uint16_t);
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

char *external_screen_string = NULL;
FAKE_VOID_FUNC2(periodic_task_init_a, PERIODIC_TASK_CALLBACK, uint32_t);

void test_ms_message_clock_message_is_set_and_response_is_sent_buzzer_beeps()
{
    char message[] = "MS|5|hello|";
    ccp_message_handler_handle(message);
    TEST_ASSERT_EQUAL_STRING("hello", message_get_message());
    TEST_ASSERT_EQUAL(1, ccp_message_sender_send_response_fake.call_count);
    TEST_ASSERT_EQUAL(CCP_AT_MS, ccp_message_sender_send_response_fake.arg0_val);
    TEST_ASSERT_EQUAL(CCP_STATUS_OK, ccp_message_sender_send_response_fake.arg1_val);
    TEST_ASSERT_EQUAL(1, buzzer_beep_fake.call_count);
}

void test_tm_message_time_is_set()
{
    char message[] = "TM|1|4|1234|";
    ccp_message_handler_handle(message);
    TEST_ASSERT_EQUAL(12, ds3231_write_hour_fake.arg0_val);
    TEST_ASSERT_EQUAL(34, ds3231_write_min_fake.arg0_val);
}

void test_handle_alarm_message()
{
    char message[] = "CA|4|1234|";
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
    FFF_RESET_HISTORY();
    RESET_FAKE(log_info);
    RESET_FAKE(log_debug);
    RESET_FAKE(wifi_command_TCP_transmit);
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
