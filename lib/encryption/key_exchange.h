#pragma once
#include <stdint.h>

/*
 * @brief Initializes the key exchange module
 */
void key_echange_init();

/*
 * @brief Generates the public and private keys
 */
void key_exchange_generate_keys();

/*
@brief Gets the public key
*/
void key_exchange_get_public_key(uint8_t *public_key);

/*
 * @brief Generates a shared secret
 */
void key_exchange_generate_shared_secret(uint8_t *public_key, uint8_t *secret);