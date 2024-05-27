#include "unity.h"
#include "../fff.h"
#include "../comm/ccp_protocol.h"
#include "../drivers/periodic_task.h"
#include "../state/periodic_request.h"
#include "../controllers/humidity_temperature.h"

DEFINE_FFF_GLOBALS;
FAKE_VOID_FUNC2(periodic_task_init_b, PERIODIC_TASK_CALLBACK, uint32_t);
FAKE_VOID_FUNC1(log_debug, char *);
FAKE_VOID_FUNC1(humidity_temperature_get_in_string_format, char *);
FAKE_VOID_FUNC2(ccp_message_sender_send_request, CCP_ACTION_TYPE, char *)

void periodic_request_test_10_minutes_init()
{
    periodic_request_10_minutes_init();

    TEST_ASSERT_EQUAL_INT(1, periodic_task_init_b_fake.call_count);
}

void periodic_request_test_10_minutes_simulate_task()
{
    periodic_request_10_minutes_init();

    PERIODIC_TASK_CALLBACK captured_task = periodic_task_init_b_fake.arg0_val;
    captured_task();

    TEST_ASSERT_EQUAL_INT(1, humidity_temperature_get_in_string_format_fake.call_count);
}

void periodic_request_test_10_minutes_delay()
{
    periodic_request_10_minutes_init();

    TEST_ASSERT_EQUAL_INT(600000, periodic_task_init_b_fake.arg1_val);
}

int main(void)
{
    UNITY_BEGIN();

    // RUN 10 MINUTE PERIODIC REQUEST TEST
    RUN_TEST(periodic_request_test_10_minutes_init);
    RUN_TEST(periodic_request_test_10_minutes_simulate_task);
    RUN_TEST(periodic_request_test_10_minutes_delay);

    return UNITY_END();
}

void setUp(void)
{
    FFF_RESET_HISTORY();

    RESET_FAKE(periodic_task_init_b);
    RESET_FAKE(ccp_message_sender_send_request);
    RESET_FAKE(humidity_temperature_get_in_string_format);
    RESET_FAKE(log_debug);
}

void tearDown(void)
{
}