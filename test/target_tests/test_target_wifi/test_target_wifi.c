// COULD NOT FIND A WAY TO MAKE THE WI-FI MODULE TARGET TEST TO WORK
/*
    HardwareSerial0.cpp.o (symbol from plugin): In function `Serial':
    (.text+0x0): multiple definition of `__vector_25'
    uart.c.o (symbol from plugin):(.text+0x0): first defined here
    HardwareSerial0.cpp.o (symbol from plugin): In function `Serial':
    (.text+0x0): multiple definition of `__vector_26'
    uart.c.o (symbol from plugin):(.text+0x0): first defined here
*/
// Potentional fix was found by converting the file to a C++ since Serial is a C++ library

// Tests the Wi-fi module on target
#define WIFI_SSID "Correct Name"
#define WIFI_PASSWORD "Correct Password"
#define TCP_SERVER "192.168.56.1" // Should be running and in echo mode for the test to pass.
#define TCP_PORT 8080

#include "unity.h"
#include "wifi.h"
#include <util/delay.h>
#include <string.h>
#include <stdio.h>
#include "uart.h"

void setUp(void)
{
    wifi_init(NULL);
}

void tearDown(void)
{
}

void test_wifi_AT()
{

    TEST_ASSERT_EQUAL(WIFI_OK, wifi_command_AT());
}

void test_wifi_Connect_to_accessPoint_wrong_password()
{

    TEST_ASSERT_EQUAL(WIFI_FAIL, wifi_command_join_AP("Correct Name", "Wrong Password"));
}
void test_wifi_disable_echo()
{

    TEST_ASSERT_EQUAL(WIFI_OK, wifi_command_disable_echo());
}

void test_wifi_connect_to_AP_wrong_ssid()
{
    TEST_ASSERT_EQUAL(WIFI_FAIL, wifi_command_join_AP("Wrong Name", "Correct Password"));
}

void test_wifi_connect_to_AP_with_correct_ssid_and_password()
{
    TEST_ASSERT_EQUAL(WIFI_OK, wifi_command_join_AP(SSID, PASSWORD));
}

void test_wifi_set_to_mode_1()
{
    TEST_ASSERT_EQUAL(WIFI_OK, wifi_command_set_mode_to_1());
}
void test_wifi_set_to_single_connection()
{
    WIFI_ERROR_MESSAGE_t error = wifi_command_set_to_single_Connection();

    TEST_ASSERT_TRUE_MESSAGE(error == WIFI_OK || error == WIFI_ERROR_RECEIVED_ERROR, "Not WIFI_OK or WIFI_ERROR_RECEIVED_ERROR");

    char message[1024];
    if (error == WIFI_ERROR_RECEIVED_ERROR)
    {
        sprintf(message, "INFO! set wifi to single connection did not receive OK, because it already was setup to single connection         :1:_:PASS\n");
        TEST_MESSAGE(message); // TEST_MESSAGE("m e s s a g e :1:_:PASS\n");
    }
}

char received_buffer[128];
void receive()
{
    // uart_send_string_blocking(USART_0, received_buffer);
}
void test_wifi_create_TCP_connection()
{
    TEST_ASSERT_EQUAL(WIFI_OK, wifi_command_create_TCP_connection(TCP_SERVER, TCP_PORT, receive, received_buffer));
    TEST_ASSERT_EQUAL(WIFI_OK, wifi_command_TCP_transmit((uint8_t *)"1234567890", 4));
    _delay_ms(500);
}

void test_wifi_send_stuff()
{

    TEST_ASSERT_EQUAL(WIFI_OK, wifi_command_TCP_transmit((uint8_t *)"1234567890", 4));
    _delay_ms(500);
}

void test_wifi_receive_stuff()
{
    received_buffer[4] = '\0';
    _delay_ms(500);

    TEST_ASSERT_EQUAL_STRING("1234", received_buffer);
}

void test_wifi_close_tcp()
{
    TEST_ASSERT_EQUAL(WIFI_OK, wifi_command_close_TCP_connection());
}

void test_get_ip()
{
    char ip[60];
    TEST_ASSERT_EQUAL(WIFI_OK, wifi_command_get_ip_from_URL("dr.dk", ip));

    // TEST_ASSERT_EQUAL_STRING("2.23.172.130", ip);
}

void test_wifi_quit_AP()
{
    TEST_ASSERT_EQUAL(WIFI_OK, wifi_command_quit_AP());
}

int main(void)
{
    UNITY_BEGIN();
    _delay_ms(2000);

    RUN_TEST(test_wifi_AT);
    RUN_TEST(test_wifi_set_to_mode_1);
    RUN_TEST(test_wifi_set_to_single_connection);
    RUN_TEST(test_wifi_connect_to_AP_with_correct_ssid_and_password);
    RUN_TEST(test_wifi_create_TCP_connection);
    RUN_TEST(test_wifi_send_stuff);
    RUN_TEST(test_wifi_receive_stuff);
    RUN_TEST(test_wifi_close_tcp);
    RUN_TEST(test_get_ip);
    RUN_TEST(test_wifi_quit_AP);

    return UNITY_END();
}