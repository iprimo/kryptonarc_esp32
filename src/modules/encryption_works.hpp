#include "string.h"

String encryptV2(String input) {
  
  return input;
}

String decryptV2(String input) {
  
  return input;
}



//     // ////////////////////////////////////////////////////////////////////////////////  Testing Section   >>>
    
//     String plaintext = "Hello, world!";
    
//     // Encrypt the plaintext
//     String ciphertext = encryptV1(plaintext, key);
    
//     Serial.print("Plaintext: ");
//     Serial.println(plaintext);
    
//     Serial.print("Ciphertext: ");
//     Serial.println(ciphertext);
    
//     // Decrypt the ciphertext
//     String decryptedtext = decryptV1(ciphertext, key);
    
//     Serial.print("Decrypted text: ");
//     Serial.println(decryptedtext);
    
//     delay(1000);
    
//     // ////////////////////////////////////////////////////////////////////////////////  Testing Section   <<<
//     // ////////////////////////////////////////////////////////////////////////////////  Testing Section   <<<
//     // ////////////////////////////////////////////////////////////////////////////////  Testing Section   <<<
//     // ////////////////////////////////////////////////////////////////////////////////  Testing Section   <<<
//     // ////////////////////////////////////////////////////////////////////////////////  Testing Section   <<<






// #include <string.h>

// const char* key = "mysecretkey"; // the encryption key
// const int keyLen = strlen(key);

// void setup() {
//   Serial.begin(9600);
// }

// void loop() {
//   String plaintext = "Hello, world!";
  
//   // Encrypt the plaintext
//   String ciphertext = encrypt(plaintext, key);
  
//   Serial.print("Plaintext: ");
//   Serial.println(plaintext);
  
//   Serial.print("Ciphertext: ");
//   Serial.println(ciphertext);
  
//   // Decrypt the ciphertext
//   String decryptedtext = decrypt(ciphertext, key);
  
//   Serial.print("Decrypted text: ");
//   Serial.println(decryptedtext);
  
//   delay(1000);
// }

// String encrypt(String input, const char* key) {
//   const int keyLen = strlen(key);
//   String output = "";
  
//   for (int i = 0; i < input.length(); i++) {
//     output += (char)(input.charAt(i) ^ key[i % keyLen]);
//   }
  
//   return output;
// }

// String decrypt(String input, const char* key) {
//   const int keyLen = strlen(key);
//   String output = "";
  
//   for (int i = 0; i < input.length(); i++) {
//     output += (char)(input.charAt(i) ^ key[i % keyLen]);
//   }
  
//   return output;
// }
