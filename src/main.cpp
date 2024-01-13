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
#include "modules/encryption_works.hpp"
#include "modules/base64_char_masking.hpp"

#include "base64.h"
#include "mbedtls/base64.h"

SOFTWARE_GLOBAL_PARAMETERS_VAR software_parameters_variables;
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

  ////////////////////////////////////////////////////////////////////////

  char clearMessage[1024];
  char encryptionKey[17] = "1234567890123456";
  char encryptedData[1024];
  char receivedMessage[1024];


  ////////////////////////////////////////////////////////////////////////
  
}


void loop() {
  int variableCounter = 0;
  ////////////////////////////////////////////////////////////////////////
  // Hardware works
  constrcut_MCU_ID_fixed = getMacAddress() ;

  ////////////////////////////////////////////////////////////////////////
  // E2PROM works
  e2prom_variables = e2promReadAllWorks();

  // if ( strlen( e2prom_variables.hardware_uuid ) == 0 || strlen( e2prom_variables.board_model ) == 0 || !isUUIDValid( e2prom_variables.hardware_uuid )) {
  if ( !isUUIDValid( e2prom_variables.hardware_uuid )) {
    wipeAllAndReissueAllBasics();
  }

  // ////////////////////////////////////////////////////////////////////////
  // //
  // Serial.print("e2prom_variables.hardware_uuid  >>> " ) ; Serial.println( e2prom_variables.hardware_uuid );
  // Serial.print("e2prom_variables.board_model  >>> " ) ; Serial.println( e2prom_variables.board_model );
  // Serial.print("e2prom_variables.vender_xc  >>> " ) ; Serial.println( e2prom_variables.vender_xc );
  // Serial.print("e2prom_variables.device_xc  >>> " ) ; Serial.println( e2prom_variables.device_xc );
  // Serial.print("e2prom_variables.tenant_xc  >>> " ) ; Serial.println( e2prom_variables.tenant_xc );
  // Serial.print("constrcut_MCU_ID_fixed.cChipModel >>> " ) ; Serial.println(  constrcut_MCU_ID_fixed.cChipModel );
  // Serial.print("constrcut_MCU_ID_fixed.cChipRevision  >>> " ) ; Serial.println( constrcut_MCU_ID_fixed.cChipRevision );
  // Serial.print("constrcut_MCU_ID_fixed.cChipCores >>> " ) ; Serial.println(  constrcut_MCU_ID_fixed.cChipCores );
  // Serial.print("constrcut_MCU_ID_fixed.cChipId  >>> " ) ; Serial.println( constrcut_MCU_ID_fixed.cChipId );
  // Serial.print("constrcut_MCU_ID_fixed.baseMacChrSOFTAP >>> " ) ; Serial.println(  constrcut_MCU_ID_fixed.baseMacChrSOFTAP );
  // Serial.print("constrcut_MCU_ID_fixed.baseMacChrBT >>> " ) ; Serial.println(  constrcut_MCU_ID_fixed.baseMacChrBT );
  // Serial.print("constrcut_MCU_ID_fixed.baseMacChrETH  >>> " ) ; Serial.println( constrcut_MCU_ID_fixed.baseMacChrETH );
  // Serial.print("constrcut_MCU_ID_fixed.baseMacChrWiFi >>> " ) ; Serial.println(  constrcut_MCU_ID_fixed.baseMacChrWiFi );

  
  while ( true ){

    if ( !bleDeviceConnected && variableCounter > 12000) { // 120 Seconds = 120,000.00 milli-seconds => 120,000.00 / 10 (delay) = 3,000
      // Reseting device if the counter meets the condition
      Serial.println("Software controlled device restart");
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