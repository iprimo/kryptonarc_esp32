#include <Arduino.h>
#include <stdio.h>
#include <string.h>
#include "EEPROM.h"
#include "system_structs.hpp"

extern SOFTWARE_GLOBAL_PARAMETERS_FIXED software_parameters_fixed;
extern DEVICE_GLOBAL_HARDWARE_PARAMETERS_FIXED constrcut_MCU_ID_fixed;
extern E2PROM_STORED_DATA_FIXED e2prom_variables;
extern BROADCAST_GLOBAL_VAR broadcast_global_variables;

extern HardwareSerial Serial;

#define EEPROM_BLOCKS_SIZE 256
#define ACTIVE_EEPROM_SIZE 4096 

// DO NOT CHANGE ORDER OF ARRAY BELOW
// DO NOT MOVE THE ORDER OR CHANGE THE ORDER OF THIS ARRAY
// Total E2PROM block4096/256 = 16
const char *arr[] = {
    "board_model",
    "hardware_uuid",
    "vender_xc",
    "device_xc",
    "tenant_xc",
    "manufacturer_xc",
    
    "lastResortKeyOffline_Internal",
    "keySmithKeyOnline_Internal",
    "encryptionKey_Internal",
    "hashKey_Internal",

    "lastResortKeyOffline02_Internal",
    "keySmithKeyOnline02_Internal",
    "encryptionKey02_Internal",
    "hashKey02_Internal",

    "tempName06",
    "tempName07"
};


const int arr_len = sizeof(arr) / sizeof(arr[0]);


int find_string_in_array(const char* str_var) {
    int i;
    for (i = 0; i < arr_len; i++) {
        if ( strcmp( str_var ,  arr[i] ) == 0  ) {
            return i; // return the index of the match
        }
    }
    return -1; // indicate no match was found
}


const char* e2promInitiate() {
    if ( EEPROM.begin( ACTIVE_EEPROM_SIZE ) ) {
        const char* return_var = "EEPROM initized";
        return return_var;
    } else {
        Serial.println("Failed to init EEPROM");
        delay(1000000);
        const char* return_var = "Failed to init EEPROM";
        return return_var;
    }
}



const char* e2promWriteWorks( const char* type_selector, const char* data) {
    int idx = find_string_in_array( type_selector );
    
    // writing byte-by-byte to EEPROM
    int starting_mem_address = EEPROM_BLOCKS_SIZE  * idx;
    for (int i = 0; i < EEPROM_BLOCKS_SIZE; i++) {
        EEPROM.write( (starting_mem_address + i ), data[i] );
    }
    EEPROM.commit();

    const char* return_var = "Done Writing";
    return return_var;
}

const char* e2promReadWorks( const char* type_selector ) {
    char* e2prom_DataAssembled = new char[EEPROM_BLOCKS_SIZE](); // () initializes all elements to null
    
    int idx = find_string_in_array( type_selector );

    // reading byte-by-byte from EEPROM
    int starting_mem_address = EEPROM_BLOCKS_SIZE * idx;
    for (int i = 0; i < EEPROM_BLOCKS_SIZE ; i++) {
        byte readValue = EEPROM.read( starting_mem_address + i  );

        if (readValue == 0) {
            break;
        }

        char read_ValueChar = char(readValue);
        e2prom_DataAssembled[ i ] = read_ValueChar;
    }

	return e2prom_DataAssembled;
}


E2PROM_STORED_DATA_FIXED e2promReadAllWorks( ) {
    E2PROM_STORED_DATA_FIXED temp_construct;
    
    // Define 
    strcpy( temp_construct.board_model, e2promReadWorks( "board_model" )  );
    strcpy( temp_construct.hardware_uuid, e2promReadWorks( "hardware_uuid" )  );
    strcpy( temp_construct.vender_xc, e2promReadWorks( "vender_xc" ) );
    strcpy( temp_construct.device_xc, e2promReadWorks( "device_xc" ) );
    strcpy( temp_construct.tenant_xc, e2promReadWorks( "tenant_xc" ) );
    strcpy( temp_construct.manufacturer_xc, e2promReadWorks( "manufacturer_xc" ) );
    strcpy( temp_construct.lastResortKeyOffline_Internal, e2promReadWorks( "lastResortKeyOffline_Internal" ) );
    strcpy( temp_construct.keySmithKeyOnline_Internal, e2promReadWorks( "keySmithKeyOnline_Internal" ) );
    strcpy( temp_construct.encryptionKey_Internal, e2promReadWorks( "encryptionKey_Internal" ) );
    strcpy( temp_construct.hashKey_Internal, e2promReadWorks( "hashKey_Internal" ) );
    strcpy( temp_construct.lastResortKeyOffline02_Internal, e2promReadWorks( "lastResortKeyOffline02_Internal" ) );
    strcpy( temp_construct.keySmithKeyOnline02_Internal, e2promReadWorks( "keySmithKeyOnline02_Internal" ) );
    strcpy( temp_construct.encryptionKey02_Internal, e2promReadWorks( "encryptionKey02_Internal" ) );
    strcpy( temp_construct.hashKey02_Internal, e2promReadWorks( "hashKey02_Internal" ) );
    strcpy( temp_construct.tempName06, e2promReadWorks( "tempName06" ) );
    strcpy( temp_construct.tempName07, e2promReadWorks( "tempName07" ) );


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


const char* generateUUIDString( ) {
    const char* charset = "0123456789abcdef";
    char* uuid = new char[37](); // () initializes all elements to null
    for (int i = 0; i < 36; i++) {
        if (i == 8 || i == 13 || i == 18 || i == 23) {
        uuid[i] = '-';
        } else {
        uuid[i] = charset[random(16)];
        }
    }
    uuid[36] = '\0'; // Null-terminate the string
    return uuid;
}

bool isUUIDValid(char* str) {
    const int len = strlen(str);

    if (len != 36) {
        return false;
    }

    for (int i = 0; i < len; i++) {
        if (i == 8 || i == 13 || i == 18 || i == 23) {
            if (str[i] != '-') {
                return false;
            }
        } else {
            if (!isxdigit(str[i])) {
                return false;
            }
        }
    }

    return true;
}




void wipeAllAndReissueAllBasics( ) {

    ////////////////////////////////////////////////////////////////////////

    e2promWipeAllData();
    
    // // Board Model ID
    // const char* board_model_var = "KA_CB_G090V5B";
    // e2promWriteWorks(  "board_model" , board_model_var ) ;
    

    e2promWriteWorks(  "hardware_uuid" , generateUUIDString() ) ;

    e2prom_variables = e2promReadAllWorks();
}
