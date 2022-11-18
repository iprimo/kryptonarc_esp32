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
    
    // To print sMessage use "Serial.println(str.c_str());"
    // Source: https://techoverflow.net/2022/09/07/how-to-serial-println-a-stdstring/
    std::string sMessage;

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


    const char *server_hw_gw_fingerprint = "F1 13 62 10 51 7B 3A F9 1C 96 D8 79 DE 39 2B C3 95 0A EA 57";
    const char *server_hw_gw_certificate = \
"-----BEGIN CERTIFICATE-----\n"
"MIIDuTCCAqGgAwIBAgIUJvmxijo9/k3BQHGgju1oUB960OQwDQYJKoZIhvcNAQEL\n"
"BQAwbDELMAkGA1UEBhMCQVUxEzARBgNVBAgMClNvbWUtU3RhdGUxITAfBgNVBAoM\n"
"GEludGVybmV0IFdpZGdpdHMgUHR5IEx0ZDElMCMGA1UEAwwcaHdfZGlyZWN0LmRl\n"
"di5rcnlwdG9uYXJjLmNvbTAeFw0yMjExMTcwMTM4MjJaFw0yMzExMTcwMTM4MjJa\n"
"MGwxCzAJBgNVBAYTAkFVMRMwEQYDVQQIDApTb21lLVN0YXRlMSEwHwYDVQQKDBhJ\n"
"bnRlcm5ldCBXaWRnaXRzIFB0eSBMdGQxJTAjBgNVBAMMHGh3X2RpcmVjdC5kZXYu\n"
"a3J5cHRvbmFyYy5jb20wggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQD7\n"
"a/cfQQWZLWiOj07lO9l4yT55gZzYHeKm7JMmwJHNCg9uNbeS+h6/34hRhKoARMUI\n"
"Va/6o8fsfdTlJCFXPfO7AVeDGlwHeaUSw2/DokcD331cad+SB/X5y0r/L0JRECXJ\n"
"8tCebddhri6M3ujMYUTenvoxBNOq4r/TWFj6NyXU83LPySDqQF91VHV107Td/Wye\n"
"Sh3aUc3wD6sVBWE4UJmmQubeOa93Xp7uskc6Hv2w1bgghKLIJqHqCABomIaIKLTu\n"
"fLYOl6QETI8lQDV4+QOk3NcF5BRkwcw6tOwjDyj1er1OS9Zd83fxnplkCiqJFS3J\n"
"XB9mgB7TXgocZTq6E5ljAgMBAAGjUzBRMB0GA1UdDgQWBBQokMac3B8mwKEBePox\n"
"jZG/ZkDZLDAfBgNVHSMEGDAWgBQokMac3B8mwKEBePoxjZG/ZkDZLDAPBgNVHRMB\n"
"Af8EBTADAQH/MA0GCSqGSIb3DQEBCwUAA4IBAQB+ovVXUvwJvpKiXrTszu3i6znh\n"
"FlNM24YgFHLOpaBRLW/yhfdq4scyGEp9M9c/jHJORyH43yT9VRQppEjyRB6kC87q\n"
"7xMzH+jGuT7IrXsaYp71SMkh/Rq8pHhomzBgP1KArODoE6mHDjxLywFq7CCx1aYI\n"
"ooKG4E91svSS0FOYI6XiZxaXczdGUaPVc69etpifEzuDuvBXrfwyYpEflcwhvDgh\n"
"p8GQAfRLnANwqCq5ND/UX8DFfp10EqzZV5Az630DT/CXEGCGIeABnnjNMZ1R1jQh\n"
"uyX+I8Lr5P/N5a1MTc7trs0x/TooeVksG3g/3llab47tKA4641o2E/U/Oi2Q\n"
"-----END CERTIFICATE-----\n" ;
    // const char* server_hw_gw_fingerprint = "78 40 ED 9D 2C CE 5D F6 7C 65 4D 85 ED 1F 2C 37 17 09 6F C0 E0 74 F5 0F C8 27 B0 8F 92 2A CF 70";    
