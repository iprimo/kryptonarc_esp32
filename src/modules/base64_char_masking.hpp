// Original source - Example of Arduino IDE AES128_Example
#include "string.h"
#include "base64.h"
#include "mbedtls/base64.h"   // https://forum.arduino.cc/t/esp32-base64-decoding/1123601/26



// // Example
//   // String toEncode = "Test encoding";
//   String toEncode = "Test encoding_Test encoding__Test encoding___Test encoding____Test encoding____Test encoding______Test encoding";
//   Serial.println("toEncode >>> ");
//   Serial.println(toEncode);
//   String encoded = base64::encode( toEncode.c_str());
//   Serial.println("encoded >>> ");
//   Serial.println(encoded);

//   char uuu[1024];
//   base64_char_decoding( encoded , uuu );
//   Serial.println("uuu >>> ");
//   Serial.println(uuu);






// #ifndef BASE64_CHAR_ENCODING_HPP
// #define BASE64_CHAR_ENCODING_HPP

// // Source: 
// // https://forum.arduino.cc/t/esp32-base64-decoding/1123601/26

// void base64_char_encoding( char* clear_data, char* encoded_data ) {
//   String encoded_data_string = base64::encode( clear_data );
//   encoded_data = encoded_data_string;

//   // Serial.println("sendStr56>>>>   ");
//   // Serial.println(sendStr56);
//   // String encoded = base64::encode( sendStr56 );
//   // Serial.println("encoded>>>>   ");
//   // Serial.println(encoded);


  // String toEncode = "Test encoding";
  // String encoded = base64::encode( toEncode.c_str());
  // Serial.println("encoded >>> ");
  // Serial.println(encoded);




// }

// #endif

#ifndef BASE64_CHAR_DECODING_HPP
#define BASE64_CHAR_DECODING_HPP
// source: https://forum.arduino.cc/t/esp32-base64-decoding/1123601/26
void base64_char_decoding( String encoded, char* clear_data ) {

  // size_t decodedLength;

  // unsigned char decodedBuffer[1024]; // Adjust buffer size as needed

  // mbedtls_base64_decode(decodedBuffer, sizeof(decodedBuffer), &decodedLength,
  //                      (const unsigned char*)encodedString, strlen(encodedString));

  // decodedBuffer[decodedLength] = '\0'; // Add null terminator for printing

  // // Serial.println("Decoded string:");
  // // Serial.println((char*)decodedBuffer); // Output: This is a test string

  // clear_data = (char*)decodedBuffer ;
  

  
  // const char *encodedString = "VGhpcyBpcyB0aGUgZm9ybWF0"; // Base64-encoded string
  const char *encodedString = encoded.c_str() ; // Base64-encoded string
  size_t decodedLength;

  unsigned char decodedBuffer[1024]; // Adjust buffer size as needed

  mbedtls_base64_decode(decodedBuffer, sizeof(decodedBuffer), &decodedLength,
                       (const unsigned char*)encodedString, strlen(encodedString));

  decodedBuffer[decodedLength] = '\0'; // Add null terminator for printing

  // Serial.println("Decoded string:");
  // Serial.println((char*)decodedBuffer); // Output: This is a test string

  strcpy(clear_data, (char*)decodedBuffer);

}
// source: https://forum.arduino.cc/t/esp32-base64-decoding/1123601/26

  // // const char *encodedString = "VGhpcyBpcyB0aGUgZm9ybWF0"; // Base64-encoded string
  // const char *encodedString = encoded.c_str() ; // Base64-encoded string
  // size_t decodedLength;

  // unsigned char decodedBuffer[100]; // Adjust buffer size as needed

  // mbedtls_base64_decode(decodedBuffer, sizeof(decodedBuffer), &decodedLength,
  //                      (const unsigned char*)encodedString, strlen(encodedString));

  // decodedBuffer[decodedLength] = '\0'; // Add null terminator for printing

  // Serial.println("Decoded string:");
  // Serial.println((char*)decodedBuffer); // Output: This is a test string


#endif
