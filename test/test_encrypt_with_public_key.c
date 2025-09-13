#include "crypto_utils.h"
#include <stdio.h>

int main() {
    char encrypted[512];
    const char *test_input = "Hello, ESP32!";
    int result = encrypt_with_public_key(test_input, encrypted, sizeof(encrypted));
    printf("encrypt_with_public_key returned: %d\n", result);
    if (result == 0) {
        printf("Encrypted (base64): %s\n", encrypted);
    } else {
        printf("Encryption failed!\n");
    }
    return 0;
}
