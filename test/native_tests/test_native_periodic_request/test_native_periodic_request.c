#include "unity.h"
#include "../../fff.h"
#include "../drivers/periodic_task.h"
#include "../controllers/periodic_request.h"
#include "../controllers/humidity_temperature.h"

FAKE_VOID_FUNC2(periodic_task_init_b, PERIODIC_TASK_CALLBACK, uint32_t);
FAKE_VOID_FUNC1(native_delay_ms, int);
FAKE_VOID_FUNC0(humidity_temperature_send);

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

    TEST_ASSERT_EQUAL_INT(1, humidity_temperature_send_fake.call_count);
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
    RESET_FAKE(native_delay_ms);
    RESET_FAKE(humidity_temperature_send);
}

void tearDown(void)
{
}