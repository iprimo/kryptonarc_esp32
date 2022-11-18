// // // Source example
// https://stackoverflow.com/questions/56139657/write-string-to-permanent-flash-memory-of-arduino-esp32
// https://stackoverflow.com/questions/56139657/write-string-to-permanent-flash-memory-of-arduino-esp32

#include <Arduino.h>
#include <string>
#include "EEPROM.h"


int padlock_addr = 0;
int tenant_addr = 64;
int aes_01_code_addr = 128;
int aes_02_code_addr = 192;
int aes_03_code_addr = 256;
int locksmith_01_lock_verification = 320;
int locksmith_02_lock_verification = 384;
int locksmith_03_lock_verification = 448;
int placeholder_01 = 512;
int placeholder_02 = 576; // ->640

#define EEPROM_BLOCKS_SIZE 64
#define ACTIVE_EEPROM_SIZE 640 

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


String e2promWriteWorks(String type_selector, String data) {
    int starting_address = -1;
    if ( type_selector == "padlock_addr"){
        starting_address = padlock_addr ;
    } else if ( type_selector == "tenant_addr"){
        starting_address = tenant_addr ;
    } else if ( type_selector == "aes_01_code_addr"){
        starting_address = aes_01_code_addr ;
    } else if ( type_selector == "aes_02_code_addr"){
        starting_address = aes_02_code_addr ;
    } else if ( type_selector == "aes_03_code_addr"){
        starting_address = aes_03_code_addr ;
    } else if ( type_selector == "locksmith_01_lock_verification"){
        starting_address = locksmith_01_lock_verification ;
    } else if ( type_selector == "locksmith_02_lock_verification"){
        starting_address = locksmith_02_lock_verification ;
    } else if ( type_selector == "locksmith_03_lock_verification"){
        starting_address = locksmith_03_lock_verification ;
    } else if ( type_selector == "placeholder_01"){
        starting_address = placeholder_01 ;
    } else if ( type_selector == "placeholder_02"){
        starting_address = placeholder_02 ;
    }

    // Serial.print(">>>>>   type_selector: ");
    // Serial.print(type_selector);
    // Serial.println("<<<<<");

    char *str_in_char = new char[data.length() + 1];
    strcpy(str_in_char, data.c_str());
    
    // writing byte-by-byte to EEPROM
    for (int i = 0; i < EEPROM_BLOCKS_SIZE; i++) {
        EEPROM.write( (starting_address + i ), str_in_char[i] );
    }
    EEPROM.commit();

	return "Done Writing";
}

String e2promReadWorks( String type_selector ) {
    int starting_address = -1;
    String sss = "";
    if ( type_selector == "padlock_addr"){
        starting_address = padlock_addr ;
    } else if ( type_selector == "tenant_addr"){
        starting_address = tenant_addr ;
    } else if ( type_selector == "aes_01_code_addr"){
        starting_address = aes_01_code_addr ;
    } else if ( type_selector == "aes_02_code_addr"){
        starting_address = aes_02_code_addr ;
    } else if ( type_selector == "aes_03_code_addr"){
        starting_address = aes_03_code_addr ;
    } else if ( type_selector == "locksmith_01_lock_verification"){
        starting_address = locksmith_01_lock_verification ;
    } else if ( type_selector == "locksmith_02_lock_verification"){
        starting_address = locksmith_02_lock_verification ;
    } else if ( type_selector == "locksmith_03_lock_verification"){
        starting_address = locksmith_03_lock_verification ;
    } else if ( type_selector == "placeholder_01"){
        starting_address = placeholder_01 ;
    } else if ( type_selector == "placeholder_02"){
        starting_address = placeholder_02 ;
    }

    // reading byte-by-byte from EEPROM
    // char str[64] = "";
    for (int i = starting_address; i < ( EEPROM_BLOCKS_SIZE + starting_address ); i++) {
        byte readValue = EEPROM.read(i);

        if (readValue == 0) {
            break;
        }

        char readValueChar = char(readValue);
        // Serial.print(readValueChar);
        // strncat( str, &readValueChar, 1 );
        sss = sss + readValueChar;
    }
    // Serial.println("}} ");
    // Serial.println(sss);
    // Serial.println("----------111");
	return sss;
}





