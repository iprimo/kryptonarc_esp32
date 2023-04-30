#include <Arduino.h>
#include "esp_system.h"
#include <cstring>
#include <iostream>
#include <string>
#include "system_structs.hpp"

#define Max_Digits 10

// MAC Addresses 
DEVICE_GLOBAL_HARDWARE_PARAMETERS_FIXED getMacAddress() {
	DEVICE_GLOBAL_HARDWARE_PARAMETERS_FIXED HardwareID;
	uint32_t chipId = 0;
	for(int i=0; i<17; i=i+8) {
	  chipId |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
	}

	// Chip Model
	sprintf(HardwareID.cChipModel , "%s", ESP.getChipModel());

	////////////////////////////////////////////////////////////////////////////////
	// Chip Revision
	char strChipRevision[Max_Digits + sizeof(char)];
	sprintf(HardwareID.cChipRevision , "%d", ESP.getChipRevision());
	////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////
	// Chip Cores
	char strChipCores[Max_Digits + sizeof(char)];
	sprintf(HardwareID.cChipCores , "%d", ESP.getChipCores());
	////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////
	// Chip ID
	char strChipID[Max_Digits + sizeof(char)];
	sprintf(HardwareID.cChipId , "%d", chipId );
	////////////////////////////////////////////////////////////////////////////////
	
	////////////////////////////////////////////////////////////////////////////////
    // SoftAP MAC address
    uint8_t baseMacSOFTAP[6];
	esp_read_mac(baseMacSOFTAP, ESP_MAC_WIFI_SOFTAP);
	sprintf(HardwareID.baseMacChrSOFTAP, "%02X:%02X:%02X:%02X:%02X:%02X", baseMacSOFTAP[0], baseMacSOFTAP[1], baseMacSOFTAP[2], baseMacSOFTAP[3], baseMacSOFTAP[4], baseMacSOFTAP[5]);
	////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////
    // Bluetooth MAC address
	uint8_t baseMacBT[6];
	esp_read_mac(baseMacBT, ESP_MAC_BT);
	sprintf(HardwareID.baseMacChrBT, "%02X:%02X:%02X:%02X:%02X:%02X", baseMacBT[0], baseMacBT[1], baseMacBT[2], baseMacBT[3], baseMacBT[4], baseMacBT[5]);
	////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////
    // ETH MAC address
	uint8_t baseMacETH[6];
	esp_read_mac(baseMacETH, ESP_MAC_ETH);
	sprintf(HardwareID.baseMacChrETH, "%02X:%02X:%02X:%02X:%02X:%02X", baseMacETH[0], baseMacETH[1], baseMacETH[2], baseMacETH[3], baseMacETH[4], baseMacETH[5]);
	////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////	
    //  Wifi MAC address
	uint8_t baseMacWiFi[6];
	esp_read_mac(baseMacWiFi, ESP_MAC_WIFI_STA);
	sprintf(HardwareID.baseMacChrWiFi, "%02X:%02X:%02X:%02X:%02X:%02X", baseMacWiFi[0], baseMacWiFi[1], baseMacWiFi[2], baseMacWiFi[3], baseMacWiFi[4], baseMacWiFi[5]);
	////////////////////////////////////////////////////////////////////////////////

	return HardwareID ;
}

