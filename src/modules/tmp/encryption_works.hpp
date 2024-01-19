// Helpful example
// https://www.dfrobot.com/blog-1001.html
// Original source - Example of Arduino IDE AES128_Example

#include "string.h"
#include "mbedtls/aes.h"

// Note, we had issues with Data Padding
// C & javascript work independently, but data padding issue presist

// ////////////////////////////////////////////////////////////////////////


//   // String toEncode = "Test encoding";
//   String toEncode = "Test encoding_Test encoding__Test encoding___Test encoding____Test encoding____Test encoding______Test encoding";
//   Serial.println("toEncode >>> ");
//   Serial.println(toEncode);
//   String encoded = base64::encode( toEncode.c_str());
//   Serial.println("encoded >>> ");
//   Serial.println(encoded);

//   char uuu[1024];
//   base64_string_decoding( encoded , uuu );
//   Serial.println("uuu >>> ");
//   Serial.println(uuu);

  
  
  
//   char * key = "abcdefghijklmnop";

//   // char *plainText = "Tech tutorials x";
//   char *plainText = "1234567890123456";
//   unsigned char cipherTextOutput[16];
//   unsigned char decipheredTextOutput[16];

//   encrypt(plainText, key, cipherTextOutput);
//   decrypt(cipherTextOutput, key, decipheredTextOutput);

//   Serial.println("\nOriginal plain text:");
//   Serial.println(plainText);




//   Serial.println("\nCiphered text:");

//   char encrypted_data[sizeof(cipherTextOutput) * 2 + 1];  // Allocate space for digits and null terminator
//   int resultIndex = 0;

//   for (int i = 0; i < 16; i++) {

//     char str[3];

//     sprintf(str, "%02x", (int)cipherTextOutput[i]);
//     Serial.print(str);

//     // Append str to the encrypted_data
//     strncpy(encrypted_data + resultIndex, str, 2);  // Copy 2 characters from str
//     resultIndex += 2;  // Move the index for the next append
//   }
// // Add null terminator to mark the end of the string
//   encrypted_data[resultIndex] = '\0';
//   Serial.println("");
//   Serial.println("  >>>encrypted_data  >>>:  ");
//   Serial.println(encrypted_data);
//   Serial.println("");


//   char decrypted_data[17];  // Allocate space for digits and null terminator
//   Serial.println("\n\nDeciphered text:");
//   for (int i = 0; i < 16; i++) {
//     Serial.print((char)decipheredTextOutput[i]);
//     decrypted_data[i] = (char)decipheredTextOutput[i] ;
//   }
//   decrypted_data[ 16 ] = '\0';
//   Serial.println("");
//   Serial.println("  >>>decrypted_data  >>>:  ");
//   Serial.println(decrypted_data);
//   Serial.println("");

// // Use case example
// ////////////////////////////////////////////////////////////////////////
// Some Javascript example 


                // const key = "2b7e151628aed2a6abf79798096b56d7";

                // // char *plainText = "Tech tutorials x";
                // const plainText = "1234567890123456";



                // function pkcs7Padding(text) {
                //     const blockSize = 16; // AES block size
                //     const paddingLength = blockSize - (text.length % blockSize);
                //     const padding = new Array(paddingLength + 1).join(String.fromCharCode(paddingLength));
                //     return text + padding;
                //   }
                  
                //   function pkcs7Unpadding(text) {
                //     const paddingLength = text.charCodeAt(text.length - 1);
                //     return text.slice(0, -paddingLength);
                //   }

                // function encrypt(plainText, key) {
                //     const paddedPlainText = pkcs7Padding(plainText);
                //     const cipherParams = CryptoJS.AES.encrypt(paddedPlainText, key, { mode: CryptoJS.mode.ECB });
                //     const ciphertext = cipherParams.toString();
                //     return ciphertext;
                //   }
                  
                //   function decrypt(ciphertext, key) {
                //     const cipherParams = CryptoJS.AES.decrypt(ciphertext, key, { mode: CryptoJS.mode.ECB });
                //     const decryptedBytes = cipherParams.toString(CryptoJS.enc.Utf8);
                //     const plainText = pkcs7Unpadding(decryptedBytes);
                //     return plainText;
                //   }

                // const  kkkk = encrypt(plainText, key)
                //   console.log("encrypt(plainText, key) >>>>    ",kkkk)
                //   console.log("decrypt(ciphertext, key) >>>>    ",decrypt(kkkk, key))






#ifndef AES_ENCRYPTION_HPP
#define AES_ENCRYPTION_HPP
// void encrypt(char * plainText, char * key, unsigned char * outputBuffer){

//   mbedtls_aes_context aes;

//   mbedtls_aes_init( &aes );
//   mbedtls_aes_setkey_enc( &aes, (const unsigned char*) key, strlen(key) * 8 );
//   mbedtls_aes_crypt_ecb( &aes, MBEDTLS_AES_ENCRYPT, (const unsigned char*)plainText, outputBuffer);
//   mbedtls_aes_free( &aes );
// }

void encrypt(char *plainText, char *key, unsigned char *outputBuffer) {
    size_t textLength = strlen(plainText);
    mbedtls_aes_context aes;

    mbedtls_aes_init(&aes);
    mbedtls_aes_setkey_enc(&aes, (const unsigned char*)key, strlen(key) * 8);

    // Ensure textLength is a multiple of block size (16 bytes)
    size_t paddedLength = ((textLength / 16) + 1) * 16;

    // Pad plaintext if necessary
    unsigned char paddedPlainText[paddedLength];
    memcpy(paddedPlainText, plainText, textLength);
    memset(paddedPlainText + textLength, paddedLength - textLength, paddedLength - textLength);

    // Encrypt padded plaintext
    mbedtls_aes_crypt_ecb(&aes, MBEDTLS_AES_ENCRYPT, paddedPlainText, outputBuffer);

    mbedtls_aes_free(&aes);
}



#endif


#ifndef AES_DECRYPTION_HPP
#define AES_DECRYPTION_HPP

void decrypt(unsigned char * chipherText, char * key, unsigned char * outputBuffer){

  mbedtls_aes_context aes;

  mbedtls_aes_init( &aes );
  mbedtls_aes_setkey_dec( &aes, (const unsigned char*) key, strlen(key) * 8 );
  mbedtls_aes_crypt_ecb(&aes, MBEDTLS_AES_DECRYPT, (const unsigned char*)chipherText, outputBuffer);
  mbedtls_aes_free( &aes );
}
#endif



