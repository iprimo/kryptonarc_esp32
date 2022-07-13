#include <Arduino.h>
#include "esp_system.h"

String getMacAddress() {

    // SoftAP MAC address
    uint8_t baseMacSOFTAP[6];
	esp_read_mac(baseMacSOFTAP, ESP_MAC_WIFI_SOFTAP);
	char baseMacChrSOFTAP[18] = {0};
	sprintf(baseMacChrSOFTAP, "%02X:%02X:%02X:%02X:%02X:%02X", baseMacSOFTAP[0], baseMacSOFTAP[1], baseMacSOFTAP[2], baseMacSOFTAP[3], baseMacSOFTAP[4], baseMacSOFTAP[5]);

    // Bluetooth MAC address
	uint8_t baseMacBT[6];
	esp_read_mac(baseMacBT, ESP_MAC_BT);
	char baseMacChrBT[18] = {0};
	sprintf(baseMacChrBT, "%02X:%02X:%02X:%02X:%02X:%02X", baseMacBT[0], baseMacBT[1], baseMacBT[2], baseMacBT[3], baseMacBT[4], baseMacBT[5]);

    // ETH MAC address
	uint8_t baseMacETH[6];
	esp_read_mac(baseMacETH, ESP_MAC_ETH);
	char baseMacChrETH[18] = {0};
	sprintf(baseMacChrETH, "%02X:%02X:%02X:%02X:%02X:%02X", baseMacETH[0], baseMacETH[1], baseMacETH[2], baseMacETH[3], baseMacETH[4], baseMacETH[5]);

    //  Wifi MAC address
	uint8_t baseMacWiFi[6];
	esp_read_mac(baseMacWiFi, ESP_MAC_WIFI_STA);
	char baseMacChrWiFi[18] = {0};
	sprintf(baseMacChrWiFi, "%02X:%02X:%02X:%02X:%02X:%02X", baseMacWiFi[0], baseMacWiFi[1], baseMacWiFi[2], baseMacWiFi[3], baseMacWiFi[4], baseMacWiFi[5]);
	return  "__WiFi_"  +  String(baseMacChrWiFi) + "__SOFTAP_"  +  String(baseMacChrSOFTAP)  + "__BT_"  +  String(baseMacChrBT) + "__ETH_"  +  String(baseMacChrETH) ;
}

long addx(int a, int b) {
    return a + b;
}
