// // // Source example
// https://stackoverflow.com/questions/56139657/write-string-to-permanent-flash-memory-of-arduino-esp32
// https://stackoverflow.com/questions/56139657/write-string-to-permanent-flash-memory-of-arduino-esp32

#include <Arduino.h>
#include "EEPROM.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>

#define EEPROM_SIZE 64 * 4


void e2proFFFFmINitiate() {

    Serial.println("starting now...");

    if (!EEPROM.begin(EEPROM_SIZE)) {
        Serial.println("failed to init EEPROM");
        delay(1000000);
    }
}


void e2proFFFFmWriteWFFFFFForks(String lock_xigcode, String tenant_xigcode, String aes_key_01, String aes_key_02 ) {
    int starting_addr = 64;
    int addr = 0;
    // the sample text which we are storing in EEPROM
    char lock_xigcode_local[64] = "CARNIVAL OF RUST 11111 - Section 1 - lock_xigcode";
    char tenant_xigcode_local[64] = "CARNIVAL OF RUST 11111 - Section 1 - tenant_xigcode";
    char aes1_local[64] = "CARNIVAL OF RUST 11111 - Section 1 - aes1";
    char aes2_local[64] = "CARNIVAL OF RUST 11111 - Section 1 - aes2";
    
    // char *con = malloc(256);
    char *con = (char*)malloc(256);
    memcpy(con, lock_xigcode_local, 64);
    memcpy(con + 64, tenant_xigcode_local, 64);
    memcpy(con + 64 + 64, aes1_local, 64);
    memcpy(con + 64 + 64 + 64, aes2_local, 64);


    // writing byte-by-byte to EEPROM
    for (int i = 0; i < (EEPROM_SIZE * 4); i++) {
        Serial.print( "i : " );
        Serial.print( i );
        Serial.print( "     con[i] : " ); 
        Serial.print( con[i] );
        Serial.println( "================================" );
        EEPROM.write(addr + starting_addr, con[i]);
        addr += 1;
    }
    EEPROM.commit();
    Serial.println( "================================ End of Commit " );
}

void e2proFFFFmReadWFFFFFForks() {
    Serial.println( "================================ Start of READ" );
    int starting_addr = 0;
    int addr = 0;
  
    // reading byte-by-byte from EEPROM
    for (int i = 0; i < ( EEPROM_SIZE * 3 ); i++) {
        byte readValue = EEPROM.read(i + starting_addr );

        // Serial.print( "i : " );
        // Serial.print( i );
        // Serial.print( "     readValue : " ); 
        // Serial.print( readValue );
        // Serial.println( "================================" );

        // if (readValue == 0) {
        //     Serial.println( "Value 0 was read <<<< " );
        //     // break;
        // }

        char readValueChar = char(readValue);
        Serial.print(readValueChar);
    }
    Serial.println( "================================ End of  of READ" );
}


