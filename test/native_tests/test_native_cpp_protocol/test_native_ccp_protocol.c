#include <unity.h>
#include <ccp_protocol.h>
#include <stdio.h>
#include "../fff.h"
#include <wifi.h>
#include <uart.h>

FAKE_VALUE_FUNC(WIFI_ERROR_MESSAGE_t, wifi_command_TCP_transmit, uint8_t *, uint16_t);
FAKE_VOID_FUNC(uart_init, USART_t, uint32_t, UART_Callback_t);
FAKE_VOID_FUNC(uart_send_blocking, USART_t, uint8_t);
FAKE_VOID_FUNC(uart_send_array_nonBlocking, USART_t, uint8_t *, uint16_t);
FAKE_VOID_FUNC(uart_send_array_blocking, USART_t, uint8_t *, uint16_t);
FAKE_VOID_FUNC(uart_send_string_blocking, USART_t, char *);

void ccp_test_create_request_without_body()
{
    char buffer[100];
    ccp_create_request(CCP_AT_TM, "", buffer);
    TEST_ASSERT_EQUAL_STRING("TM|0||", buffer);
}

void ccp_test_create_request_with_body()
{
    char buffer[100];
    ccp_create_request(CCP_AT_MS, "Hello, World!", buffer);
    TEST_ASSERT_EQUAL_STRING("MS|13|Hello, World!|", buffer);
}

void ccp_test_create_response_without_body()
{
    char buffer[100];
    ccp_create_response(buffer, CCP_AT_TM, CCP_STATUS_OK, "");
    TEST_ASSERT_EQUAL_STRING("TM|1|0||", buffer);
}

void ccp_test_create_response_with_body()
{
    char buffer[100];
    ccp_create_response(buffer, CCP_AT_MS, CCP_STATUS_SERVER_ERROR, "Internal Server Error");
    TEST_ASSERT_EQUAL_STRING("MS|2|21|Internal Server Error|", buffer);
}

void ccp_test_parse_response_with_unknown_action_type()
{
    char raw_response[] = "XX|1|11|Hello World|";

    response test_response;
    CCP_PARSING_STATUS parsing_status = ccp_parse_response(raw_response, &test_response);

    TEST_ASSERT_TRUE(CCP_PARSING_VALID == parsing_status);
    TEST_ASSERT_EQUAL_STRING("Hello World", test_response.body);
    TEST_ASSERT_TRUE(CCP_STATUS_OK == test_response.status_code);
    TEST_ASSERT_TRUE(CCP_AT_UNKNOWN == test_response.action_type);
}

void ccp_test_parse_response_with_unknown_status_code()
{
    char raw_response[] = "MS|9|11|Hello World|";

    response test_response;
    CCP_PARSING_STATUS parsing_status = ccp_parse_response(raw_response, &test_response);

    TEST_ASSERT_TRUE(CCP_PARSING_VALID == parsing_status);
    TEST_ASSERT_EQUAL(CCP_AT_MS, test_response.action_type);
    TEST_ASSERT_EQUAL_STRING("Hello World", test_response.body);
    TEST_ASSERT_TRUE(CCP_STATUS_NUM_STATUS_CODES == test_response.status_code);
}

void ccp_test_parse_response_with_empty_body()
{
    char raw_response[] = "MS|1|0|";

    response test_response;
    CCP_PARSING_STATUS parsing_status = ccp_parse_response(raw_response, &test_response);
    TEST_ASSERT_TRUE(CCP_PARSING_VALID == parsing_status);
    TEST_ASSERT_EQUAL(CCP_STATUS_OK, test_response.status_code);
    TEST_ASSERT_EQUAL_STRING("", test_response.body);
}

void ccp_test_parse_response_no_body_length()
{
    char raw_response[] = "MS|1||Hello World|";

    response test_response;
    CCP_PARSING_STATUS parsing_status = ccp_parse_response(raw_response, &test_response);
    TEST_ASSERT_TRUE(CCP_PARSING_INVALID_WRONG_FORMAT == parsing_status);
}

