#ifndef STRING_WORKS_HPP
#define STRING_WORKS_HPP

#include "system_structs.hpp"

const char* find_values_between_substringsV4(char* str, const char* substringA1, const char* substringA2 ) {
    char* p1 = strstr(str, substringA1);
    if (!p1) return "NA_SUB_STRING_01" ;

    p1 += strlen(substringA1);
    char* p2 = strstr(p1, substringA2);
    if (!p2) return "NA_SUB_STRING_02" ;
    
    *p2 = 0;
    return p1 ;
}

const char* find_values_between_substringsV5(const char* str, const char* substringA1, const char* substringA2) {
    const char* p1 = strstr(str, substringA1);
    if (!p1) return "NA_SUB_STRING_11";

    p1 += strlen(substringA1);
    const char* p2 = strstr(p1, substringA2);
    if (!p2) return "NA_SUB_STRING_22";

    // Create a copy of the substring to avoid modifying the original string
    size_t substring_length = p2 - p1;
    char* result = new char[substring_length + 1];
    strncpy(result, p1, substring_length);
    result[substring_length] = '\0';

    return result;
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

char* extract_substring( int starting_index, const char* original_string) {
  // Get the length of the original string
  int length = strlen(original_string);

  // Calculate the starting index (3 in this case)
  // int starting_index = 3;

  // Ensure the starting index is within bounds
  if (starting_index >= length) {
    return NULL;  // Handle invalid index
  }

  // Allocate memory for the substring, including space for the null terminator
  char* substring = new char[length - starting_index + 1];

  // Copy the characters from the starting index to the end of the original string
  strncpy(substring, original_string + starting_index, length - starting_index);

  // Add the null terminator
  substring[length - starting_index] = '\0';

  return substring;
}



#endif
