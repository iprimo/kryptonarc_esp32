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
    unsigned char *encrypted = (unsigned char*)malloc(512);
    if (!encrypted) {
        mbedtls_pk_free(&pk);
        mbedtls_ctr_drbg_free(&ctr_drbg);
        mbedtls_entropy_free(&entropy);
        return -10;
    }
    size_t enc_len = 0;
    ret = mbedtls_base64_decode(encrypted, 512, &enc_len, (const unsigned char*)input, strlen(input));
    if (ret != 0) {
        free(encrypted);
        mbedtls_pk_free(&pk);
        mbedtls_ctr_drbg_free(&ctr_drbg);
        mbedtls_entropy_free(&entropy);
        return -2;
    }
    size_t olen = 0;
    ret = mbedtls_pk_decrypt(&pk, encrypted, enc_len, (unsigned char*)output, &olen, output_len, mbedtls_ctr_drbg_random, &ctr_drbg);
    free(encrypted);
    mbedtls_pk_free(&pk);
    mbedtls_ctr_drbg_free(&ctr_drbg);
    mbedtls_entropy_free(&entropy);
    if (ret != 0) return -3;
    output[olen] = '\0';
    return 0;
}




        // //////////////////////////////////////////
        // // RSA Encryption of encKey, hashKey and timeStamp
          
        // char *plain = (char*)malloc(512);
        // if (!plain) {
        //   Serial.println("Failed to allocate memory for plain buffer!");
        // } else {
        //   plain[0] = '\0';
        //   strcat(plain, "encKey:");
        //   strcat(plain, e2prom_variables.encryptionKey_Internal);
        //   strcat(plain, "::hashKey:");
        //   strcat(plain, e2prom_variables.hashKey_Internal);
        //   strcat(plain, "::timeStamp:");
        //   strcat(plain, software_parameters_variables.incoming_data_time_stamp);
        //   strcat(plain, "::");

        //   Serial.print("Plain: ");
        //   Serial.println(plain);

        //   int plain_len = strlen(plain);
        //   Serial.print("plain_len: ");
        //   Serial.println(plain_len);
        // }

        // // RSA encryption
        // char *encrypted = (char*)malloc(1024);
        // if (!plain || !encrypted) {
        //     if (!plain) Serial.println("Failed to allocate memory for plain buffer!");
        //     if (!encrypted) Serial.println("Failed to allocate memory for encryption buffer!");
        // } else {
        //   encrypted[0] = '\0';
        //   int enc_result = encrypt_with_public_key(plain, encrypted, 1024);
        //   if (enc_result == 0) {
        //     Serial.print("Encrypted: ");
        //     Serial.println(encrypted);
        //     // // Decrypt for testing
        //     // char *decrypted = (char*)malloc(1024); // Increased buffer size to match encrypted
        //     // if (!decrypted) {
        //     //   Serial.println("Failed to allocate memory for decrypted buffer!");
        //     // } else {
        //     //   decrypted[0] = '\0';
        //     //   int dec_result = decrypt_with_private_key(encrypted, decrypted, 1024);
        //     //   if (dec_result == 0) {
        //     //     Serial.print("Decrypted: ");
        //     //     Serial.println(decrypted);
        //     //   } else {
        //     //     Serial.print("Decryption failed! Error code: ");
        //     //     Serial.println(dec_result);
        //     //   }
        //     //   free(decrypted);
        //     // }
        //   } else {
        //     Serial.print("Encryption failed! Error code: ");
        //     Serial.println(enc_result);
        //     Serial.print("Encrypted buffer (may be garbage): ");
        //     Serial.println(encrypted);
        //   }
        // }


        // Serial.print("sendStr56:555555 ");
        // Serial.println(sendStr56);

        // // Append the encrypted block to the full response
        // fullResponse += "publicKeyEnc:";
        // if (encrypted) fullResponse += encrypted;
        // fullResponse += "::";
        // // Copy the result to tx_DataCache
        // strncpy(tx_DataCache, fullResponse.c_str(), TRANSFER_ARRAY_SIZE - 1);
        // tx_DataCache[TRANSFER_ARRAY_SIZE - 1] = '\0';

        // if (plain) free(plain);
        // if (encrypted) free(encrypted);

        





