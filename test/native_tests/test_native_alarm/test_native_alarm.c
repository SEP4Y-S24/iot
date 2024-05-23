#include <unity.h>
#include "../fff.h"
#include "../drivers/periodic_task.h"
#include "../drivers/buzzer.h"
#include "../drivers/native.h"
#include "../drivers/hc_sr04.h"
#include "../drivers/buttons.h"
#include "../drivers/ds3231.h"
#include "../utils/logger.h"
#include "../controllers/clock.h"
#include "../controllers/alarm.h"

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

FAKE_VALUE_FUNC(uint8_t, ds3231_read_hour);
FAKE_VALUE_FUNC(uint8_t, ds3231_read_min);
FAKE_VOID_FUNC(ds3231_write_hour, uint8_t);
FAKE_VOID_FUNC(ds3231_write_min, uint8_t);

void setUp(void)
{
    FFF_RESET_HISTORY();
    RESET_FAKE(periodic_task_init_c);
    RESET_FAKE(log_debug);
    RESET_FAKE(log_info);
    RESET_FAKE(hc_sr04_init);
    RESET_FAKE(hc_sr04_takeMeasurement);
    RESET_FAKE(buzzer_beep);
    RESET_FAKE(native_delay_ms);
    RESET_FAKE(buzzer_init);
    RESET_FAKE(buzzer_on);
    RESET_FAKE(buzzer_off);
    RESET_FAKE(buttons_init);
    RESET_FAKE(buttons_1_pressed);
    RESET_FAKE(ds3231_read_hour);
    RESET_FAKE(ds3231_read_min);
    RESET_FAKE(ds3231_write_hour);
    RESET_FAKE(ds3231_write_min);

    alarm_init();
    ds3231_read_hour_fake.return_val = 10;
    ds3231_read_min_fake.return_val = 10;
}

void tearDown(void)
{
}

void alarm_init_should_set_alarm_set_and_active_to_false()
{
    alarm_init();
    TEST_ASSERT_TRUE(alarm_get_alarm_count() == 0);
}

void alarm_set_time_sets_alarm_to_set_and_active()
{
    alarm_init();
    alarm_create(10, 10);
    TEST_ASSERT_TRUE(alarm_get_alarm_count() == 1);
}

void alarm_unset_should_unset_alarm()
{
    alarm_init();
    alarm_create(10, 10);
    alarm_delete(10, 10);
    TEST_ASSERT_TRUE(alarm_get_alarm_count() == 0);
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
