#include "MD5Builder.h"

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

SOFTWARE_GLOBAL_PARAMETERS_FIXED software_parameters_fixed;
DEVICE_GLOBAL_HARDWARE_PARAMETERS_FIXED constrcut_MCU_ID_fixed;
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

void setup() {
  Serial.begin(115200);

  ////////////////////////////////////////////////////////////////////////
  // Servo Initiate
  servoInitiate();
  
  ////////////////////////////////////////////////////////////////////////
  // E2PROM Initiate
  e2promInitiate();

  ////////////////////////////////////////////////////////////////////////
  // BLE Initiate
  BluetoothInitiate();

}


void loop() {
  int variableCounter = 0;
  ////////////////////////////////////////////////////////////////////////
  // Hardware works
  constrcut_MCU_ID_fixed = getMacAddress() ;

  ////////////////////////////////////////////////////////////////////////
  // E2PROM works
  e2prom_variables = e2promReadAllWorks();

  if ( strlen( e2prom_variables.hardware_uuid ) == 0 || strlen( e2prom_variables.board_model ) == 0) {
    wipeAllAndReissueAllBasics();
  }
  
  while ( true ){

    if ( !bleDeviceConnected && variableCounter > 12000) { // 120 Seconds = 120,000.00 milli-seconds => 120,000.00 / 10 (delay) = 3,000
      // Reseting device if the counter meets the condition
      Serial.println("Restarting device");
      ESP.restart();

    } else if ( bleDeviceConnected && !(variableCounter == 0)){
      // When device connected reset the counter
      variableCounter = 0 ;

    } else if ( !bleDeviceConnected ){
      // Nothing connected - reset counter
      delay(10);
      variableCounter = variableCounter + 1 ;

    } 
    BluetoothMainProcess() ;
  }
}