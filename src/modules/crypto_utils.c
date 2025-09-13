#include "crypto_utils.h"
#include <string.h>
#include <mbedtls/pk.h>
#include <mbedtls/base64.h>
#include <mbedtls/ctr_drbg.h>
#include <mbedtls/entropy.h>

// Helper: initialize mbedtls context
static void mbedtls_init(mbedtls_pk_context *pk, mbedtls_ctr_drbg_context *ctr_drbg, mbedtls_entropy_context *entropy) {
    mbedtls_pk_init(pk);
    mbedtls_ctr_drbg_init(ctr_drbg);
    mbedtls_entropy_init(entropy);
    mbedtls_ctr_drbg_seed(ctr_drbg, mbedtls_entropy_func, entropy, NULL, 0);
}

int encrypt_with_public_key(const char *input, char *output, size_t output_len) {
    if (!input || !output || output_len < 350) {
        if (output && output_len > 0) output[0] = '\0';
        return -10; // invalid args or buffer too small
    }
    mbedtls_pk_context pk;
    mbedtls_ctr_drbg_context ctr_drbg;
    mbedtls_entropy_context entropy;
    mbedtls_init(&pk, &ctr_drbg, &entropy);
    int ret = mbedtls_pk_parse_public_key(&pk, (const unsigned char*)PUBLIC_KEY, strlen(PUBLIC_KEY)+1);
    if (ret != 0) {
        mbedtls_pk_free(&pk);
        mbedtls_ctr_drbg_free(&ctr_drbg);
        mbedtls_entropy_free(&entropy);
        if (output && output_len > 0) output[0] = '\0';
        return -1;
    }
    unsigned char *encrypted = (unsigned char*)malloc(256);
    if (!encrypted) {
        mbedtls_pk_free(&pk);
        mbedtls_ctr_drbg_free(&ctr_drbg);
        mbedtls_entropy_free(&entropy);
        if (output && output_len > 0) output[0] = '\0';
        return -11; // malloc failed
    }
    size_t olen = 0;
    ret = mbedtls_pk_encrypt(&pk, (const unsigned char*)input, strlen(input), encrypted, &olen, 256, mbedtls_ctr_drbg_random, &ctr_drbg);
    if (ret != 0) {
        free(encrypted);
        mbedtls_pk_free(&pk);
        mbedtls_ctr_drbg_free(&ctr_drbg);
        mbedtls_entropy_free(&entropy);
        if (output && output_len > 0) output[0] = '\0';
        return -2;
    }
    size_t b64len = 0;
    ret = mbedtls_base64_encode((unsigned char*)output, output_len, &b64len, encrypted, olen);
    free(encrypted);
    mbedtls_pk_free(&pk);
    mbedtls_ctr_drbg_free(&ctr_drbg);
    mbedtls_entropy_free(&entropy);
    if (ret != 0) {
        if (output && output_len > 0) output[0] = '\0';
        return -3;
    }
    if (b64len < output_len) {
        output[b64len] = '\0';
    } else if (output_len > 0) {
        output[output_len-1] = '\0';
    }
    return 0;
}

int decrypt_with_private_key(const char *input, char *output, size_t output_len) {
    mbedtls_pk_context pk;
    mbedtls_ctr_drbg_context ctr_drbg;
    mbedtls_entropy_context entropy;
    mbedtls_init(&pk, &ctr_drbg, &entropy);
    int ret = mbedtls_pk_parse_key(&pk, (const unsigned char*)PRIVATE_KEY, strlen(PRIVATE_KEY)+1, NULL, 0);
    if (ret != 0) return -1;
    unsigned char encrypted[256];
    size_t enc_len = 0;
    ret = mbedtls_base64_decode(encrypted, sizeof(encrypted), &enc_len, (const unsigned char*)input, strlen(input));
    if (ret != 0) return -2;
    size_t olen = 0;
    ret = mbedtls_pk_decrypt(&pk, encrypted, enc_len, (unsigned char*)output, &olen, output_len, mbedtls_ctr_drbg_random, &ctr_drbg);
    mbedtls_pk_free(&pk);
    mbedtls_ctr_drbg_free(&ctr_drbg);
    mbedtls_entropy_free(&entropy);
    if (ret != 0) return -3;
    output[olen] = '\0';
    return 0;
}
