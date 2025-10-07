
#ifndef STRING_WORKS_HPP
#define STRING_WORKS_HPP

#include "system_structs.hpp"
#include "modules/sha_hash.hpp"
#include "modules/base64_char_masking.hpp"

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



void removeSubstring(char* original, const char* substringToRemove, char* result) {
    char* start = strstr(original, substringToRemove);

    if (start != NULL) {
        int length = start - original;
        strncpy(result, original, length);
        result[length] = '\0';

        strcat(result, start + strlen(substringToRemove));
    } else {
        // If substring not found, copy the original to result
        strcpy(result, original);
    }
}

// Helper function to parse meta, hash, and data from receivingString
bool parseMetaHashData(const char* receivingString, char*& meta, char*& hash, char*& data, char*& data_decoded) {
  meta = nullptr;
  hash = nullptr;
  data = nullptr;
  data_decoded = nullptr;
  int len = strlen(receivingString);
  int firstPipe = -1;
  int lastPipe = -1;
  const char* delim = "||";
  const char* firstPtr = strstr(receivingString, delim);
  const char* lastPtr = nullptr;
  if (firstPtr) {
    firstPipe = firstPtr - receivingString;
    const char* searchPtr = firstPtr + 2;
    while (true) {
      const char* nextPtr = strstr(searchPtr, delim);
      if (nextPtr) {
        lastPtr = nextPtr;
        searchPtr = nextPtr + 2;
      } else {
        break;
      }
    }
    if (lastPtr) {
      lastPipe = lastPtr - receivingString;
    } else {
      lastPipe = firstPipe;
    }
  }

  if (firstPipe != -1 && lastPipe != -1 && firstPipe != lastPipe) {
    data = new char[firstPipe + 1]();
    strncpy(data, receivingString, firstPipe);
    data[firstPipe] = '\0';

    // Decode base64 data
    data_decoded = new char[1024](); // Adjust size as needed
    base64_string_decoding(String(data), data_decoded);

    int metaLen = len - lastPipe - 2;
    meta = new char[metaLen + 1]();
    strncpy(meta, receivingString + lastPipe + 2, metaLen);
    meta[metaLen] = '\0';

    int hashLen = lastPipe - firstPipe - 2;
    hash = new char[hashLen + 1]();
    strncpy(hash, receivingString + firstPipe + 2, hashLen);
    hash[hashLen] = '\0';

    // Do NOT clean up output pointers here; caller is responsible for freeing them
    return true;
  } else {
    Serial.println("Failed to parse meta, hash, data from receivingString!");
    // Clean up only if something was allocated in error case
    if (data) { delete[] data; data = nullptr; }
    if (meta) { delete[] meta; meta = nullptr; }
    if (hash) { delete[] hash; hash = nullptr; }
    if (data_decoded) { delete[] data_decoded; data_decoded = nullptr; }
    return false;
  }
}

// Helper function to verify hash using meta, hash, and data

    // 0x-0	: global hash and enrypton keys used
    // 0x-1	: device hash and enrypton keys used

bool verifyTrafficHash(const char* meta, const char* hash, char* data) {
  char hash256ResultArray[65];
  const char* thisTrafficHashKey = nullptr;
  bool result = false;
  if (meta && strstr(meta, "hash:g1SHA256")) {
    thisTrafficHashKey = software_parameters_fixed.GLOBAL_SHARED_HASH_KEY;
  } else if (meta && strstr(meta, "hash:d1SHA256")) {
    thisTrafficHashKey = e2prom_variables.hashKey_Internal;
  } else {
    Serial.println("No valid hash type found in meta!");
    return false;
  }

  hashSHA256((const char*)data, thisTrafficHashKey, hash256ResultArray);
  if (hash && strcmp(hash, hash256ResultArray) == 0) {
    Serial.println("hash OK!");
    result = true;
  } else {
    Serial.println("hash Error!");
    result = false;
  }

  // No dynamic allocations in this function, but if you add any, clean up here
  return result;
}


#endif
