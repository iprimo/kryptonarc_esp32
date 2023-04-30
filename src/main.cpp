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

// int RECIEVE_ARRAY_SIZE=1000 ;
// int TRANSFER_ARRAY_SIZE=1000;
// char* rx_DataAssembled = new char[RECIEVE_ARRAY_SIZE](); // () initializes all elements to null
// char* txCValue = new char[ TRANSFER_ARRAY_SIZE ](); // () initializes all elements to null



bool deviceConnected = false;
bool oldDeviceConnected = false;

void setup() {
  Serial.begin(115200);

  ////////////////////////////////////////////////////////////////////////
  // Servo works
  servoInitiate();
  
  ////////////////////////////////////////////////////////////////////////
  // Hardware works
  constrcut_MCU_ID_fixed = getMacAddress() ;

  // Serial.println(">>1> constrcut_MCU_ID_fixed >>constrcut_MCU_ID_fixed>    ") ; 
  // Serial.println(constrcut_MCU_ID_fixed.cChipModel           );
	// Serial.println(constrcut_MCU_ID_fixed.cChipRevision        );
	// Serial.println(constrcut_MCU_ID_fixed.cChipCores           );
	// Serial.println(constrcut_MCU_ID_fixed.cChipId              );
	// Serial.println(constrcut_MCU_ID_fixed.baseMacChrSOFTAP     );
	// Serial.println(constrcut_MCU_ID_fixed.baseMacChrBT         );
	// Serial.println(constrcut_MCU_ID_fixed.baseMacChrETH        );
	// Serial.println(constrcut_MCU_ID_fixed.baseMacChrWiFi       );


  ////////////////////////////////////////////////////////////////////////
  // E2PROM works
  e2promInitiate();

  e2prom_variables = e2promReadAllWorks();

  if ( strlen( e2prom_variables.hardware_uuid ) == 0 || strlen( e2prom_variables.board_model ) == 0) {
    wipeAllAndReissueAllBasics();
  }

  // Serial.print(">>1> x2  second ") ; Serial.println(e2prom_variables.hardware_uuid );     Serial.print(">>1> length >>>    ") ;  Serial.println(  strlen( e2prom_variables.hardware_uuid ));
  // Serial.print(">>0> x2  second ") ; Serial.println(e2prom_variables.board_model );     Serial.print(">>0> length >>>    ") ;  Serial.println(  strlen( e2prom_variables.board_model ));
  // Serial.print(">>2> x2  second ") ; Serial.println(e2prom_variables.vender_xc );     Serial.print(">>2> length >>>    ") ;  Serial.println(  strlen( e2prom_variables.vender_xc ));
  // Serial.print(">>3> x2  second ") ; Serial.println(e2prom_variables.device_xc );     Serial.print(">>3> length >>>    ") ;  Serial.println(  strlen( e2prom_variables.device_xc ));
  // Serial.print(">>4> x2  second ") ; Serial.println(e2prom_variables.tenant_xc );     Serial.print(">>4> length >>>    ") ;  Serial.println(  strlen( e2prom_variables.tenant_xc ));
  // Serial.print(">>5> x2  second ") ; Serial.println(e2prom_variables.secure_code_01  );     Serial.print(">>5> length >>>    ") ;  Serial.println(  strlen( e2prom_variables.secure_code_01  ));
  // Serial.print(">>6> x2  second ") ; Serial.println(e2prom_variables.secure_code_02  );     Serial.print(">>6> length >>>    ") ;  Serial.println(  strlen( e2prom_variables.secure_code_02  ));
  // Serial.print(">>7> x2  second ") ; Serial.println(e2prom_variables.secure_code_03  );     Serial.print(">>7> length >>>    ") ;  Serial.println(  strlen( e2prom_variables.secure_code_03  ));


  BluetoothInitiate();

}


void loop() {

  while ( true ){
    BluetoothMainProcess() ;
  }
}