//     const char *server_hw_gw_certificate = R"(
// -----BEGIN CERTIFICATE-----
// MIIDuTCCAqGgAwIBAgIUJvmxijo9/k3BQHGgju1oUB960OQwDQYJKoZIhvcNAQEL
// BQAwbDELMAkGA1UEBhMCQVUxEzARBgNVBAgMClNvbWUtU3RhdGUxITAfBgNVBAoM
// GEludGVybmV0IFdpZGdpdHMgUHR5IEx0ZDElMCMGA1UEAwwcaHdfZGlyZWN0LmRl
// di5rcnlwdG9uYXJjLmNvbTAeFw0yMjExMTcwMTM4MjJaFw0yMzExMTcwMTM4MjJa
// MGwxCzAJBgNVBAYTAkFVMRMwEQYDVQQIDApTb21lLVN0YXRlMSEwHwYDVQQKDBhJ
// bnRlcm5ldCBXaWRnaXRzIFB0eSBMdGQxJTAjBgNVBAMMHGh3X2RpcmVjdC5kZXYu
// a3J5cHRvbmFyYy5jb20wggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQD7
// a/cfQQWZLWiOj07lO9l4yT55gZzYHeKm7JMmwJHNCg9uNbeS+h6/34hRhKoARMUI
// Va/6o8fsfdTlJCFXPfO7AVeDGlwHeaUSw2/DokcD331cad+SB/X5y0r/L0JRECXJ
// 8tCebddhri6M3ujMYUTenvoxBNOq4r/TWFj6NyXU83LPySDqQF91VHV107Td/Wye
// Sh3aUc3wD6sVBWE4UJmmQubeOa93Xp7uskc6Hv2w1bgghKLIJqHqCABomIaIKLTu
// fLYOl6QETI8lQDV4+QOk3NcF5BRkwcw6tOwjDyj1er1OS9Zd83fxnplkCiqJFS3J
// XB9mgB7TXgocZTq6E5ljAgMBAAGjUzBRMB0GA1UdDgQWBBQokMac3B8mwKEBePox
// jZG/ZkDZLDAfBgNVHSMEGDAWgBQokMac3B8mwKEBePoxjZG/ZkDZLDAPBgNVHRMB
// Af8EBTADAQH/MA0GCSqGSIb3DQEBCwUAA4IBAQB+ovVXUvwJvpKiXrTszu3i6znh
// FlNM24YgFHLOpaBRLW/yhfdq4scyGEp9M9c/jHJORyH43yT9VRQppEjyRB6kC87q
// 7xMzH+jGuT7IrXsaYp71SMkh/Rq8pHhomzBgP1KArODoE6mHDjxLywFq7CCx1aYI
// ooKG4E91svSS0FOYI6XiZxaXczdGUaPVc69etpifEzuDuvBXrfwyYpEflcwhvDgh
// p8GQAfRLnANwqCq5ND/UX8DFfp10EqzZV5Az630DT/CXEGCGIeABnnjNMZ1R1jQh
// uyX+I8Lr5P/N5a1MTc7trs0x/TooeVksG3g/3llab47tKA4641o2E/U/Oi2Q
// -----END CERTIFICATE-----
// )";

};
#endif


#ifndef GLOBAL_HARDWARE_ID_VAR
#define GLOBAL_HARDWARE_ID_VAR
struct DEVICE_HARDWARE_INFO 
{
    std::string sChipModel;
    int iChipRevision = 0;
    int iChipCores = 0;
    uint32_t uChipId = 0;

    char baseMacChrSOFTAP[18] = {0};
    char baseMacChrBT[18] = {0};
    char baseMacChrETH[18] = {0};
    char baseMacChrWiFi[18] = {0};
} ;
#endif
