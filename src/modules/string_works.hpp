#include "system_structs.hpp"

const char* find_values_between_substringsV4(char* str, const char* substringA1, const char* substringA2 ) {
    char* p1 = strstr(str, substringA1);
    if (!p1) return "N_A__" ;

    p1 += strlen(substringA1);
    char* p2 = strstr(p1, substringA2);
    if (!p2) return "N_A__" ;
    
    *p2 = 0;
    return p1 ;
}



char convertStringToChar(String str) {
    int str_len = str.length() + 1;
    char char_array[str_len];
    str.toCharArray(char_array, str_len);
    return char_array[0];
}




char* extractDataAfterDelimiter(char* inputChar, char delimiter) {
  // Find the last occurrence of the delimiter
  char* lastDelimiterPosition = strrchr(inputChar, delimiter);

  // If the delimiter is found, extract the data
  if (lastDelimiterPosition != nullptr) {
    // Point to the character after the delimiter
    char* extractedData = lastDelimiterPosition + 1;

    // Ensure null-termination for safety
    extractedData[strlen(extractedData)] = '\0';

    return extractedData;
  } else {
    // If the delimiter is not found, return nullptr
    return nullptr;
  }
}


bool findSubstring(const char* inputString, const char* subString) {
  int subStrLength = strlen(subString);
  int inputStrLength = strlen(inputString);

  // Iterate through the input string, checking for the substring
  for (int i = 0; i <= inputStrLength - subStrLength; i++) {
    bool found = true;
    for (int j = 0; j < subStrLength; j++) {
      if (inputString[i + j] != subString[j]) {
        found = false;
        break;
      }
    }

    if (found) {
      return true; // Substring found
    }
  }

  return false; // Substring not found
}

bool findSubChar(char* inputString, char subChar) {
  // Iterate through the input string
  for (int i = 0; inputString[i] != '\0'; i++) {
    if (inputString[i] == subChar) {
      // If the sub-char is found, return true
      return true;
    }
  }

  // If the sub-char is not found, return false
  return false;
}


bool splitAtLastDelimiter(char* inputChar, char delimiter, char* dataBeforeDelimiter, char* dataAfterDelimiter) {
  // Find the last occurrence of the delimiter
  char* lastDelimiterPosition = strrchr(inputChar, delimiter);

  // If the delimiter is found, split the string
  if (lastDelimiterPosition != nullptr) {
    *lastDelimiterPosition = '\0';  // Terminate the string before the delimiter

    // Copy the parts into the provided buffers
    strcpy(dataBeforeDelimiter, inputChar);
    strcpy(dataAfterDelimiter, lastDelimiterPosition + 1);
    return true;
  } else {
    // If the delimiter is not found, set the buffers to empty strings
    dataBeforeDelimiter[0] = '\0';
    dataAfterDelimiter[0] = '\0';
    return false;
  }
}
