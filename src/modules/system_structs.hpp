
#ifndef GLOBAL_VAR_DEFINITIONS_HPP
#define GLOBAL_VAR_DEFINITIONS_HPP
// https://stackoverflow.com/questions/6882637/using-struct-in-different-cpp-file
// https://stackoverflow.com/questions/6882637/using-struct-in-different-cpp-file
// 
#include "cstddef"
#include <string>
#include "WiFi.h"

using namespace std;

struct PassingDataStruct
{

    int iValue;
    long lValue;
    bool bOperationLogic = false;
    
    // To print sEMessage use "Serial.println(str.c_str());"
    // Source: https://techoverflow.net/2022/09/07/how-to-serial-println-a-stdstring/
    std::string sEMessage;

    const char *cMessage;


    // int x;
    // long age;
    // bool return_logic;
    // // char *last_name;
    // std::string last_name;

    // BLERemoteCharacteristic* pBLERemoteCharacteristic, 
    // uint8_t* pData,
    // size_t length,

    // uint8_t mac[6];
    // void f1() { /* Implementation here. */ }
    // void f2(); /* Implemented in PassingDataStruct.cpp */
};

struct HTTPWorksReply
{
    bool bEServerReachableLogic = false;
    bool bEServerRespondedLogic = false;
    bool bEDeviceRegisteredLogic = false;
    std::string sEReturnedData;
    // To print sEMessage use "Serial.println(str.c_str());"
    // Source: https://techoverflow.net/2022/09/07/how-to-serial-println-a-stdstring/
    std::string sEMessage;
    const char *cMessage;

};

struct BROADCAST_GLOBAL_VAR
{
    char* broadcastOutputA = NULL;
    const char* broadcastOutputA_SubStringStart = "-BOAV_";
    const char* broadcastOutputA_SubStringEnd = "_BOAV-";

    // char baseMacChrBT[18] = {0};
    
    // char* valueB = NULL;
    // const char* valueB_SubStringStart = "-BO1AV_";
    // const char* valueB_SubStringEnd = "_BO1AV-";
};

struct SOFTWARE_GLOBAL_PARAMETERS_VAR
{
    bool wifi_device_connected = false;
    int data_transfer_sequence_ble = 5749;
    char incoming_data_time_stamp[64] ;
    unsigned long global_current_millis = 0 ;

    const int global_very_fast_flashing_on_delay = 50 ;
    const int global_very_fast_flashing_off_delay = 100 ;
    
    const int global_fast_flashing_on_delay = 125 ;
    const int global_fast_flashing_off_delay = 250 ;
    
    const int global_normal_flashing_on_delay = 250 ;
    const int global_normal_flashing_off_delay = 500 ;
    
    const int global_slow_flashing_on_delay = 750 ;
    const int global_slow_flashing_off_delay = 1500 ;

    const int global_very_slow_flashing_on_delay = 2000 ;
    const int global_very_slow_flashing_off_delay = 3000 ;
    
    const int global_fix_flashing_on_delay = 1000 ;
    const int global_fix_flashing_off_delay = 0 ;
    
    unsigned long global_green_flashing_previous_millis_timer = 0 ;
    bool global_green_flashing_temp_var = false ;
    bool global_green_flashing_on = false ;
    int global_green_flashing_on_delay = 0 ;
    int global_green_flashing_off_delay = 0 ;
    int global_green_flashing_target_counter = -1 ;
    int global_green_flashing_current_counter = -1 ;
    bool global_green_leave_on_after_flashing = false ;

    unsigned long global_blue_flashing_previous_millis_timer = 0 ;
    bool global_blue_flashing_temp_var = false ;
    bool global_blue_flashing_on = false ;
    int global_blue_flashing_on_delay = 0 ;
    int global_blue_flashing_off_delay = 0 ;
    int global_blue_flashing_target_counter = -1 ;
    int global_blue_flashing_current_counter = -1 ;
    bool global_blue_leave_on_after_flashing = false ;
    
    unsigned long global_red_flashing_previous_millis_timer = 0 ;
    bool global_red_flashing_temp_var = false ;
    bool global_red_flashing_on = false ;
    int global_red_flashing_on_delay = 0 ;
    int global_red_flashing_off_delay = 0 ;
    int global_red_flashing_target_counter = -1 ;
    int global_red_flashing_current_counter = -1 ;
    bool global_red_leave_on_after_flashing = false ;

    unsigned long global_previous_millis_timer_02 = 0 ;
    unsigned long global_previous_millis_timer_03 = 0 ;
    unsigned long global_previous_millis_timer_04 = 0 ;
    unsigned long global_previous_millis_timer_05 = 0 ;
    unsigned long global_previous_millis_timer_06 = 0 ;
    unsigned long global_previous_millis_timer_07 = 0 ;
    unsigned long global_previous_millis_timer_08 = 0 ;
    unsigned long global_previous_millis_timer_09 = 0 ;
    unsigned long global_previous_millis_timer_10 = 0 ;


};

