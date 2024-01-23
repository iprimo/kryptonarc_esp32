#include "Arduino.h"
#include "WiFi.h"
#include "modules/system_structs.hpp"
#include "modules/string_works.hpp"

const char *targetSsid = "KryptonArc2G";
const char *targetPassword = "PleaseHelpMe";


const char* ENC_TYPE[] = {
    "Open",
    "WEP",
    "WPA_PSK",
    "WPA2_PSK",
    "WPA_WPA2_PSK",
    "WPA2_ENTERPRISE",
    "MAX"
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void wifiDisconnectFromAP() {
        
        // WiFi disconnect from an AP if it was previously connected
        WiFi.disconnect();
        Serial.println(" WiFi Module: Disconnected From All APs");
    }


// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// void wifiScanNetworks_ConsolePrint() {
//         Serial.println(" WiFi Module: scan start");

//         // WiFi.scanNetworks will return the number of networks found
//         int n = WiFi.scanNetworks();
//         Serial.println(" WiFi Module: scan done");
//         if (n == 0) {
//             Serial.println(" WiFi Module: no networks found");
//         } else {
//             Serial.print(n);
//             Serial.println(" WiFi Module:  networks found");
//             for (int i = 0; i < n; ++i) {
//             // Print SSID and RSSI for each network found
//             Serial.print(i + 1);
//             Serial.print(": ");
//             Serial.print(WiFi.SSID(i));
//             Serial.print(" (");
//             Serial.print(WiFi.RSSI(i));
//             Serial.print(")");
//             Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
//             delay(10);
//             }
//         }
//         Serial.println(" WiFi Module: End of scalling");

//     }


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void findWiFi_exactMatch(const char *ssid, WiFiInfo *info) {
    info->found = false;
    int16_t n = WiFi.scanNetworks();
    for (uint8_t i=0; i<n; ++i) {
        if (strcmp(WiFi.SSID(i).c_str(), ssid) == 0) {
            info->found = true;
            info->channel = WiFi.channel(i);
            info->rssi = WiFi.RSSI(i);
            info->auth_mode = WiFi.encryptionType(i);
            return;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void find_wifi_last_resort_key_and_take_action() {
    WiFiInfo in_fo;
    in_fo.found = false;
    int16_t n = WiFi.scanNetworks();
    for (uint8_t i=0; i<n; ++i) {
        Serial.println();
        Serial.println(" Found SSID ");
        Serial.print(WiFi.SSID(i).c_str());

        if ( findSubstring(WiFi.SSID(i).c_str(), e2prom_variables.lastResortKeyOffline_Internal) ) {
            strcpy( in_fo.ssid, WiFi.SSID(i).c_str() );
            in_fo.found = true;
            in_fo.channel = WiFi.channel(i);
            in_fo.rssi = WiFi.RSSI(i);
            in_fo.auth_mode = WiFi.encryptionType(i);
            // return;
        }
    }
    Serial.println();
    Serial.printf(in_fo.found
                ? "Task: %s, SSID: %s, channel: %i, RSSI: %i dBm, encryption: %s\n"
                : "Task: %s, SSID could not be found\n",
            "lastResortKeyOffline - detection: ",
            in_fo.ssid,
            in_fo.channel,
            in_fo.rssi,
            ENC_TYPE[ in_fo.auth_mode ] );
    
    if ( in_fo.found ) {
        char char2[20]; 

        removeSubstring( in_fo.ssid, e2prom_variables.lastResortKeyOffline_Internal , char2);

        Serial.println();
        Serial.println("    char2>>> ");
        Serial.println(char2);
        Serial.println();

        write_shackle_lock_status(char2);
    }
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void wifi_initialization() {
  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
}