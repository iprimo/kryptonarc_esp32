#include "HardwareSerial.h"
#include "BLEDevice.h"
#include "BLEServer.h"
#include "BLEUtils.h"

#include "iostream"    // std::cout
#include "algorithm"    // std::min
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "ESP32Servo.h"
#include "modules/servo.hpp"

#include "modules/string_works.hpp"
#include "modules/hardware_info_works.hpp"
#include "modules/system_structs.hpp"
#include "modules/e2prom_works.hpp"
#include "modules/bluetooth_works.hpp"
#include "modules/base64_char_masking.hpp"
#include "modules/timer_works.hpp"
#include "modules/led_works.hpp"
#include "modules/wifi_works.hpp"
#include "modules/ntp_works.hpp"

#include "base64.h"
#include "mbedtls/base64.h"

SOFTWARE_GLOBAL_PARAMETERS_VAR software_parameters_variables;
SOFTWARE_GLOBAL_PARAMETERS_FIXED software_parameters_fixed;
DEVICE_GLOBAL_HARDWARE_PARAMETERS_FIXED constrcut_mcu_id_fixed;
E2PROM_STORED_DATA_FIXED e2prom_variables;
BROADCAST_GLOBAL_VAR broadcast_global_variables;

using namespace std;

Servo ServoOutputA;

BLEServer *pServer;
BLECharacteristic *pCharacteristic;
BLEUUID mUUID;
BLEAdvertising *pAdvertising;
BLEService *pService ;

bool bleDeviceConnected = false;
bool oldBLEDeviceConnected = false;


#include <WiFi.h>


void setup() {
  Serial.begin(115200);
  servo_initialization();
  e2prom_initialization();
  bluetooth_initialization();
  led_initialization();
  wifi_initialization();
}


void loop() {
  led_action_startup();
  unsigned long device_preivous_time = millis();
  unsigned long device_now_time = device_preivous_time;
  int seconds_counter = 0;
  int variableCounter = 0;
  ////////////////////////////////////////////////////////////////////////
  // Hardware works
  constrcut_mcu_id_fixed = getMacAddress() ;

  ////////////////////////////////////////////////////////////////////////
  // E2PROM works
    e2prom_variables = e2promReadAllWorks();

    // Validate UUID and integer fields
    bool valid_uuid = isUUIDValid(e2prom_variables.hardware_uuid);
    int storage_version_int = atoi(e2prom_variables.storage_version);
    int storage_config_version_int = atoi(e2prom_variables.storage_config_version);

    
  Serial.print(">>>  storage_version_int  :    ");
  Serial.print( storage_version_int );
    
  Serial.print(">>>  storage_config_version_int  :    ");
  Serial.print( storage_config_version_int );

    bool valid_storage_version = (storage_version_int > 0);
    bool valid_storage_config_version = (storage_config_version_int > 0);

    if (!valid_uuid || !valid_storage_version || !valid_storage_config_version) {
        wipeAllAndReissueAllBasics();
          Serial.print(">>>  wipe E2PROM and restarting everything  :    ");

    }
  Serial.println();
  Serial.print(">>>  e2prom_variables.hardware_uuid  :    ");
  Serial.print( e2prom_variables.hardware_uuid );
  Serial.println();
  Serial.print(">>>  e2prom_variables.device_xc  :    ");
  Serial.print( e2prom_variables.device_xc );
  Serial.println();
  Serial.print(">>>  e2prom_variables.tenant_xc  :    ");
  Serial.print( e2prom_variables.tenant_xc );

  while ( true ){
    timer_global_action();
    led_global_action();

    if ( strlen( e2prom_variables.device_xc ) > 10 && strlen( e2prom_variables.tenant_xc ) > 10 ){ 
        // device configured 
        // Serial.println();
        // Serial.print(">>>  device configured     ");

        if ( seconds_counter > 3.5*60 ){ // reboot after 3.5 mins if no connection WiFi or Bluetooth
            Serial.println(">>>Software controlled device restart - Device configured");
            ESP.restart();

        } else if ( seconds_counter > 3*60 ){ // Attempt to connect to Last Resort
            Serial.println(">>>Last Resort Process In Progress - Device configured");
            flashing_led_red( "on" , "normal_flashing" , true );
            find_wifi_last_resort_key_and_take_action();
            delay(5000);

        } else if ( seconds_counter >= 2* 60 ) { // Attempt to connect to WiFi
            // Serial.println(">>>WiFi Process In Progress - Device configured");
            if ( software_parameters_variables.wifi_device_connected ){ 
                seconds_counter = 2.5*60; // Stay here if wifi connected
                wifi_health_check();
            } else { 
                disable_bluetooth();
                ntp_initialization(); 
                wifi_connect(); // connect to HW_Direct - Tenenat exists: HW_Direct
                ntp_process(); // device connected at this time
            } 

        } else if ( seconds_counter >= 0* 60 ) {  // Attempt to connect to BLE - Blue LED
            // Serial.println(">>>Bluetooth Process In Progress - Device configured");
            if ( bleDeviceConnected ){ seconds_counter = 0; } // Stay here if BLE connected - Timer
            BluetoothMainProcess() ;
        }
        
    } else { 
        // Device not configured    
        if ( seconds_counter > 3.5*60 ){ // reboot after 3.5 mins 
            Serial.println(">>> Device Blank - Software controlled device restart");
            ESP.restart();

        } else if ( seconds_counter >= 2* 60 ) {
            // firmware update
             flashing_led_red( "on" , "very_fast_flashing" , true );

        }else if ( seconds_counter >= 0* 60 ) {  // Attempt to connect to BLE
            // Serial.println(">>> Device Blank - BLE Process In Progress");
            flashing_led_blue( "on" , "normal_flashing" , true );
            if ( bleDeviceConnected ){ seconds_counter = 0; } // Stay here if BLE connected - Timer
            BluetoothMainProcess() ;
        }
    }

    device_now_time = millis();
    if ( device_now_time - device_preivous_time > 999 ){
      device_preivous_time = device_now_time;
      seconds_counter++ ;
    }
  }
}