void ccp_test_parse_response_only_action_type()
{
    char raw_response[] = "MS|||";

    response test_response;
    CCP_PARSING_STATUS parsing_status = ccp_parse_response(raw_response, &test_response);
    TEST_ASSERT_TRUE(CCP_PARSING_INVALID_WRONG_FORMAT == parsing_status);
}

void ccp_test_parse_response_with_too_long_body()
{
    char raw_response[] = "MS|1|100|Body length is set to be too long.|";

    response test_response;
    CCP_PARSING_STATUS parsing_status = ccp_parse_response(raw_response, &test_response);

    TEST_ASSERT_TRUE(CCP_PARSING_INVALID_WRONG_FORMAT == parsing_status);
    TEST_ASSERT_TRUE(CCP_AT_MS == test_response.action_type);
    TEST_ASSERT_EQUAL(CCP_STATUS_OK, test_response.status_code);
    TEST_ASSERT_EQUAL_STRING("", test_response.body);
}

void ccp_test_parse_response_without_body()
{
    char raw_response[] = "MS|1|";

    response test_response;
    CCP_PARSING_STATUS parsing_status = ccp_parse_response(raw_response, &test_response);

    TEST_ASSERT_TRUE(CCP_PARSING_INVALID_WRONG_FORMAT == parsing_status);
    TEST_ASSERT_EQUAL_STRING("", test_response.body);
}

void ccp_test_parse_response_with_action_type()
{
    char raw_response[] = "MS|1|10|Hello World|";

    response test_response;
    CCP_PARSING_STATUS parsing_status = ccp_parse_response(raw_response, &test_response);

    TEST_ASSERT_TRUE(CCP_PARSING_VALID == parsing_status);
    TEST_ASSERT_TRUE(CCP_AT_MS == test_response.action_type);
}

void ccp_test_parse_response_with_status_code()
{
    char raw_response[] = "MS|1|10|Hello World|";

    response test_response;
    CCP_PARSING_STATUS parsing_status = ccp_parse_response(raw_response, &test_response);

    TEST_ASSERT_TRUE(CCP_PARSING_VALID == parsing_status);
    TEST_ASSERT_TRUE(CCP_STATUS_OK == test_response.status_code);
}

void ccp_test_parse_response_with_body()
{
    char raw_response[] = "MS|1|11|Hello World|";

    response test_response;
    CCP_PARSING_STATUS parsing_status = ccp_parse_response(raw_response, &test_response);

    TEST_ASSERT_TRUE(CCP_PARSING_VALID == parsing_status);
    TEST_ASSERT_EQUAL_STRING("Hello World", test_response.body);
}

void ccp_test_parse_request_with_unknown_action_type()
{
    char raw_request[] = "XX|11|Hello World|";

    request test_request;
    CCP_PARSING_STATUS parsing_status = ccp_parse_request(raw_request, &test_request);

    TEST_ASSERT_TRUE(CCP_PARSING_VALID == parsing_status);
    TEST_ASSERT_TRUE(CCP_AT_UNKNOWN == test_request.action_type);
}

void ccp_test_parse_request_with_empty_body()
{
    char raw_request[] = "CA|0|";

    request test_request;
    CCP_PARSING_STATUS parsing_status = ccp_parse_request(raw_request, &test_request);

    TEST_ASSERT_TRUE(CCP_PARSING_VALID == parsing_status);
    TEST_ASSERT_EQUAL_STRING("", test_request.body);
}

void ccp_test_parse_request_with_too_long_body()
{
    char raw_request[] = "CA|100|Hello World|";

    request test_request;
    CCP_PARSING_STATUS parsing_status = ccp_parse_request(raw_request, &test_request);

    TEST_ASSERT_TRUE(CCP_PARSING_INVALID_WRONG_FORMAT == parsing_status);
    TEST_ASSERT_TRUE(CCP_AT_CA == test_request.action_type);
    TEST_ASSERT_EQUAL_STRING("", test_request.body);
}

