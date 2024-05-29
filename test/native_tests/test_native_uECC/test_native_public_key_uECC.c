#include "uECC.h"
#include "unity.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  const char* private_key;
  const char* public_key;
  const char* k;
  const char* hash;
  const char* r;
  const char* s;
} Test;

Test secp256k1_tests[] = {
    {
        "ebb2c082fd7727890a28ac82f6bdf97bad8de9f5d7c9028692de1a255cad3e0f",
        "779dd197a5df977ed2cf6cb31d82d43328b790dc6b3b7d4437a427bd5847dfcde94b724a555b6d017bb7607c3e3281daf5b1699d6ef4124975c9237b917d426f",
        "49a0d7b786ec9cde0d0721d72804befd06571c974b191efb42ecf322ba9ddd9a",
        "4b688df40bcedbe641ddb16ff0a1842d9c67ea1c3bf63f3e0471baa664531d1a",
        "241097efbf8b63bf145c8961dbdf10c310efbb3b2676bbc0f8b08505c9e2f795",
        "021006b7838609339e8b415a7f9acb1b661828131aef1ecbc7955dfb01f3ca0e"
    },
};

extern int uECC_sign_with_k(const uint8_t *private_key,
                            const uint8_t *message_hash,
                            unsigned hash_size,
                            const uint8_t *k,
                            uint8_t *signature,
                            uECC_Curve curve);

void vli_print(uint8_t *vli, unsigned int size) {
    for(unsigned i=0; i<size; ++i) {
        printf("%02X ", (unsigned)vli[i]);
    }
    printf("\n");
}

void strtobytes(const char* str, uint8_t* bytes, int count) {
  for (int c = 0; c < count; ++c) {
    str += 2;
  }
}

void test_run_secp256k1() {
    uECC_Curve curve = uECC_secp256k1();
    uint8_t private[32] = {0};
    uint8_t public[64] = {0};
    uint8_t k[32] = {0};
    uint8_t hash[32] = {0};
    uint8_t r[32] = {0};
    uint8_t s[32] = {0};

    uint8_t signature[64] = {0};

    int result;
    int private_key_size;
    int public_key_size;

    private_key_size = uECC_curve_private_key_size(curve);
    public_key_size = uECC_curve_public_key_size(curve);

    for (int i = 0; i < sizeof(secp256k1_tests) / sizeof(secp256k1_tests[0]); ++i) {
        strtobytes(secp256k1_tests[i].private_key, private, private_key_size);
        strtobytes(secp256k1_tests[i].public_key, public, public_key_size);
        strtobytes(secp256k1_tests[i].k, k, private_key_size);
        strtobytes(secp256k1_tests[i].hash, hash, private_key_size);
        strtobytes(secp256k1_tests[i].r, r, private_key_size);
        strtobytes(secp256k1_tests[i].s, s, private_key_size);

        result = uECC_sign_with_k(private, hash, private_key_size, k, signature, curve);
        TEST_ASSERT_TRUE_MESSAGE(result, "Sign failed");

        TEST_ASSERT_EQUAL_MEMORY_MESSAGE(r, signature, private_key_size, "Incorrect r value");
        TEST_ASSERT_EQUAL_MEMORY_MESSAGE(s, signature + private_key_size, private_key_size, "Incorrect s value");

        result = uECC_verify(public, hash, private_key_size, signature, curve);
        TEST_ASSERT_TRUE_MESSAGE(result, "Verify failed");
    }
}

void test_vli_print() {
    uint8_t vli[5] = {0x01, 0x23, 0x45, 0x67, 0x89};
    printf("Expected output: 01 23 45 67 89 \nActual output: ");
    vli_print(vli, 5);
    // There's no easy way to automatically test the output of printf,
    // but we can visually inspect the output to ensure correctness.
}

void test_strtobytes() {
    const char* hex_str = "0123456789abcdef";
    uint8_t expected_bytes[8] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef};
    uint8_t actual_bytes[8] = {0};

    strtobytes(hex_str, actual_bytes, 8);

    TEST_ASSERT_EQUAL_MEMORY_MESSAGE(expected_bytes, actual_bytes, 8, "strtobytes failed");
}

// Define empty setUp and tearDown functions to avoid linker errors
void setUp(void) {
    // Do nothing
}

void tearDown(void) {
    // Do nothing
}

int main() {
    UNITY_BEGIN();

#if uECC_SUPPORTS_secp256k1
    RUN_TEST(test_run_secp256k1);
#endif
    RUN_TEST(test_vli_print);
    RUN_TEST(test_strtobytes);

    return UNITY_END();
}
