// // Source: https://randomnerdtutorials.com/esp32-useful-wi-fi-functions-arduino/
// // Source: https://randomnerdtutorials.com/esp32-useful-wi-fi-functions-arduino/

// #include <Arduino.h>
// #include <WiFi.h>

// const char* SPECIFIC_SSID = "KryptonArc2G";
// const char* ENC_TYPE[] = {
//     "Open",
//     "WEP",
//     "WPA_PSK",
//     "WPA2_PSK",
//     "WPA_WPA2_PSK",
//     "WPA2_ENTERPRISE",
//     "MAX"
// };

// struct WiFiInfo {
// bool found;
// int32_t channel;
// int32_t rssi;
// wifi_auth_mode_t auth_mode;
// } wifi_info;

// void findWiFi(const char *ssid, WiFiInfo *info) {
// info->found = false;
// int16_t n = WiFi.scanNetworks();
// for (uint8_t i=0; i<n; ++i) {
// if (strcmp(WiFi.SSID(i).c_str(), ssid) == 0) {
// info->found = true;
// info->channel = WiFi.channel(i);
// info->rssi = WiFi.RSSI(i);
// info->auth_mode = WiFi.encryptionType(i);
// return;
// }
// }
// }

// void setup() {
//         Serial.begin(115200);
// }

// void loop() {
//         findWiFi(SPECIFIC_SSID, &wifi_info);
//         Serial.printf(wifi_info.found
//                     ? "SSID: %s, channel: %i, RSSI: %i dBm, encryption: %s\n"
//                     : "SSID: %s ... could not be found\n",
//                 SPECIFIC_SSID,
//                 wifi_info.channel,
//                 wifi_info.rssi,
//                 ENC_TYPE[wifi_info.auth_mode]
//             );

//         delay(1000);

// }