struct E2PROM_STORED_DATA_FIXED
{
    char hardware_uuid[64] ;
    char board_model[64] ;

    char manufacturer_xc[64] ;
    char vender_xc[64] ;
    
    char tenant_xc[64] ;
    char device_xc[64] ;


    char hashKey_Internal[64] ;
    char lastResortKeyOffline_Internal[64] ;
    char lastResortKeyOffline02_Internal[64] ;

    char keySmithKeyOnline_Internal[64] ;
    char encryptionKey_Internal[64] ;
    char keySmithKeyOnline02_Internal[64] ;

    char encryptionKey02_Internal[64] ;
    char hashKey02_Internal[64] ;
    char current_shackle_lock_configuration[64] ;
    // char tempName16[64] ;
    // char tempName17[64] ;
    // char tempName18[64] ;
    // char tempName19[64] ;
    // char tempName20[64] ;
    // char tempName21[64] ;
    // char tempName22[64] ;
    // char tempName23[64] ;
    // char tempName24[64] ;
    // char tempName25[64] ;
    // char tempName26[64] ;
    // char tempName27[64] ;
    // char tempName28[64] ;
    // char tempName29[64] ;
    // char tempName30[64] ;
    // char tempName31[64] ;
    // char tempName32[64] ;
    // char tempName33[64] ;
    // char tempName34[64] ;
    // char tempName35[64] ;
    // char tempName36[64] ;
    // char tempName37[64] ;
    // char tempName38[64] ;
    // char tempName39[64] ;
    // char tempName40[64] ;
    // char tempName41[64] ;
    // char tempName42[64] ;
    // char tempName43[64] ;
    // char tempName44[64] ;
    // char tempName45[64] ;
    // char tempName46[64] ;
    // char tempName47[64] ;
    // char tempName48[64] ;
    // char tempName49[64] ;
    // char tempName50[64] ;
    // char tempName51[64] ;
    // char tempName52[64] ;
    // char tempName53[64] ;
    // char tempName54[64] ;
    // char tempName55[64] ;
    // char tempName56[64] ;
    // char tempName57[64] ;
    // char tempName58[64] ;
    // char tempName59[64] ;
    // char tempName60[64] ;
    // char tempName61[64] ;
    // char tempName62[64] ;
    // char tempName63[64] ;
    // char tempName64[64] ;
    
};

struct SOFTWARE_GLOBAL_PARAMETERS_FIXED
{
    const bool serial_debug = true;
    const char* STANDARD_WIFI_SSID = "KryptonArc2G";
    const char* STANDARD_WIFI_PASSWORD = "PleaseHelpMe";

    const char* GLOBAL_SHARED_MASK_KEY = "vjhdi378DiO21oh"; // This is to 
    const char* GLOBAL_SHARED_HASH_KEY = "48cf29ea128baf2d";
    // const char* GLOBAL_HASH_SALT = "DFJynken3Deal87i9EfbNDK2mPBhthxt";
    const char* FIRMWARE_VERSION = "3.19";

    const char* PRODUCT_SERIES = "Marble Series";
    const char* PRODUCT_MODEL = "MX14";

    const int SHACKLE_UNLOCK_DEGREE = 30;
    const int SHACKLE_LOCK_DEGREE = 120;
    const int LED_PIN_BLUE = 5;
    const int LED_PIN_GREEN = 17;
    const int LED_PIN_RED = 16;

    const int SERVO_PIN = 18;
    const int BUZZER_PASSIVE = 19;

    const char *url = "https://fota.kryptonarc.com/firmware.bin"; //state url of your firmware image

