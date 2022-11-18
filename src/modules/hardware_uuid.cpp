#include <Arduino.h>
#include "esp_system.h"
#include "system_structs.cpp"

DEVICE_HARDWARE_INFO HardwareID;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// MAC Addresses 
DEVICE_HARDWARE_INFO getMacAddress() {
	uint32_t chipId = 0;
	for(int i=0; i<17; i=i+8) {
	  chipId |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
	}
	// Serial.printf("ESP32 Chip model = %s Rev %d\n", ESP.getChipModel(), ESP.getChipRevision());
	// Serial.printf("This chip has %d cores\n", ESP.getChipCores());
  	// Serial.print("Chip ID: "); Serial.println(chipId);
	
	HardwareID.sChipModel = ESP.getChipModel();
	HardwareID.iChipRevision = ESP.getChipRevision();
	HardwareID.iChipCores = ESP.getChipCores();
	HardwareID.uChipId = chipId;

    // SoftAP MAC address
    uint8_t baseMacSOFTAP[6];
	esp_read_mac(baseMacSOFTAP, ESP_MAC_WIFI_SOFTAP);
	char baseMacChrSOFTAP[18] = {0};
	// sprintf(baseMacChrSOFTAP, "%02X:%02X:%02X:%02X:%02X:%02X", baseMacSOFTAP[0], baseMacSOFTAP[1], baseMacSOFTAP[2], baseMacSOFTAP[3], baseMacSOFTAP[4], baseMacSOFTAP[5]);
	sprintf(HardwareID.baseMacChrSOFTAP, "%02X:%02X:%02X:%02X:%02X:%02X", baseMacSOFTAP[0], baseMacSOFTAP[1], baseMacSOFTAP[2], baseMacSOFTAP[3], baseMacSOFTAP[4], baseMacSOFTAP[5]);

    // Bluetooth MAC address
	uint8_t baseMacBT[6];
	esp_read_mac(baseMacBT, ESP_MAC_BT);
	char baseMacChrBT[18] = {0};
	// sprintf(baseMacChrBT, "%02X:%02X:%02X:%02X:%02X:%02X", baseMacBT[0], baseMacBT[1], baseMacBT[2], baseMacBT[3], baseMacBT[4], baseMacBT[5]);
	sprintf(HardwareID.baseMacChrBT, "%02X:%02X:%02X:%02X:%02X:%02X", baseMacBT[0], baseMacBT[1], baseMacBT[2], baseMacBT[3], baseMacBT[4], baseMacBT[5]);

    // ETH MAC address
	uint8_t baseMacETH[6];
	esp_read_mac(baseMacETH, ESP_MAC_ETH);
	char baseMacChrETH[18] = {0};
	// sprintf(baseMacChrETH, "%02X:%02X:%02X:%02X:%02X:%02X", baseMacETH[0], baseMacETH[1], baseMacETH[2], baseMacETH[3], baseMacETH[4], baseMacETH[5]);
	sprintf(HardwareID.baseMacChrETH, "%02X:%02X:%02X:%02X:%02X:%02X", baseMacETH[0], baseMacETH[1], baseMacETH[2], baseMacETH[3], baseMacETH[4], baseMacETH[5]);

    //  Wifi MAC address
	uint8_t baseMacWiFi[6];
	esp_read_mac(baseMacWiFi, ESP_MAC_WIFI_STA);
	char baseMacChrWiFi[18] = {0};
	// sprintf(baseMacChrWiFi, "%02X:%02X:%02X:%02X:%02X:%02X", baseMacWiFi[0], baseMacWiFi[1], baseMacWiFi[2], baseMacWiFi[3], baseMacWiFi[4], baseMacWiFi[5]);
	sprintf(HardwareID.baseMacChrWiFi, "%02X:%02X:%02X:%02X:%02X:%02X", baseMacWiFi[0], baseMacWiFi[1], baseMacWiFi[2], baseMacWiFi[3], baseMacWiFi[4], baseMacWiFi[5]);
	

	// HardwareID.cChipModel = "";
	// HardwareID.sChipModel = "";
	// HardwareID.iChipRevision = 0;
	// HardwareID.iChipCores = 0;
	// HardwareID.chipId = 0;
	// HardwareID.baseMacChrSOFTAP = baseMacChrWiFi;
	// HardwareID.baseMacChrBT = baseMacChrWiFi;
	// HardwareID.baseMacChrETH = baseMacChrWiFi;
	// HardwareID.baseMacChrWiFi = baseMacChrWiFi;

	// return  "__WiFi_"  +  String(baseMacChrWiFi) + "__SOFTAP_"  +  String(baseMacChrSOFTAP)  + "__BT_"  +  String(baseMacChrBT) + "__ETH_"  +  String(baseMacChrETH) ;
	// return  "___+_+_" ;
	return HardwareID ;
}








// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////





// #include <Arduino.h>
// #include "esp_system.h"

// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// // Chip ID
// // Source: https://github.com/espressif/arduino-esp32/blob/master/libraries/ESP32/examples/ChipID/GetChipID/GetChipID.ino
// // Source: https://github.com/espressif/arduino-esp32/blob/master/libraries/ESP32/examples/ChipID/GetChipID/GetChipID.ino
// // 	Example of Output
// 			// ESP32 Chip model = ESP32-D0WDQ6 Rev 1
// 			// This chip has 2 cores
// 			// Chip ID: 7743348
// 			// ESP32 Chip model = ESP32-D0WDQ6 Rev 1
// 			// This chip has 2 cores
// 			// Chip ID: 7743348


// // uint32_t chipId = 0;

// // void setup() {
// // 	Serial.begin(115200);
// // }

// // void loop() {
// // 	for(int i=0; i<17; i=i+8) {
// // 	  chipId |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
// // 	}

// // 	Serial.printf("ESP32 Chip model = %s Rev %d\n", ESP.getChipModel(), ESP.getChipRevision());
// // 	Serial.printf("This chip has %d cores\n", ESP.getChipCores());
// //   Serial.print("Chip ID: "); Serial.println(chipId);
  
// // 	delay(3000);

// // }
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// // MAC Addresses 
// String getMacAddress() {
	
//     // SoftAP MAC address
//     uint8_t baseMacSOFTAP[6];
// 	esp_read_mac(baseMacSOFTAP, ESP_MAC_WIFI_SOFTAP);
// 	char baseMacChrSOFTAP[18] = {0};
// 	sprintf(baseMacChrSOFTAP, "%02X:%02X:%02X:%02X:%02X:%02X", baseMacSOFTAP[0], baseMacSOFTAP[1], baseMacSOFTAP[2], baseMacSOFTAP[3], baseMacSOFTAP[4], baseMacSOFTAP[5]);

//     // Bluetooth MAC address
// 	uint8_t baseMacBT[6];
// 	esp_read_mac(baseMacBT, ESP_MAC_BT);
// 	char baseMacChrBT[18] = {0};
// 	sprintf(baseMacChrBT, "%02X:%02X:%02X:%02X:%02X:%02X", baseMacBT[0], baseMacBT[1], baseMacBT[2], baseMacBT[3], baseMacBT[4], baseMacBT[5]);

//     // ETH MAC address
// 	uint8_t baseMacETH[6];
// 	esp_read_mac(baseMacETH, ESP_MAC_ETH);
// 	char baseMacChrETH[18] = {0};
// 	sprintf(baseMacChrETH, "%02X:%02X:%02X:%02X:%02X:%02X", baseMacETH[0], baseMacETH[1], baseMacETH[2], baseMacETH[3], baseMacETH[4], baseMacETH[5]);

//     //  Wifi MAC address
// 	uint8_t baseMacWiFi[6];
// 	esp_read_mac(baseMacWiFi, ESP_MAC_WIFI_STA);
// 	char baseMacChrWiFi[18] = {0};
// 	sprintf(baseMacChrWiFi, "%02X:%02X:%02X:%02X:%02X:%02X", baseMacWiFi[0], baseMacWiFi[1], baseMacWiFi[2], baseMacWiFi[3], baseMacWiFi[4], baseMacWiFi[5]);
// 	return  "__WiFi_"  +  String(baseMacChrWiFi) + "__SOFTAP_"  +  String(baseMacChrSOFTAP)  + "__BT_"  +  String(baseMacChrBT) + "__ETH_"  +  String(baseMacChrETH) ;
// }
