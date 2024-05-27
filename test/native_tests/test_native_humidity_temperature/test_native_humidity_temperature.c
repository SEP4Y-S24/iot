#include "unity.h"
#include "../fff.h"
#include "../controllers/humidity_temperature.h"
#include "../comm/ccp_message_sender.h"
#include "../drivers/dht11.h"
#include "../utils/logger.h"
#include <stdio.h>

DEFINE_FFF_GLOBALS;
FAKE_VALUE_FUNC4(DHT11_ERROR_MESSAGE_t, dht11_get, uint8_t *, uint8_t *, uint8_t *, uint8_t *);
FAKE_VOID_FUNC2(ccp_message_sender_send_request, CCP_ACTION_TYPE, char *);
FAKE_VOID_FUNC1(log_debug, char *);

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

void test_humidity_temperature_get_in_string_format_success(void)
{
    dht11_get_fake.custom_fake = dht11_get_successful_custom_fake;

    char expected_message[30];
    sprintf(expected_message, "T%d.%d-H%d.%d", EXPECTED_TEMPERATURE_INT, EXPECTED_TEMPERATURE_DEC, EXPECTED_HUMIDITY_INT, EXPECTED_HUMIDITY_DEC);

    humidity_temperature_get_in_string_format(message_buffer);

    TEST_ASSERT_EQUAL_STRING(expected_message, message_buffer);
}

void test_humidity_temperature_get_in_string_format_fail(void)
{
    dht11_get_fake.custom_fake = dht11_get_failed_custom_fake;

    humidity_temperature_get_in_string_format(message_buffer);

    TEST_ASSERT_EQUAL_STRING(EXPECTED_FAILURE_MESSAGE, message_buffer);
}

void setUp(void)
{
    FFF_RESET_HISTORY();

    RESET_FAKE(dht11_get);
    RESET_FAKE(ccp_message_sender_send_request);
    RESET_FAKE(log_debug);
}

void tearDown(void)
{
}

int main(void)
{
    UNITY_BEGIN();

    // NOTICE - the code was refactored so this tests has to be changed
    // Test are passing locally but fail in the workflow with values:
    //
    // ccp_message_sender_send_request_fake.arg1_val = "="
    RUN_TEST(test_humidity_temperature_get_in_string_format_success);
    //
    // ccp_message_sender_send_request_fake.arg1_val = "H"
    RUN_TEST(test_humidity_temperature_get_in_string_format_fail);
    //
    // Exact cause was not found

    return UNITY_END();
}