void ccp_test_parse_request_without_body()
{
    char raw_request[] = "CA|";

    request test_request;
    CCP_PARSING_STATUS parsing_status = ccp_parse_request(raw_request, &test_request);

    TEST_ASSERT_TRUE(CCP_PARSING_INVALID_WRONG_FORMAT == parsing_status);
    TEST_ASSERT_EQUAL_STRING("", test_request.body);
}

void ccp_test_parse_request_with_action_type()
{
    char raw_request[] = "CA|11|Hello World|";

    request test_request;
    CCP_PARSING_STATUS parsing_status = ccp_parse_request(raw_request, &test_request);

    TEST_ASSERT_TRUE(CCP_PARSING_VALID == parsing_status);
    TEST_ASSERT_TRUE(CCP_AT_CA == test_request.action_type);
}

void ccp_test_parse_request_with_body()
{
    char raw_request[] = "CA|11|Hello World|";

    request test_request;
    CCP_PARSING_STATUS parsing_status = ccp_parse_request(raw_request, &test_request);

    TEST_ASSERT_TRUE(CCP_PARSING_VALID == parsing_status);
    TEST_ASSERT_EQUAL_STRING("Hello World", test_request.body);
}

void ccp_test_at_from_str()
{
    CCP_ACTION_TYPE at = ccp_at_from_str("TM|........");
    TEST_ASSERT_TRUE(at == CCP_AT_TM);
}

void ccp_test_at_from_str2()
{
    CCP_ACTION_TYPE at = ccp_at_from_str("MS");
    TEST_ASSERT_TRUE(at == CCP_AT_MS);
}

void ccp_test_at_from_str3()
{
    CCP_ACTION_TYPE at = ccp_at_from_str("CA");
    TEST_ASSERT_TRUE(at == CCP_AT_CA);
}

int main(void)
{
    UNITY_BEGIN();
    // TEST CREATE REQUEST
    RUN_TEST(ccp_test_create_request_without_body);
    RUN_TEST(ccp_test_create_request_with_body);

    // TEST CREATE RESPONSE
    RUN_TEST(ccp_test_create_response_without_body);
    RUN_TEST(ccp_test_create_response_with_body);

    // TEST PARSE RESPONSE
    RUN_TEST(ccp_test_parse_response_with_action_type);
    RUN_TEST(ccp_test_parse_response_with_body);
    RUN_TEST(ccp_test_parse_response_with_empty_body);
    RUN_TEST(ccp_test_parse_response_with_status_code);
    RUN_TEST(ccp_test_parse_response_with_too_long_body);
    RUN_TEST(ccp_test_parse_response_with_unknown_action_type);
    RUN_TEST(ccp_test_parse_response_with_unknown_status_code);
    RUN_TEST(ccp_test_parse_response_without_body);

    // TEST PARSE REQUEST
    RUN_TEST(ccp_test_parse_request_with_action_type);
    RUN_TEST(ccp_test_parse_request_with_body);
    RUN_TEST(ccp_test_parse_request_with_empty_body);
    RUN_TEST(ccp_test_parse_request_with_too_long_body);
    RUN_TEST(ccp_test_parse_request_with_unknown_action_type);
    RUN_TEST(ccp_test_parse_request_without_body);

    // TEST ACTION TYPE CONVERTION
    RUN_TEST(ccp_test_at_from_str);
    RUN_TEST(ccp_test_at_from_str2);
    RUN_TEST(ccp_test_at_from_str3);

    return UNITY_END();
}

void setUp(void)
{
    FFF_RESET_HISTORY();
    RESET_FAKE(wifi_command_TCP_transmit);
}

void tearDown(void)
{
}
