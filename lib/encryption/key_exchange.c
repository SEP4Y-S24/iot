#include <stdint.h>
#include "uECC.h"
#include "logger.h"
#include <stdio.h>
static uint8_t private_key[33];
static uint8_t public_key[65];
static uECC_Curve curve;

static void hash_secret(uint8_t *hash, uint8_t *secret);
void key_echange_init()
{
    curve = uECC_secp256r1();
}
// TODO implement a better random number generator
int simple_rng(uint8_t *dest, unsigned size)
{
    static uint8_t value = 0;
    // Static variable to keep track of the current value
    // Increment the value for each call (otherwise the two private keys will be the same)
    value++; // Fill 'dest' with the current value
    for (unsigned i = 0; i < size; ++i)
    {
        dest[i] = value + i + 7; // 7 is my random number. To be more random, you could read a value from a analog input, using the ADC.
    }
    return 1; // Indicate success
}

void key_exchange_generete_keys()
{
    uECC_Curve curve = uECC_secp256r1();
    uECC_set_rng(&simple_rng);
    uECC_make_key(public_key, private_key, curve);
}

void key_exchange_get_public_key(uint8_t *copy_public_key)
{
    for (int i = 0; i < 64; i++)
    {
        copy_public_key[i] = public_key[i];
    }
    copy_public_key[64] = '\0';
}

void key_exchange_generate_shared_secret(uint8_t *received_public_key, uint8_t *secret)
{
    uECC_Curve curve = uECC_secp256r1();
    uint8_t generated_secret[33];
    uECC_shared_secret(received_public_key, private_key, generated_secret, curve);
    uint8_t hash[17];
    // hash_secret(hash, generated_secret); // hash the generated secret and truncuate it
    log_debug("private key: ");
    log_debug((char *)private_key);
    for (int i = 0; i < 16; i++)
    {
        secret[i] = generated_secret[i];
    }
    secret[16] = '\0';
    log_debug("Shared secret: ");
    log_debug((char *)generated_secret);
}

static void hash_secret(uint8_t *hash, uint8_t *secret)
{
    for (int i = 0; i < 16; i++)
    {
        hash[i] = secret[i];
    } // TODO: Implement a hash function
    hash[16] = '\0';
}