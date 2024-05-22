#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "unity.h"
#include "aes.h" // Include the AES library header file

// Function declarations
void cryptorator_init(uint8_t *givenkey);
uint8_t* cryptorator_encrypt(const uint8_t *message);
uint8_t* cryptorator_decrypt(const uint8_t *encrypted_data);
void cryptorator_generate_iv(uint8_t *iv);

// Set up and tear down functions
void setUp(void) {
    // This function will be called before each test case
}

void tearDown(void) {
    // This function will be called after each test case
}

// Test case for encryption and decryption
void test_encryption_decryption() {
    uint8_t key[16] = {0}; // Initialize key with zeros
    uint8_t message[] = "hello world";
    
    cryptorator_init(key);

    // Encrypt the message
    uint8_t *encrypted_data = cryptorator_encrypt(message);

    // Decrypt the encrypted data
    uint8_t *decrypted_data = cryptorator_decrypt(encrypted_data);

    // Check if decrypted message matches original message
    TEST_ASSERT_EQUAL_STRING("hello world", decrypted_data);

    // Free allocated memory
    free(encrypted_data);
    free(decrypted_data);
}

// Test case for decryption
void test_decryption_withIV() {
    uint8_t key[16] = {0}; // Initialize key with zeros
    uint8_t message[] = "hello world";
    cryptorator_init(key);

    // Encrypt the message
    uint8_t *encrypted_data = cryptorator_encrypt(message);

    // Create IV and encrypted message combined
    uint8_t combined_data[strlen((char*)message) + AES_BLOCKLEN];
    memcpy(combined_data, encrypted_data, AES_BLOCKLEN); // Copy IV
    memcpy(combined_data + AES_BLOCKLEN, encrypted_data + AES_BLOCKLEN, strlen((char*)message)); // Copy encrypted message

    // Decrypt the combined data
    uint8_t *decrypted_data = cryptorator_decrypt(combined_data);

    // Check if decrypted message matches original message
    TEST_ASSERT_EQUAL_STRING("hello world", decrypted_data);

    // Free allocated memory
    free(encrypted_data);
    free(decrypted_data);
}

// Entry point for the test suite
int main() {
    UNITY_BEGIN();
    // Run the encryption and decryption test
    RUN_TEST(test_encryption_decryption);
    RUN_TEST(test_decryption_withIV);
    return UNITY_END();
}
