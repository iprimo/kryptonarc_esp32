#ifndef CRYPTO_UTILS_H
#define CRYPTO_UTILS_H

#include <stddef.h>

// Example 2048-bit RSA public and private keys (PEM format, truncated for brevity)
#define PUBLIC_KEY "-----BEGIN PUBLIC KEY-----\nMIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAwVl+32cbc17TVxqe8QSA\n52yUHyVuX88HzRhdxgBs63pmX8CbcE83UdMjqeZY0PF5KtBq4s6h18H9XmyAEOGY\nNFava2S7UwOaIIHV2r4SUdx2STU+P+8ruwQX8tBWBRqv/AcJhUCKdbTjeh/997EX\ncqsaTB7YJtQItH7ztpGjLLtTO/36wNcADqUHACqmJ+UsSB2M7x+GBhvjiWrQrxBl\no7ILLJfzZuNR/heCt0nBL+ys/Ecs61VLP0Z/YZVQKDmpXX92jxV+pEH8/pBh7PA8\nwBOhvYyqrR0CSeHFbRIHSJ7PnXz60xKWH7FfVaRvBiWba0aG/Vo4nNbP4Tc3vA1w\nLwIDAQAB\n-----END PUBLIC KEY-----"
#define PRIVATE_KEY "-----BEGIN PRIVATE KEY-----\n...replace_with_actual_key...\n-----END PRIVATE KEY-----"

#ifdef __cplusplus
extern "C" {
#endif

// Encrypts input string with public key, outputs encrypted data (base64 encoded)
int encrypt_with_public_key(const char *input, char *output, size_t output_len);

// Decrypts input (base64 encoded) with private key, outputs decrypted string
int decrypt_with_private_key(const char *input, char *output, size_t output_len);

#ifdef __cplusplus
}
#endif

#endif // CRYPTO_UTILS_H
