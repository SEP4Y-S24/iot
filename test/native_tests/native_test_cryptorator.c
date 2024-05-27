#ifdef NATIVE_TEST_CRYPTORATOR

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "unity.h"
#include "cryptorator.h"
#ifdef TEST_CRYPTORATOR
// Set up and tear down functions
void setUp(void)
{
    // This function will be called before each test case
}

void tearDown(void)
{
    // This function will be called after each test case
}

// Test case for encryption and decryption
void test_encryption_decryption()
{
    uint8_t key[16] = {0}; // Initialize key with zeros
    char message[] = "hello world";

    cryptorator_init(key);

    // Make a copy of the message for encryption
    char *encrypted_message = strdup(message);
    if (encrypted_message == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }

    // Encrypt the message
    cryptorator_encrypt(&encrypted_message);

    // Decrypt the message
    cryptorator_decrypt(encrypted_message);

    // Check if decrypted message matches original message
    TEST_ASSERT_EQUAL_STRING("hello world", encrypted_message);

    // Free allocated memory
    free(encrypted_message);
}

// Test case for decryption
void test_decryption_withIV()
{
    uint8_t key[16] = {0}; // Initialize key with zeros
    char message[] = "hello world";
    cryptorator_init(key);

    // Make a copy of the message for encryption
    char *encrypted_message = strdup(message);
    if (encrypted_message == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }

    // Encrypt the message
    cryptorator_encrypt(&encrypted_message);

    // Decrypt the message
    cryptorator_decrypt(encrypted_message);

    // Check if decrypted message matches original message
    TEST_ASSERT_EQUAL_STRING("hello world", encrypted_message);

    // Free allocated memory
    free(encrypted_message);
}

// Entry point for the test suite
int main()
{
    UNITY_BEGIN();
    // Run the encryption and decryption test
    RUN_TEST(test_encryption_decryption);
    RUN_TEST(test_decryption_withIV);
    return UNITY_END();
}

#endif