    // this certificate exists on orignal code from Espressif , belongs to "ISRG Root X1" a wide well known CA on the web
    const char *fota_server_fota_certificate = R"(
-----BEGIN CERTIFICATE-----
MIIFYDCCBEigAwIBAgIQQAF3ITfU6UK47naqPGQKtzANBgkqhkiG9w0BAQsFADA/
MSQwIgYDVQQKExtEaWdpdGFsIFNpZ25hdHVyZSBUcnVzdCBDby4xFzAVBgNVBAMT
DkRTVCBSb290IENBIFgzMB4XDTIxMDEyMDE5MTQwM1oXDTI0MDkzMDE4MTQwM1ow
TzELMAkGA1UEBhMCVVMxKTAnBgNVBAoTIEludGVybmV0IFNlY3VyaXR5IFJlc2Vh
cmNoIEdyb3VwMRUwEwYDVQQDEwxJU1JHIFJvb3QgWDEwggIiMA0GCSqGSIb3DQEB
AQUAA4ICDwAwggIKAoICAQCt6CRz9BQ385ueK1coHIe+3LffOJCMbjzmV6B493XC
ov71am72AE8o295ohmxEk7axY/0UEmu/H9LqMZshftEzPLpI9d1537O4/xLxIZpL
wYqGcWlKZmZsj348cL+tKSIG8+TA5oCu4kuPt5l+lAOf00eXfJlII1PoOK5PCm+D
LtFJV4yAdLbaL9A4jXsDcCEbdfIwPPqPrt3aY6vrFk/CjhFLfs8L6P+1dy70sntK
4EwSJQxwjQMpoOFTJOwT2e4ZvxCzSow/iaNhUd6shweU9GNx7C7ib1uYgeGJXDR5
bHbvO5BieebbpJovJsXQEOEO3tkQjhb7t/eo98flAgeYjzYIlefiN5YNNnWe+w5y
sR2bvAP5SQXYgd0FtCrWQemsAXaVCg/Y39W9Eh81LygXbNKYwagJZHduRze6zqxZ
Xmidf3LWicUGQSk+WT7dJvUkyRGnWqNMQB9GoZm1pzpRboY7nn1ypxIFeFntPlF4
FQsDj43QLwWyPntKHEtzBRL8xurgUBN8Q5N0s8p0544fAQjQMNRbcTa0B7rBMDBc
SLeCO5imfWCKoqMpgsy6vYMEG6KDA0Gh1gXxG8K28Kh8hjtGqEgqiNx2mna/H2ql
PRmP6zjzZN7IKw0KKP/32+IVQtQi0Cdd4Xn+GOdwiK1O5tmLOsbdJ1Fu/7xk9TND
TwIDAQABo4IBRjCCAUIwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMCAQYw
SwYIKwYBBQUHAQEEPzA9MDsGCCsGAQUFBzAChi9odHRwOi8vYXBwcy5pZGVudHJ1
c3QuY29tL3Jvb3RzL2RzdHJvb3RjYXgzLnA3YzAfBgNVHSMEGDAWgBTEp7Gkeyxx
+tvhS5B1/8QVYIWJEDBUBgNVHSAETTBLMAgGBmeBDAECATA/BgsrBgEEAYLfEwEB
ATAwMC4GCCsGAQUFBwIBFiJodHRwOi8vY3BzLnJvb3QteDEubGV0c2VuY3J5cHQu
b3JnMDwGA1UdHwQ1MDMwMaAvoC2GK2h0dHA6Ly9jcmwuaWRlbnRydXN0LmNvbS9E
U1RST09UQ0FYM0NSTC5jcmwwHQYDVR0OBBYEFHm0WeZ7tuXkAXOACIjIGlj26Ztu
MA0GCSqGSIb3DQEBCwUAA4IBAQAKcwBslm7/DlLQrt2M51oGrS+o44+/yQoDFVDC
5WxCu2+b9LRPwkSICHXM6webFGJueN7sJ7o5XPWioW5WlHAQU7G75K/QosMrAdSW
9MUgNTP52GE24HGNtLi1qoJFlcDyqSMo59ahy2cI2qBDLKobkx/J3vWraV0T9VuG
WCLKTVXkcGdtwlfFRjlBz4pYg1htmf5X6DYO8A4jqv2Il9DjXA6USbW1FzXSLr9O
he8Y4IWS6wY7bCkjCWDcRQJMEhg76fsO3txE+FiYruq9RUWhiF1myv4Q6W+CyBFC
Dfvp7OOGAN6dEOM4+qR9sdjoSYKEBpsr6GtPAQw4dy753ec5
-----END CERTIFICATE-----
)";


    const char *cloud_comms_rsa_certificate_development = R"(
