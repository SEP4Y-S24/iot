#include "unity.h"
#include "working_state.h"
#include "../fff.h"
#include <stdbool.h>

// Define fakes for the dependencies
DEFINE_FFF_GLOBALS;

FAKE_VOID_FUNC(wifi_reassign_callback, void (*)(void), char *);
FAKE_VOID_FUNC(ccp_message_handler_handle, const char *);
FAKE_VOID_FUNC(ccp_message_sender_send_request, const char *, const char *);
FAKE_VOID_FUNC(native_delay_ms, unsigned int);
FAKE_VOID_FUNC(periodic_request_10_minutes_init);
FAKE_VOID_FUNC(periodic_request_10_minutes_stop);
FAKE_VOID_FUNC(state_coordinator_wait_for_event, bool *);

// Mock callback function
void mock_tcp_callback() {
    ccp_message_handler_handle(message_buffer);
}

void setUp(void) {
    // Reset all fakes before each test
    RESET_FAKE(wifi_reassign_callback);
    RESET_FAKE(ccp_message_handler_handle);
    RESET_FAKE(ccp_message_sender_send_request);
    RESET_FAKE(native_delay_ms);
    RESET_FAKE(periodic_request_10_minutes_init);
    RESET_FAKE(periodic_request_10_minutes_stop);
    RESET_FAKE(log_info);
    RESET_FAKE(state_coordinator_wait_for_event);

    // Set the mock callback function
    wifi_reassign_callback_fake.custom_fake = mock_tcp_callback;
}

void tearDown(void) {
    // Cleanup code if needed
}

void test_working_state_switch(void) {
    // Call the function to test
    State result = working_state_switch();

    // Verify the function calls
    TEST_ASSERT_EQUAL(1, wifi_reassign_callback_fake.call_count);
    TEST_ASSERT_EQUAL(1, log_info_fake.call_count);
    TEST_ASSERT_EQUAL_STRING("Entered working state", log_info_fake.arg0_val);
    TEST_ASSERT_EQUAL(1, ccp_message_sender_send_request_fake.call_count);
    TEST_ASSERT_EQUAL_STRING(CCP_AT_TM, ccp_message_sender_send_request_fake.arg0_val);
    TEST_ASSERT_EQUAL_STRING("", ccp_message_sender_send_request_fake.arg1_val);
    TEST_ASSERT_EQUAL(1, native_delay_ms_fake.call_count);
    TEST_ASSERT_EQUAL(2000, native_delay_ms_fake.arg0_val);
    TEST_ASSERT_EQUAL(1, periodic_request_10_minutes_init_fake.call_count);
    TEST_ASSERT_EQUAL(1, state_coordinator_wait_for_event_fake.call_count);
    TEST_ASSERT_EQUAL_PTR(&error, state_coordinator_wait_for_event_fake.arg0_val);
    TEST_ASSERT_EQUAL(1, periodic_request_10_minutes_stop_fake.call_count);

    // Verify the result (Note: the actual value does not matter as per the comment in the function)
    TEST_ASSERT_EQUAL(WORKING_STATE, result);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_working_state_switch);
    return UNITY_END();
}
