// #include "global_variables.hpp"
#include "system_structs.cpp"

extern BROADCAST_GLOBAL_VAR broadcast_global_variables;

String find_values_between_substringsV3(char* str, const char* substringA1, const char* substringA2 ) {
    char* p1 = strstr(str, substringA1);
    // if (!p1) return strdup("") ;
    if (!p1) return "N_A__" ;

    p1 += strlen(substringA1);
    char* p2 = strstr(p1, substringA2);
    if (!p2) return strdup("") ;
    if (!p2) return "N_A__" ;
    
    *p2 = 0;
    return p1 ;
}

String encryptV1(String input, const char* key) {
  const int keyLen = strlen(key);
  String output = "";
  String outputX2 = "||";
  
  for (int i = 0; i < input.length(); i++) {
    output += (char)(input.charAt(i) ^ key[i % keyLen]);
    outputX2 = outputX2 + "|" + (input.charAt(i) ^ key[i % keyLen]);
  }
  outputX2 = outputX2 + "|||";

  Serial.print("outputX2: ");
  Serial.println(outputX2);

  return output;
}

String decryptV1(String input, const char* key) {
  const int keyLen = strlen(key);
  String output = "";
  
  for (int i = 0; i < input.length(); i++) {
    output += (char)(input.charAt(i) ^ key[i % keyLen]);
  }
  
  return output;
}



// // Set up key and data to encrypt
// String keyString = "0123456789abcdeffedcba9876543210";
// uint8_t key[16];
// for (int i = 0; i < keyString.length(); i += 2) {
//   key[i/2] = strtoul(keyString.substring(i, i+2).c_str(), NULL, 16);
// }
// String data = "hello world!";


