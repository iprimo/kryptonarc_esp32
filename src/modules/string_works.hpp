
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
bool parseMetaHashData(const char* receivingString, char*& meta, char*& device_hash, char*& global_hash, char*& data, char*& data_decoded) {
  meta = nullptr;
  device_hash = nullptr;
  global_hash = nullptr;
  data = nullptr;
  data_decoded = nullptr;
  int len = strlen(receivingString);
  const char* delim = "||";
  const char* sectionPtrs[4] = {nullptr, nullptr, nullptr, nullptr};
  int sectionIdx = 0;
  const char* searchPtr = receivingString;
  while (sectionIdx < 4) {
    const char* nextPtr = strstr(searchPtr, delim);
    if (nextPtr) {
      sectionPtrs[sectionIdx++] = nextPtr;
      searchPtr = nextPtr + 2;
    } else {
      break;
    }
  }

  // We need 3 delimiters for 4 sections
  if (sectionIdx == 3) {
    // Section 0: data (payload)
    int dataLen = sectionPtrs[0] - receivingString;
    data = new char[dataLen + 1]();
    strncpy(data, receivingString, dataLen);
    data[dataLen] = '\0';

    // Decode base64 data
    data_decoded = new char[1024](); // Adjust size as needed
    base64_string_decoding(String(data), data_decoded);

    // Section 1: device_hash
    int deviceHashLen = sectionPtrs[1] - (sectionPtrs[0] + 2);
    device_hash = new char[deviceHashLen + 1]();
    strncpy(device_hash, sectionPtrs[0] + 2, deviceHashLen);
    device_hash[deviceHashLen] = '\0';

    // Section 2: global_hash
    int globalHashLen = sectionPtrs[2] - (sectionPtrs[1] + 2);
    global_hash = new char[globalHashLen + 1]();
    strncpy(global_hash, sectionPtrs[1] + 2, globalHashLen);
    global_hash[globalHashLen] = '\0';

    // Section 3: meta (metadata)
    int metaLen = len - (sectionPtrs[2] - receivingString) - 2;
    meta = new char[metaLen + 1]();
    strncpy(meta, sectionPtrs[2] + 2, metaLen);
    meta[metaLen] = '\0';

    // Do NOT clean up output pointers here; caller is responsible for freeing them
    return true;
  } else {
    Serial.println("Failed to parse meta, device_hash, global_hash, data from receivingString!");
    // Clean up only if something was allocated in error case
    if (data) { delete[] data; data = nullptr; }
    if (meta) { delete[] meta; meta = nullptr; }
    if (device_hash) { delete[] device_hash; device_hash = nullptr; }
    if (global_hash) { delete[] global_hash; global_hash = nullptr; }
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
  if (meta && strstr(meta, "dHash:d1SHA256")) {
    thisTrafficHashKey = e2prom_variables.hashKey_Internal;
  } else if (meta && strstr(meta, "gHash:g1SHA256")) {
    thisTrafficHashKey = software_parameters_fixed.GLOBAL_SHARED_HASH_KEY;
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
