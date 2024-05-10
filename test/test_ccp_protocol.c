#ifdef TEST_CCP_PROTOCOL

#include <unity.h>
#include <ccp_protocol.h>
#include <stdio.h>
#include <fff.h>
#include <wifi.h>

FAKE_VALUE_FUNC(WIFI_ERROR_MESSAGE_t, wifi_command_TCP_transmit, uint8_t *, uint16_t);

void ccp_test_create_request_without_body()
{
    char buffer[100];
    ccp_create_request(CCP_AT_TM, "", buffer);
    TEST_ASSERT_EQUAL_STRING("TM\r\n0\r\n\r\n", buffer);
}

void ccp_test_create_request_with_body()
{
    char buffer[100];
    ccp_create_request(CCP_AT_MS, "Hello, World!", buffer);
    TEST_ASSERT_EQUAL_STRING("MS\r\n13\r\nHello, World!\r\n", buffer);
}

void ccp_test_create_response_without_body()
{
    char buffer[100];
    ccp_create_response(buffer, CCP_AT_TM, CCP_STATUS_OK, "");
    TEST_ASSERT_EQUAL_STRING("TM\r\n1\r\n0\r\n\r\n", buffer);
}

void ccp_test_create_response_with_body()
{
    char buffer[100];
    ccp_create_response(buffer, CCP_AT_MS, CCP_STATUS_SERVER_ERROR, "Internal Server Error");
    TEST_ASSERT_EQUAL_STRING("MS\r\n2\r\n21\r\nInternal Server Error\r\n", buffer);
}

void ccp_test_parse_response_with_unknown_action_type()
{
    char raw_response[] = "TR\r\n1\r\n10\r\nHello World\r\n";

    response test_response = ccp_parse_response(raw_response);

    TEST_ASSERT_TRUE(CCP_AT_UNKNOWN == test_response.action_type);
}

void ccp_test_parse_response_with_unknown_status_code()
{
    char raw_response[] = "MS\r\n9\r\n10\r\nHello World\r\n";

    response test_response = ccp_parse_response(raw_response);

    TEST_ASSERT_TRUE(CCP_STATUS_NUM_STATUS_CODES == test_response.status_code);
}

void ccp_test_parse_response_with_empty_body()
{
    char raw_response[] = "MS\r\n1\r\n0\r\n";

    response test_response = ccp_parse_response(raw_response);

    TEST_ASSERT_EQUAL_STRING("", test_response.body);
}

void ccp_test_parse_response_with_too_long_body()
{
    char raw_response[] = "MS\r\n1\r\n100\r\nBody length is set to bee too long.\r\n";

    response test_response = ccp_parse_response(raw_response);

    TEST_ASSERT_TRUE(CCP_AT_UNKNOWN == test_response.action_type);
    TEST_ASSERT_TRUE(CCP_STATUS_BAD_REQUEST == test_response.status_code);
    TEST_ASSERT_EQUAL_STRING("", test_response.body);
}

void ccp_test_parse_response_without_body()
{
    char raw_response[] = "MS\r\n1\r\n";

    response test_response = ccp_parse_response(raw_response);

    TEST_ASSERT_EQUAL_STRING("", test_response.body);
}

void ccp_test_parse_response_with_action_type()
{
    char raw_response[] = "MS\r\n1\r\n10\r\nHello World\r\n";

    response test_response = ccp_parse_response(raw_response);

    TEST_ASSERT_TRUE(CCP_AT_MS == test_response.action_type);
}

void ccp_test_parse_response_with_status_code()
{
    char raw_response[] = "MS\r\n1\r\n10\r\nHello World\r\n";

    response test_response = ccp_parse_response(raw_response);

    TEST_ASSERT_TRUE(CCP_STATUS_OK == test_response.status_code);
}

void ccp_test_parse_response_with_body()
{
    char raw_response[] = "MS\r\n1\r\n11\r\nHello World\r\n";

    response test_response = ccp_parse_response(raw_response);

    TEST_ASSERT_EQUAL_STRING("Hello World", test_response.body);
}

void ccp_test_at_from_str()
{
    CCP_ACTION_TYPE at = ccp_at_from_str("TM\r\n........");
    TEST_ASSERT_TRUE(at == CCP_AT_TM);
}

void ccp_test_at_from_str2()
{
    CCP_ACTION_TYPE at = ccp_at_from_str("MS");
    TEST_ASSERT_TRUE(at == CCP_AT_MS);
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

    // TEST ACTION TYPE CONVERTION
    RUN_TEST(ccp_test_at_from_str);
    RUN_TEST(ccp_test_at_from_str2);
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

#endif // TEST_CCP_PROTOCOL