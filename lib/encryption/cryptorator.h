
#include <stdint.h>

void cryptorator_init(uint8_t *key);
uint8_t* cryptorator_encrypt(const uint8_t *message);
uint8_t* cryptorator_decrypt(const uint8_t *message);
void cryptorator_generate_iv(uint8_t *iv);
