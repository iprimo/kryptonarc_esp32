// // // Source example
// https://stackoverflow.com/questions/56139657/write-string-to-permanent-flash-memory-of-arduino-esp32
// https://stackoverflow.com/questions/56139657/write-string-to-permanent-flash-memory-of-arduino-esp32

#include <Arduino.h>
#include "EEPROM.h"
#include <string>


int padlock_addr = 0;
int tenant_addr = 64;
int aes_01_code_addr = 128;
int aes_02_code_addr  = 192;
#define EEPROM_BLOCKS_SIZE 64
#define EEPROM_SIZE 256 // 64 * 5

String e2promInitiate() {
    Serial.println("e2prom - starting now...");
    if (!EEPROM.begin(EEPROM_SIZE)) {
        Serial.println("failed to init EEPROM");
        delay(1000000);
        return "error occured";
    } else {
        return "e2prom initiated";
    }
}


String e2promWriteWorks(String type_selector, String data) {
    int starting_address = 256;
     if ( type_selector == "padlock"){
        starting_address = padlock_addr ;
    } else if ( type_selector == "tenant"){
        starting_address = tenant_addr ;
    } else if ( type_selector == "aes_01"){
        starting_address = aes_01_code_addr ;
    } else if ( type_selector == "aes_02"){
        starting_address = aes_02_code_addr ;
    }

    char *str_in_char = new char[data.length() + 1];
    strcpy(str_in_char, data.c_str());
    

    // Serial.println("e2promWriteWorks 5232345>>> ");
    // Serial.println(type_selector);
    // Serial.println("    >>> 45820 >>> ");
    // Serial.println(starting_address);
    

    // writing byte-by-byte to EEPROM
    for (int i = 0; i < EEPROM_BLOCKS_SIZE; i++) {
        EEPROM.write( (starting_address + i ), str_in_char[i] );
    }
    EEPROM.commit();

	return "Done Writing";
}

String e2promReadWorks( String type_selector ) {
    int starting_address = 256;
     if ( type_selector == "padlock"){
        starting_address = padlock_addr ;
    } else if ( type_selector == "tenant"){
        starting_address = tenant_addr ;
    } else if ( type_selector == "aes_01"){
        starting_address = aes_01_code_addr ;
    } else if ( type_selector == "aes_02"){
        starting_address = aes_02_code_addr ;
    }

    // Serial.println("e2promReadWorks 467456>>> ");
    // Serial.println(type_selector);
    // Serial.println("    >>> 6786 >>> ");
    // Serial.println(starting_address);

    // reading byte-by-byte from EEPROM
    for (int i = starting_address; i < ( EEPROM_BLOCKS_SIZE + starting_address); i++) {
        byte readValue = EEPROM.read(i);

        if (readValue == 0) {
            break;
        }

        char readValueChar = char(readValue);
        Serial.print(readValueChar);
    }
	return "111as";
}






// String e2promWriteTest() {

//     std::string str = "CARNIVAL OF RUST 11112111131111999";
//     char *ssid = new char[str.length() + 1];
//     strcpy(ssid, str.c_str());
//     // Serial.println(ssid.length() );

//     // writing byte-by-byte to EEPROM
//     for (int i = 0; i < EEPROM_SIZE; i++) {
//         EEPROM.write(tenant_addr, ssid[i]);
//         tenant_addr += 1;
//     }
//     EEPROM.commit();

// 	return "Done Writing";
// }


// String e2promReadTest() {

//     // reading byte-by-byte from EEPROM
//     for (int i = 0; i < EEPROM_SIZE; i++) {
//         byte readValue = EEPROM.read(i);

//         if (readValue == 0) {
//             break;
//         }

//         char readValueChar = char(readValue);
//         Serial.println(readValueChar);
//     }
// 	return "111as";
// }




