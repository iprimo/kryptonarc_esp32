// https://stackoverflow.com/questions/6882637/using-struct-in-different-cpp-file
// https://stackoverflow.com/questions/6882637/using-struct-in-different-cpp-file
// 
#include <string>
using namespace std;

#ifndef PassingDataStruct_H
#define PassingDataStruct_H
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

#endif



#ifndef HTTPWorksReply_H
#define HTTPWorksReply_H
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

#endif





#ifndef GLOBAL_TENANT_VAR
#define GLOBAL_TENANT_VAR
struct TENANT_GLOBAL_VAR
{
    const char *cTenant;
    const char *cProfile;
    const char *cHardware;
};
#endif




#ifndef GLOBAL_SYSTEM_VAR
#define GLOBAL_SYSTEM_VAR
struct SYSTEM_GLOBAL_VAR
{
    const char* STANDARD_WIFI_SSID = "KryptonArc2G";
    const char* STANDARD_WIFI_PASSWORD = "PleaseHelpMe";
    const int ledRed = 18;
    const int ledBlue = 17;
    const int ledGreen = 5;
    const int buzzerPassive = 19;

    const char *url = "https://fota.kryptonarc.com/firmware.bin"; //state url of your firmware image


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
#endif


#ifndef GLOBAL_HARDWARE_ID_VAR
#define GLOBAL_HARDWARE_ID_VAR
struct DEVICE_HARDWARE_INFO 
{
    std::string sChipModel;
    std::string sChipRevision;
    std::string sChipCores;
    std::string sChipId;

    char baseMacChrSOFTAP[18] = {0};
    char baseMacChrBT[18] = {0};
    char baseMacChrETH[18] = {0};
    char baseMacChrWiFi[18] = {0};
} ;
#endif
