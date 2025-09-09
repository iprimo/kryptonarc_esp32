#ifndef E2PROM_WORKS_HPP
#define E2PROM_WORKS_HPP

#include <Arduino.h>
#include <stdio.h>
#include <string.h>
#include "EEPROM.h"
#include "system_structs.hpp"
#include "modules/system_structs.hpp"

// extern SOFTWARE_GLOBAL_PARAMETERS_VAR software_parameters_variables;
// extern SOFTWARE_GLOBAL_PARAMETERS_FIXED software_parameters_fixed;
// extern DEVICE_GLOBAL_HARDWARE_PARAMETERS_FIXED constrcut_mcu_id_fixed;
// extern E2PROM_STORED_DATA_FIXED e2prom_variables;
// extern BROADCAST_GLOBAL_VAR broadcast_global_variables;

extern HardwareSerial Serial;

#define EEPROM_BLOCKS_SIZE 64
#define ACTIVE_EEPROM_SIZE 4096 

// DO NOT CHANGE ORDER OF ARRAY BELOW
// DO NOT MOVE THE ORDER OR CHANGE THE ORDER OF THIS ARRAY
// Total E2PROM block - 4096/64=64
const char *arr[] = {
    "storage_version"      ,
    "storage_config_version", 
    "hardware_uuid",
    "board_model",
    "vender_xc",
    "device_xc",
    "tenant_xc",
    "manufacturer_xc",    

    "lastResortKeyOffline_Internal",
    "lastResortKeyOffline02_Internal",

    "keySmithKeyOnline_Internal",
    "keySmithKeyOnline02_Internal",

    "encryptionKey_Internal",
    "encryptionKey02_Internal",

    "hashKey_Internal",
    "hashKey02_Internal"
    
    // "tempName17",
    // "tempName18",
    // "tempName19",
    // "tempName20",
    // "tempName21",
    // "tempName22",
    // "tempName23",
    // "tempName24",
    // "tempName25",
    // "tempName26",
    // "tempName27",
    // "tempName28",
    // "tempName29",
    // "tempName30",
    // "tempName31",
    // "tempName32",
    // "tempName33",
    // "tempName34",
    // "tempName35",
    // "tempName36",
    // "tempName37",
    // "tempName38",
    // "tempName39",
    // "tempName40",
    // "tempName41",
    // "tempName42",
    // "tempName43",
    // "tempName44",
    // "tempName45",
    // "tempName46",
    // "tempName47",
    // "tempName48",
    // "tempName49",
    // "tempName50",
    // "tempName51",
    // "tempName52",
    // "tempName53",
    // "tempName54",
    // "tempName55",
    // "tempName56",
    // "tempName57",
    // "tempName58",
    // "tempName59",
    // "tempName60",
    // "tempName61",
    // "tempName62",
    // "tempName63",
    // "tempName64"
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


const char* e2prom_initialization () {
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
    strcpy( temp_construct.current_shackle_lock_configuration, e2promReadWorks( "current_shackle_lock_configuration" ) );
    // strcpy( temp_construct.tempName16, e2promReadWorks( "tempName16" ) );
    // strcpy( temp_construct.tempName17, e2promReadWorks( "tempName17" ) );
    // strcpy( temp_construct.tempName18, e2promReadWorks( "tempName18" ) );
    // strcpy( temp_construct.tempName19, e2promReadWorks( "tempName19" ) );
    // strcpy( temp_construct.tempName20, e2promReadWorks( "tempName20" ) );
    // strcpy( temp_construct.tempName21, e2promReadWorks( "tempName21" ) );
    // strcpy( temp_construct.tempName22, e2promReadWorks( "tempName22" ) );
    // strcpy( temp_construct.tempName23, e2promReadWorks( "tempName23" ) );
    // strcpy( temp_construct.tempName24, e2promReadWorks( "tempName24" ) );
    // strcpy( temp_construct.tempName25, e2promReadWorks( "tempName25" ) );
    // strcpy( temp_construct.tempName26, e2promReadWorks( "tempName26" ) );
    // strcpy( temp_construct.tempName27, e2promReadWorks( "tempName27" ) );
    // strcpy( temp_construct.tempName28, e2promReadWorks( "tempName28" ) );
    // strcpy( temp_construct.tempName29, e2promReadWorks( "tempName29" ) );
    // strcpy( temp_construct.tempName30, e2promReadWorks( "tempName30" ) );
    // strcpy( temp_construct.tempName31, e2promReadWorks( "tempName31" ) );
    // strcpy( temp_construct.tempName32, e2promReadWorks( "tempName32" ) );
    // strcpy( temp_construct.tempName33, e2promReadWorks( "tempName33" ) );
    // strcpy( temp_construct.tempName34, e2promReadWorks( "tempName34" ) );
    // strcpy( temp_construct.tempName35, e2promReadWorks( "tempName35" ) );
    // strcpy( temp_construct.tempName36, e2promReadWorks( "tempName36" ) );
    // strcpy( temp_construct.tempName37, e2promReadWorks( "tempName37" ) );
    // strcpy( temp_construct.tempName38, e2promReadWorks( "tempName38" ) );
    // strcpy( temp_construct.tempName39, e2promReadWorks( "tempName39" ) );
    // strcpy( temp_construct.tempName40, e2promReadWorks( "tempName40" ) );
    // strcpy( temp_construct.tempName41, e2promReadWorks( "tempName41" ) );
    // strcpy( temp_construct.tempName42, e2promReadWorks( "tempName42" ) );
    // strcpy( temp_construct.tempName43, e2promReadWorks( "tempName43" ) );
    // strcpy( temp_construct.tempName44, e2promReadWorks( "tempName44" ) );
    // strcpy( temp_construct.tempName45, e2promReadWorks( "tempName45" ) );
    // strcpy( temp_construct.tempName46, e2promReadWorks( "tempName46" ) );
    // strcpy( temp_construct.tempName47, e2promReadWorks( "tempName47" ) );
    // strcpy( temp_construct.tempName48, e2promReadWorks( "tempName48" ) );
    // strcpy( temp_construct.tempName49, e2promReadWorks( "tempName49" ) );
    // strcpy( temp_construct.tempName50, e2promReadWorks( "tempName50" ) );
    // strcpy( temp_construct.tempName51, e2promReadWorks( "tempName51" ) );
    // strcpy( temp_construct.tempName52, e2promReadWorks( "tempName52" ) );
    // strcpy( temp_construct.tempName53, e2promReadWorks( "tempName53" ) );
    // strcpy( temp_construct.tempName54, e2promReadWorks( "tempName54" ) );
    // strcpy( temp_construct.tempName55, e2promReadWorks( "tempName55" ) );
    // strcpy( temp_construct.tempName56, e2promReadWorks( "tempName56" ) );
    // strcpy( temp_construct.tempName57, e2promReadWorks( "tempName57" ) );
    // strcpy( temp_construct.tempName58, e2promReadWorks( "tempName58" ) );
    // strcpy( temp_construct.tempName59, e2promReadWorks( "tempName59" ) );
    // strcpy( temp_construct.tempName60, e2promReadWorks( "tempName60" ) );
    // strcpy( temp_construct.tempName61, e2promReadWorks( "tempName61" ) );
    // strcpy( temp_construct.tempName62, e2promReadWorks( "tempName62" ) );
    // strcpy( temp_construct.tempName63, e2promReadWorks( "tempName63" ) );
    // strcpy( temp_construct.tempName64, e2promReadWorks( "tempName64" ) );


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
    // e2promWriteWorks(  "current_shackle_lock_configuration" ,"na" ) ;

    e2prom_variables = e2promReadAllWorks();
}

#endif 