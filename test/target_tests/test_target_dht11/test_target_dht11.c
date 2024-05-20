#include "unity.h"
#include "dht11.h"
#include <util/delay.h>
#include <avr/io.h>
#include <string.h>
#include <stdio.h>

void setUp(void)
{
}

void tearDown(void)
{
}

void test_dht11_get_valid_values()
{
    uint8_t humidity_int, humidity_dec, temperature_int, temperature_dec;

    DHT11_ERROR_MESSAGE_t result = dht11_get(&humidity_int, &humidity_dec, &temperature_int, &temperature_dec);

    TEST_ASSERT_EQUAL(DHT11_OK, result);

    TEST_ASSERT_TRUE(humidity_int >= 15 && humidity_int <= 35);
    TEST_ASSERT_TRUE(temperature_int >= 20 && temperature_int <= 70);
}

void test_dht11_get_repeated_failures()
{
    for (int i = 0; i < 5; i++)
    {
        uint8_t humidity_int, humidity_dec, temperature_int, temperature_dec;

        DHT11_ERROR_MESSAGE_t result = dht11_get(&humidity_int, &humidity_dec, &temperature_int, &temperature_dec);

        TEST_ASSERT_EQUAL(DHT11_FAIL, result);
    }
}

int main(void)
{
    UNITY_BEGIN();

    // Wait ~2 seconds before the Unity test runner
    // establishes connection with a board Serial interface
    delay(2000);

    RUN_TEST(test_dht11_get_success);
    RUN_TEST(test_dht11_get_fail);

    return UNITY_END();
}