#ifdef NATIVE_TEST_HUMIDITY_TEMPERATURE

#include "unity.h"
#include "humidity_temperature.h"
#include "ccp_message_sender.h"
#include "dht11.h"
#include "logger.h"
#include "../fff.h"
#include <stdio.h>

DEFINE_FFF_GLOBALS;
FAKE_VALUE_FUNC(DHT11_ERROR_MESSAGE_t, dht11_get, uint8_t *, uint8_t *, uint8_t *, uint8_t *);
FAKE_VOID_FUNC(ccp_message_sender_send_request, CCP_ACTION_TYPE, char *);
FAKE_VOID_FUNC(log_debug, char *);
FAKE_VOID_FUNC(log_info, char *);

char message_buffer[30];

const uint8_t EXPECTED_HUMIDITY_INT = 50;
const uint8_t EXPECTED_HUMIDITY_DEC = 5;
const uint8_t EXPECTED_TEMPERATURE_INT = 25;
const uint8_t EXPECTED_TEMPERATURE_DEC = 2;
const char EXPECTED_FAILURE_MESSAGE[] = "Failed attempt to get data.";

DHT11_ERROR_MESSAGE_t dht11_get_successful_custom_fake(uint8_t *humidity_int, uint8_t *humidity_dec, uint8_t *temperature_int, uint8_t *temperature_dec)
{
    *humidity_int = EXPECTED_HUMIDITY_INT;
    *humidity_dec = EXPECTED_HUMIDITY_DEC;
    *temperature_int = EXPECTED_TEMPERATURE_INT;
    *temperature_dec = EXPECTED_TEMPERATURE_DEC;
    return DHT11_OK;
}

DHT11_ERROR_MESSAGE_t dht11_get_failed_custom_fake(uint8_t *humidity_int, uint8_t *humidity_dec, uint8_t *temperature_int, uint8_t *temperature_dec)
{
    return DHT11_FAIL;
}

void setUp(void)
{
    FFF_RESET_HISTORY();
    RESET_FAKE(dht11_get);
    RESET_FAKE(ccp_message_sender_send_request);
}

void tearDown(void)
{
}

void test_humidity_temperature_send_success(void)
{
    dht11_get_fake.custom_fake = dht11_get_successful_custom_fake;

    char expected_message[30];
    sprintf(expected_message, "T%d.%d-H%d.%d", EXPECTED_TEMPERATURE_INT, EXPECTED_TEMPERATURE_DEC, EXPECTED_HUMIDITY_INT, EXPECTED_HUMIDITY_DEC);

    humidity_temperature_send();

    TEST_ASSERT_EQUAL(1, ccp_message_sender_send_request_fake.call_count);
    TEST_ASSERT_EQUAL(CCP_AT_TH, ccp_message_sender_send_request_fake.arg0_val);
    TEST_ASSERT_EQUAL_STRING(expected_message, ccp_message_sender_send_request_fake.arg1_val);
}

void test_humidity_temperature_send_fail(void)
{
    dht11_get_fake.custom_fake = dht11_get_failed_custom_fake;

    humidity_temperature_send();

    TEST_ASSERT_EQUAL(1, ccp_message_sender_send_request_fake.call_count);
    TEST_ASSERT_EQUAL(CCP_AT_TH, ccp_message_sender_send_request_fake.arg0_val);
    TEST_ASSERT_EQUAL_STRING(EXPECTED_FAILURE_MESSAGE, ccp_message_sender_send_request_fake.arg1_val);
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_humidity_temperature_send_success);
    RUN_TEST(test_humidity_temperature_send_fail);

    return UNITY_END();
}

#endif
