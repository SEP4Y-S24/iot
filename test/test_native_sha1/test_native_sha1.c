#include "unity.h"
#include "sha1.h"
#include <string.h>

void setUp(void)
{
    // This function will be called before each test case
}

void tearDown(void)
{
    // This function will be called after each test case
}


void test_sha1_known_input(void) {
    // Test vector from FIPS PUB 180-1
    const char *test_input = "abc";
    uint8_t expected_output[SHA1HashSize] = {
        0xa9, 0x99, 0x3e, 0x36, 0x47, 0x06, 0x81, 0x6a,
        0xba, 0x3e, 0x25, 0x71, 0x78, 0x50, 0xc2, 0x6c,
        0x9c, 0xd0, 0xd8, 0x9d
    };

    SHA1Context sha;
    uint8_t message_digest[SHA1HashSize];

    TEST_ASSERT_EQUAL(shaSuccess, SHA1Reset(&sha));
    TEST_ASSERT_EQUAL(shaSuccess, SHA1Input(&sha, (const uint8_t *)test_input, strlen(test_input)));
    TEST_ASSERT_EQUAL(shaSuccess, SHA1Result(&sha, message_digest));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_output, message_digest, SHA1HashSize);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_sha1_known_input);
    return UNITY_END();
}
