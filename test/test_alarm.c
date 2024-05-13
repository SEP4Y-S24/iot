#ifdef TEST_ALARM

#include <unity.h>
#include <alarm.h>
#include <fff.h>
#include <periodic_task.h>
#include <buzzer.h>
#include <native.h>
#include <hc_sr04.h>
#include <logger.h>
#include <clock.h>

FAKE_VOID_FUNC(periodic_task_init_c, PERIODIC_TASK_CALLBACK, uint32_t);
FAKE_VOID_FUNC(log_debug, char *);
FAKE_VOID_FUNC(log_info, char *);
FAKE_VOID_FUNC(hc_sr04_init);
FAKE_VALUE_FUNC(uint16_t, hc_sr04_takeMeasurement);
FAKE_VOID_FUNC(buzzer_beep);
FAKE_VOID_FUNC(native_delay_ms, int);

void alarm_init_should_set_alarm_set_and_active_to_false()
{
    alarm_init();
    TEST_ASSERT_FALSE(alarm_get_is_created());
    TEST_ASSERT_FALSE(alarm_get_is_active());
}

void alarm_set_time_sets_alarm_to_set_and_active()
{
    alarm_set(10, 10);
    TEST_ASSERT_TRUE(alarm_get_is_created());
    TEST_ASSERT_TRUE(alarm_get_is_active());
}

void alarm_unset_should_unset_alarm()
{
    alarm_unset();
    TEST_ASSERT_FALSE(alarm_get_is_created());
    TEST_ASSERT_FALSE(alarm_get_is_active());
}

void alarm_stop_should_stop_alarm()
{
    alarm_stop();
    TEST_ASSERT_FALSE(alarm_get_is_active());
    TEST_ASSERT_TRUE(alarm_get_is_stoped);
}

void alarm_check_should_beep_when_alarm_is_set_and_active()
{
    clock_set_time(10, 10);
    alarm_set(10, 10);
    alarm_check();
    TEST_ASSERT_TRUE(buzzer_beep_fake.call_count == 1);
}

int main(void)
{

    UNITY_BEGIN();
    RUN_TEST(alarm_init_should_set_alarm_set_and_active_to_false);
    RUN_TEST(alarm_set_time_sets_alarm_to_set_and_active);
    RUN_TEST(alarm_unset_should_unset_alarm);
    RUN_TEST(alarm_stop_should_stop_alarm);
    RUN_TEST(alarm_check_should_beep_when_alarm_is_set_and_active);

    return UNITY_END();
}

void setUp(void)
{
}

void tearDown(void)
{
}

#endif