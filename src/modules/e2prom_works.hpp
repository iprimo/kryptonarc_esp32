#include <Arduino.h>
#include <stdio.h>
#include <string.h>
#include "EEPROM.h"
#include "system_structs.cpp"


#define EEPROM_BLOCKS_SIZE 256
#define ACTIVE_EEPROM_SIZE 4096 

// DO NOT MOVE THE ORDER OR CHANGE THE ORDER OF THIS ARRAY
// Total E2PROM block4096/256 = 16
const char *arr[] = {
    "board_model",
    "hardware_uuid",
    "vender_uuid",
    "device_addr",
    "tenant_addr",
    "secure_code_01",
    "secure_code_02",
    "secure_code_03",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    ""
    
};

const int arr_len = sizeof(arr) / sizeof(arr[0]);


int find_string_in_array(String str_var) {
    int i;
    for (i = 0; i < arr_len; i++) {
        if ( str_var.compareTo( arr[i] ) ) {
            return i; // return the index of the match
        }
    }
    return -1; // indicate no match was found
}


String e2promInitiate() {
    Serial.println("e2prom - starting now...");
    if ( !EEPROM.begin( ACTIVE_EEPROM_SIZE ) ) {
        Serial.println("failed to init EEPROM");
        delay(1000000);
        return "error occured";
    } else {
        return "e2prom initiated";
    }
}



String e2promWriteWorks( String type_selector, String data) {
    int idx = find_string_in_array( type_selector );

    char *str_in_char = new char[data.length() + 1];
    strcpy(str_in_char, data.c_str());
    
    // writing byte-by-byte to EEPROM
    int starting_mem_address = EEPROM_BLOCKS_SIZE  * idx;
    for (int i = 0; i < EEPROM_BLOCKS_SIZE; i++) {
        EEPROM.write( (starting_mem_address + i ), str_in_char[i] );
    }
    EEPROM.commit();

	return "Done Writing";
}

String e2promReadWorks( String type_selector ) {
    Serial.println("*******");
    Serial.println(" type_selector ");
    Serial.print( type_selector );
    Serial.println("*******");
    
    int idx = find_string_in_array( type_selector );

    Serial.println("*******");
    Serial.println(" idx ");
    Serial.print( idx );
    Serial.println("*******");

    String return_variable = "";
    // reading byte-by-byte from EEPROM
    int starting_mem_address = EEPROM_BLOCKS_SIZE * idx;
    for (int i = 0; i < EEPROM_BLOCKS_SIZE ; i++) {
        byte readValue = EEPROM.read( starting_mem_address + i  );

        if (readValue == 0) {
            break;
        }

        char readValueChar = char(readValue);
        return_variable = return_variable + readValueChar;
    }
	return return_variable;
}


char convertStringToChar(String str) {
    int str_len = str.length() + 1;
    char char_array[str_len];
    str.toCharArray(char_array, str_len);
    return char_array[0];
}

E2PROM_STORED_DATA_FIXED e2promReadAllWorks( ) {
    E2PROM_STORED_DATA_FIXED temp_construct;
    
    // Define 
    String str = e2promReadWorks(  "board_model" );
    // Length (with one extra character for the null terminator)
    int str_len = str.length() + 1; 
    // Prepare the character array (the buffer) 
    char char_array[str_len];
    // Copy it over 
    str.toCharArray(temp_construct.board_model, str_len);

    str = e2promReadWorks(  "hardware_uuid" )    ;       str_len = str.length() + 1      ;      char_array[str_len]; str.toCharArray(temp_construct.hardware_uuid, str_len);
    str = e2promReadWorks(  "vender_uuid" )    ;       str_len = str.length() + 1      ;      char_array[str_len]; str.toCharArray(temp_construct.vender_uuid, str_len);
    str = e2promReadWorks(  "device_addr" )    ;       str_len = str.length() + 1      ;      char_array[str_len]; str.toCharArray(temp_construct.device_addr, str_len);
    str = e2promReadWorks(  "tenant_addr" )    ;       str_len = str.length() + 1      ;      char_array[str_len]; str.toCharArray(temp_construct.tenant_addr, str_len);
    str = e2promReadWorks(  "secure_code_01" )    ;       str_len = str.length() + 1      ;      char_array[str_len]; str.toCharArray(temp_construct.secure_code_01, str_len);
    str = e2promReadWorks(  "secure_code_02" )    ;       str_len = str.length() + 1      ;      char_array[str_len]; str.toCharArray(temp_construct.secure_code_02, str_len);
    str = e2promReadWorks(  "secure_code_03" )    ;       str_len = str.length() + 1      ;      char_array[str_len]; str.toCharArray(temp_construct.secure_code_03, str_len);

	return temp_construct;
}




void e2promWipeAllData( ) {

    ////////////////////////////////////////////////////////////////////////
    for (int i = 0; i < ACTIVE_EEPROM_SIZE; i++) {
        EEPROM.write( i, 255 );
    }
    EEPROM.commit();
    ////////////////////////////////////////////////////////////////////////
    for (int i = 0; i < ACTIVE_EEPROM_SIZE; i++) {
        EEPROM.write( i, 0 );
    }
    EEPROM.commit();
    ////////////////////////////////////////////////////////////////////////
    
}


String generateUUIDString( ) {
  const char* charset = "0123456789abcdef";
  char uuid[37];
  for (int i = 0; i < 36; i++) {
    if (i == 8 || i == 13 || i == 18 || i == 23) {
      uuid[i] = '-';
    } else {
      uuid[i] = charset[random(16)];
    }
  }
  uuid[36] = '\0'; // Null-terminate the string
  return String(uuid);
}


