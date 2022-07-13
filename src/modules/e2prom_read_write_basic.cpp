// // // Source example
// https://stackoverflow.com/questions/56139657/write-string-to-permanent-flash-memory-of-arduino-esp32
// https://stackoverflow.com/questions/56139657/write-string-to-permanent-flash-memory-of-arduino-esp32

#include <Arduino.h>
#include "EEPROM.h"
#include <string>

#define EEPROM_SIZE 64


void e2promFffINitiate() {

    Serial.println("starting now...");

    if (!EEPROM.begin(EEPROM_SIZE)) {
        Serial.println("failed to init EEPROM");
        delay(1000000);
    }
}

void e2promWriteWFFFFFForks() {
    int starting_addr = 64;
    int addr = 0;
    // the sample text which we are storing in EEPROM
    char ssid[64] = "CARNIVAL OF RUST 11111 - Section 2";


    // writing byte-by-byte to EEPROM
    for (int i = 0; i < EEPROM_SIZE; i++) {
        EEPROM.write(addr + starting_addr, ssid[i]);
        addr += 1;
    }
    EEPROM.commit();
}

void e2promReadWFFFFFForks() {
    int starting_addr = 64;
    int addr = 0;
  
    // reading byte-by-byte from EEPROM
    for (int i = 0; i < EEPROM_SIZE; i++) {
        byte readValue = EEPROM.read(i + starting_addr );

        if (readValue == 0) {
            break;
        }

        char readValueChar = char(readValue);
        Serial.print(readValueChar);
    }
}



void e2promReadWAAAAorks() {
    int starting_addr = 0;
    int addr = 0;
  
    // reading byte-by-byte from EEPROM
    for (int i = 0; i < EEPROM_SIZE; i++) {
        byte readValue = EEPROM.read(i + starting_addr );

        if (readValue == 0) {
            break;
        }

        char readValueChar = char(readValue);
        Serial.print(readValueChar);
    }
}