-----BEGIN PUBLIC KEY-----
MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAwVl+32cbc17TVxqe8QSA
52yUHyVuX88HzRhdxgBs63pmX8CbcE83UdMjqeZY0PF5KtBq4s6h18H9XmyAEOGY
NFava2S7UwOaIIHV2r4SUdx2STU+P+8ruwQX8tBWBRqv/AcJhUCKdbTjeh/997EX
cqsaTB7YJtQItH7ztpGjLLtTO/36wNcADqUHACqmJ+UsSB2M7x+GBhvjiWrQrxBl
o7ILLJfzZuNR/heCt0nBL+ys/Ecs61VLP0Z/YZVQKDmpXX92jxV+pEH8/pBh7PA8
wBOhvYyqrR0CSeHFbRIHSJ7PnXz60xKWH7FfVaRvBiWba0aG/Vo4nNbP4Tc3vA1w
LwIDAQAB
-----END PUBLIC KEY-----
)";





    const char *server_hardware_direct_ca_domain = "hw_direct.dev.kryptonarc.com";
    const char *server_hardware_direct_ca_path = "/raw_hw_check";
    const char *server_hardware_direct_ca_fingerprint = "F1 13 62 10 51 7B 3A F9 1C 96 D8 79 DE 39 2B C3 95 0A EA 57";
    const char *server_hardware_direct_ca_certificate = \
                "-----BEGIN CERTIFICATE-----\n" \
                "MIIDZDCCAkwCCQDifMO7eM+sRjANBgkqhkiG9w0BAQsFADB0MQswCQYDVQQGEwJT\n" \
                "RTESMBAGA1UECAwJQXVzdHJhbGlhMRIwEAYDVQQHDAlNZWxib3VybmUxEDAOBgNV\n" \
                "BAoMB2hpbWluZHMxCzAJBgNVBAsMAkNBMR4wHAYDVQQDDBVjYS5kZXYua3J5cHRv\n" \
                "bmFyYy5jb20wHhcNMjIxMTE4MDg0NDA5WhcNMjMxMTE4MDg0NDA5WjB0MQswCQYD\n" \
                "VQQGEwJTRTESMBAGA1UECAwJQXVzdHJhbGlhMRIwEAYDVQQHDAlNZWxib3VybmUx\n" \
                "EDAOBgNVBAoMB2hpbWluZHMxCzAJBgNVBAsMAkNBMR4wHAYDVQQDDBVjYS5kZXYu\n" \
                "a3J5cHRvbmFyYy5jb20wggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQCz\n" \
                "/5k/CqJotYGxqtiqX14+AU74ljsrmoGspnnVgMAPOTB1ZfA+musBPOHHxDxVPTeD\n" \
                "H5ikkn6FcuXKt6XX044mfrDE7Jemx1M2mCJah3dghhYP+j6jW40L9ujC+TVgVHAx\n" \
                "DDe7J3XhquposxptBu2dnAxoO7aa7ckPY7KTVWizTfuBsnw+Ln7rCVJKYWezvvF5\n" \
                "8yC+5Rlq+3MTOby8h+8db/uVa2a2gRgKx33jcnBjDms6xV6LMb5+UMyxt0l62eSk\n" \
                "KgDNFTzIbtFHG4JSDBqD+OU0TNsFHdzt/HbUJLdBeDLOasQvvOHLVjm3VSGsHuJR\n" \
                "z0D6CKfnMI6xbWxsmTBjAgMBAAEwDQYJKoZIhvcNAQELBQADggEBAHtHB18MMNf/\n" \
                "MY3728gmdYOl1ev18THgdFo/eOfSurgUT2tHa7ye/iOCCoYLzbRjRXzEWhY2ECR2\n" \
                "TwaU1EywPf9COPEA/D7jVTjkQVuYmjtCckVriEt1lkYpjJHfFVY4og6j/sK9ada2\n" \
                "uvyr/8JueBGTUGfIxndMKlh3Y7VmrhLKcwWGBhF+MP3QE+JtVBCn4Ay4sCDB/k/9\n" \
                "JrUv8qf7Pld+hWoyXnwpz7ixoUqUqgSRigISUbgpl5ovWsCkjF3xYPYnlhAOuE8M\n" \
                "Zghuzj2LUitMQzcYir0aakQ/c4koB2RMn6Ut6fOrackENDrYHRuJt5hm6E1dhX14\n" \
                "9+po9PqU408=\n" \
                "-----END CERTIFICATE-----\n" ;

};

struct DEVICE_GLOBAL_HARDWARE_PARAMETERS_FIXED 
{
    // ESP32 Chip model = ESP32-D0WDQ6 Rev 1
    // This chip has 2 cores
    // Chip ID: 7743348

    char cChipModel[64] ;
    char cChipRevision[64] ;
    char cChipCores[64] ;
    char cChipId[64] ;
    
    char baseMacChrSOFTAP[18] = {0};
    char baseMacChrBT[18] = {0};
    char baseMacChrETH[18] = {0};
    char baseMacChrWiFi[18] = {0};
} ;

struct WiFiInfo {
  bool found;
  char ssid[32] ;
  int32_t channel;
  int32_t rssi;
  wifi_auth_mode_t auth_mode;
} wifi_info;


extern SOFTWARE_GLOBAL_PARAMETERS_VAR software_parameters_variables;
extern SOFTWARE_GLOBAL_PARAMETERS_FIXED software_parameters_fixed;
extern DEVICE_GLOBAL_HARDWARE_PARAMETERS_FIXED constrcut_mcu_id_fixed;
extern E2PROM_STORED_DATA_FIXED e2prom_variables;
extern BROADCAST_GLOBAL_VAR broadcast_global_variables;
extern WiFiInfo wifi_info;

#endif
