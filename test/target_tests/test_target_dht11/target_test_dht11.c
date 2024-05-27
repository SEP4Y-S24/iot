#include "unity.h"
#include "dht11.h"
#include <util/delay.h>
#include <avr/io.h>
#include <string.h>
#include <stdio.h>

void setUp(void)
{
    // This function is run before each test
}

void tearDown(void)
{
    // This function is run after each test
}

void test_dht11_get_valid_values(void)
{
    // Arrange
    uint8_t humidity_int, humidity_dec, temperature_int, temperature_dec;

    // Act
    DHT11_ERROR_MESSAGE_t result = dht11_get(&humidity_int, &humidity_dec, &temperature_int, &temperature_dec);

    // Assert
    TEST_ASSERT_EQUAL(DHT11_OK, result);
    TEST_ASSERT_TRUE(humidity_int >= 45 && humidity_int <= 65);
    TEST_ASSERT_TRUE(temperature_int >= 20 && temperature_int <= 30);
}

void test_dht11_get_repeated_failures(void)
{
    for (int i = 0; i < 5; i++)
    {
        uint8_t humidity_int, humidity_dec, temperature_int, temperature_dec;

        DHT11_ERROR_MESSAGE_t result = dht11_get(&humidity_int, &humidity_dec, &temperature_int, &temperature_dec);

        TEST_ASSERT_EQUAL(DHT11_FAIL, result);
    }
}

void setup()
{
    // Wait ~2 seconds before the Unity test runner
    // establishes connection with a board Serial interface
    _delay_ms(2000);

    UNITY_BEGIN();

    RUN_TEST(test_dht11_get_valid_values);
    RUN_TEST(test_dht11_get_repeated_failures);

    UNITY_END();
}

void loop()
{
    // Empty loop function as tests are run in setup
}
