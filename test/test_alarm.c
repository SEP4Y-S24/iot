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
#include <buttons.h>
#include <ds3231.h>

FAKE_VOID_FUNC(periodic_task_init_c, PERIODIC_TASK_CALLBACK, uint32_t);
FAKE_VOID_FUNC(log_debug, char *);
FAKE_VOID_FUNC(log_info, char *);
FAKE_VOID_FUNC(hc_sr04_init);
FAKE_VALUE_FUNC(uint16_t, hc_sr04_takeMeasurement);
FAKE_VOID_FUNC(buzzer_beep);
FAKE_VOID_FUNC(native_delay_ms, int);
FAKE_VOID_FUNC(buzzer_init);
FAKE_VOID_FUNC(buzzer_on);
FAKE_VOID_FUNC(buzzer_off);
FAKE_VOID_FUNC(buttons_init);
FAKE_VALUE_FUNC0(uint8_t, buttons_1_pressed);

FAKE_VALUE_FUNC(uint8_t, read_hour);
FAKE_VALUE_FUNC(uint8_t, read_min);
FAKE_VOID_FUNC(ds3231_write_hour, uint8_t);
FAKE_VOID_FUNC(ds3231_write_min, uint8_t);

void alarm_init_should_set_alarm_set_and_active_to_false()
{
    alarm_init();
    TEST_ASSERT_FALSE(alarm_get_is_created());
}

void alarm_set_time_sets_alarm_to_set_and_active()
{
    alarm_create(10, 10);
    TEST_ASSERT_TRUE(alarm_get_is_created());
}

void alarm_unset_should_unset_alarm()
{
    alarm_delete();
    TEST_ASSERT_FALSE(alarm_get_is_created());
}

void alarm_check_should_beep_when_alarm_is_set_and_active()
{
    clock_set_time(10, 10);
    alarm_create(10, 10);
    alarm_check();
    TEST_ASSERT_TRUE(buzzer_beep_fake.call_count == 1);
}

int main(void)
{

    UNITY_BEGIN();
    RUN_TEST(alarm_init_should_set_alarm_set_and_active_to_false);
    RUN_TEST(alarm_set_time_sets_alarm_to_set_and_active);
    RUN_TEST(alarm_unset_should_unset_alarm);
    RUN_TEST(alarm_check_should_beep_when_alarm_is_set_and_active);

    return UNITY_END();
}

void setUp(void)
{
    ds3231_read_hour_fake.return_val = 10;
    ds3231_read_min_fake.return_val = 10;
}

void tearDown(void)
{
}

#endif