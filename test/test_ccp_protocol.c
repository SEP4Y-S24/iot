#ifdef TEST_CCP_PROTOCOL

#include <unity.h>
#include <ccp_protocol.h>
#include <stdio.h>

void ccp_test_build_request_without_body()
{
    char buffer[100];
    ccp_create_request("TM", "", buffer);
    TEST_ASSERT_EQUAL_STRING("TM\r\n0\r\n\r\n", buffer);
}

void ccp_test_build_request_with_body()
{
    char buffer[100];
    ccp_create_request("MS", "Hello, World!", buffer);
    TEST_ASSERT_EQUAL_STRING("MS\r\n13\r\nHello, World!\r\n", buffer);
}

void ccp_test_build_response_without_body()
{
    char buffer[100];
    ccp_create_response(buffer, CCP_AT_TM, CCP_STATUS_OK, "");
    TEST_ASSERT_EQUAL_STRING("TM\r\n1\r\n0\r\n\r\n", buffer);
}

void ccp_test_build_response_with_body()
{
    char buffer[100];
    ccp_create_response(buffer, CCP_AT_MS, CCP_STATUS_SERVER_ERROR, "Internal Server Error");
    TEST_ASSERT_EQUAL_STRING("MS\r\n2\r\n21\r\nInternal Server Error\r\n", buffer);
}

void cpp_test_build_request()
{
}

void cpp_test_build_response()
{
    char response[] = "MS\r\n1\r\n10\r\nHello\nWorld\r\n";
    char status_buffer[10];
    int status_buffer_size = sizeof(status_buffer);

    char *data = ccp_parse_response(response, status_buffer, status_buffer_size);

    if (data == NULL)
    {
        printf("Error\n");
    }
    else
    {
        printf("Status code: %s\n", status_buffer);
        printf("Body: %s\n", data);
    }
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
    RUN_TEST(ccp_test_build_request_without_body);
    RUN_TEST(ccp_test_build_request_with_body);
    RUN_TEST(ccp_test_build_response_without_body);
    RUN_TEST(ccp_test_build_response_with_body);
    RUN_TEST(cpp_test_build_request);
    RUN_TEST(cpp_test_build_response);
    RUN_TEST(ccp_test_at_from_str);
    RUN_TEST(ccp_test_at_from_str2);
    return UNITY_END();
}

void setUp(void)
{
}

void tearDown(void)
{
}

#endif // TEST_CCP_PROTOCOL