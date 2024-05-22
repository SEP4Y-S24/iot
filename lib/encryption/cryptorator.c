#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


#include "aes.h" // Include the AES library header file

#define AES_BLOCKLEN 16 // AES block length
static uint8_t key[16]; // Define a static key array of 16 bytes


// Function to initialize the cryptorator with a given key
void cryptorator_init(uint8_t *givenkey){
    for (int i = 0; i < 16; i++) {
        key[i] = givenkey[i]; 
    }
}

// Function to encrypt data using AES in CBC mode
uint8_t* cryptorator_encrypt(const uint8_t *message) {
    struct AES_ctx ctx; // Define a context for AES encryption
    uint8_t iv[AES_BLOCKLEN]; // Define an initialization vector (IV)
    cryptorator_generate_iv(iv); // Generate a random IV
    
    // Allocate memory for the encrypted data (message size + IV size)
    uint8_t *encrypted_data = (uint8_t *)malloc(AES_BLOCKLEN + strlen((char *)message) + 1);
    if (encrypted_data == NULL) {
        // Memory allocation failed
        return NULL;
    }
    
    // Copy the IV to the output buffer
    memcpy(encrypted_data, iv, AES_BLOCKLEN);
    // Initialize the AES context with the key and IV
    AES_init_ctx_iv(&ctx, key, iv);
    // Encrypt the data using AES in CBC mode
    AES_CBC_encrypt_buffer(&ctx, message, strlen((char *)message));
    // Copy the encrypted data to the output buffer after the IV
    memcpy(encrypted_data + AES_BLOCKLEN, message, strlen((char *)message) + 1);

    return encrypted_data;
}

// Function to decrypt data using AES in CBC mode
#define AES_BLOCKLEN 16 // AES block length

// Function to decrypt data using AES in CBC mode
uint8_t* cryptorator_decrypt(const uint8_t *encrypted_data) {
    struct AES_ctx ctx; // Define a context for AES decryption
    
    // Extract IV from the encrypted data
    uint8_t iv[AES_BLOCKLEN];
    memcpy(iv, encrypted_data, AES_BLOCKLEN);
    
    // Allocate memory for the decrypted data (encrypted_data size - IV size)
    uint8_t *decrypted_data = (uint8_t *)malloc(strlen((char *)encrypted_data) - AES_BLOCKLEN + 1);
    if (decrypted_data == NULL) {
        // Memory allocation failed
        return NULL;
    }
    
    // Initialize the AES context with the key and IV
    AES_init_ctx_iv(&ctx, key, iv);
    // Decrypt the data using AES in CBC mode
    AES_CBC_decrypt_buffer(&ctx, encrypted_data + AES_BLOCKLEN, strlen((char *)encrypted_data) - AES_BLOCKLEN);
    // Copy the decrypted data to the output buffer
    memcpy(decrypted_data, encrypted_data + AES_BLOCKLEN, strlen((char *)encrypted_data) - AES_BLOCKLEN + 1);
    
    return decrypted_data;
}


#define IV_SIZE 16 // Define the size of the initialization vector (IV)
// Function to generate a random IV
void cryptorator_generate_iv(uint8_t *iv) {
    // Generate random bytes for the IV
    for (int i = 0; i < IV_SIZE; i++) {
        iv[i] = rand() % 256; // Generate a random byte (0-255) and store it in the IV
    }
} 