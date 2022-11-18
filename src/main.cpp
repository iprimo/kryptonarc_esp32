// https://github.com/palmmaximilian/ReactNativeArduinoBLE
// https://github.com/palmmaximilian/ReactNativeArduinoBLE

#include "Arduino.h"
#include "modules/system_structs.cpp"
#include "modules/bluetooth_works.h"
#include "modules/wifi_works.hpp"
#include "modules/hardware_uuid.h"
#include "modules/e2prom_read_write.h"
#include "modules/logging_service.hpp"
#include "modules/notification.hpp"
#include "modules/cloud_works.hpp"
#include "modules/ping_works.hpp"
#include "modules/morse_code.hpp"

SYSTEM_GLOBAL_VAR system_global_variables;
TENANT_GLOBAL_VAR tenant_global_variables;
DEVICE_HARDWARE_INFO Hardware____ID;

void setup()
{
    Serial.begin(115200);
    tenant_global_variables.cTenant = "a_b_c_1111_tenant";
    tenant_global_variables.cProfile = "a_b_c_1111_profile";
    tenant_global_variables.cHardware = "a_b_c_1111_padlock";

    // put your setup code here, to run once:
    pinMode (system_global_variables.ledRed, OUTPUT);
    pinMode (system_global_variables.ledBlue, OUTPUT);
    pinMode (system_global_variables.ledGreen, OUTPUT);
    pinMode( system_global_variables.buzzerPassive, OUTPUT);

}

void loop()
{

    const char* funcID = "67827";
    const char* funcName = "mainLoop";
    PassingDataStruct wifi_scan_result, wifi_connect_result, Ping_IP, Ping_Host;

    Serial.println("Rest_All_Notification 111");
    notification_reset_all();
    // notification_sound( "Rest_All_Notification" );
    // delay(3000);
    // Serial.println("Rest_All_Notification 222");

    // Reading Existing Configration from E2PROM~
    while ( true ) {
        // If SSID of KryptonArc-eKeySmith exists directly go to eKeySmith (even without Tenant config)

        // Config Exists
        if (false) {
            // Yes - (2 Config Exists) - (Start of Bluetooth First attempt)
                // Start Blueooth attempts and connect to App (Notifcation: 0x46282)
                // Bluetooth attempt works
                    // Yes - (2 Bluetooth attempt works)
                        // Stay here and execute instructions (Notifcation: 0x77299)
                        // Portentila tasks: 
                            // User Not logged in - Simple-Public-Data-Displayed
                            // User logged in - Not have persmission to access this device -> Detaild Public info displayed
                            // User loggdin - Actions could changed depenidng on permission
                            // ImageUpgrade - Approval Needed ()
                    // No - (2 Bluetooth attempt works)
                        // KryptonArc-eKeysmith SSID exists ? (For Paid Accounts)
                            // Yes - (2 KryptonArc-eKeysmith SSID exists)
                                // (Notifcation: 0x48277)
                                // Wifi - eKeysmith - If device regsitered ans is ON for 5 Miniutes of devie ON, it goes for eKeysmith
                            // No - (2 KryptonArc-eKeysmith SSID exists)
                                // (Notifcation: 0x42729)
                                // Try for 5 Minute
                                // 5 Minutes failed 
                                    // Yes - (2 raise fault (Notifcation: 0x57991)
                        
        } else {
            // No - (2 Config Exists) - (Directly go to WiFi attempts)
            int repeat_in_case_of_failure = 0; // incase of wifi detection failure it tries 3 more times
            PassingDataStruct wifi_scan_result;
            wifi_scan_result.bOperationLogic = false;
            

            //////////////////////////////////////////////////////////////////////////////////////////
            Serial.println( " _+_+_+_+_  _+_+_+_+_  _+_+_+_+_  _+_+_+_+_  _+_+_+_+_ 111111" );
            // WiFi detection
            while ( !wifi_scan_result.bOperationLogic && repeat_in_case_of_failure <= 3 ){
                wifi_scan_result = wifiTargetedNetworkScan( system_global_variables.STANDARD_WIFI_SSID );
                repeat_in_case_of_failure++;
                delay(1000); // delay between each scan
            }
            // If wifi not detected - sound error and return cycle
            if ( !wifi_scan_result.bOperationLogic ){
                loggingService( wifi_scan_result.cMessage , funcID , funcName , tenant_global_variables.cTenant, tenant_global_variables.cProfile  );
                notification_light( "redLedFlashing", 3 , 100 );
                notification_sound( "Error_Triple" , 10 );
                morse_code_data_transfer("0x47197"); // could not detect Wifi SSID
                return;
            }
            //////////////////////////////////////////////////////////////////////////////////////////

            //////////////////////////////////////////////////////////////////////////////////////////
            Serial.println( " _+_+_+_+_  _+_+_+_+_  _+_+_+_+_  _+_+_+_+_  _+_+_+_+_ 222222" );
            // wifi detected, moving to next step 
            loggingService( wifi_scan_result.cMessage , funcID , funcName , tenant_global_variables.cTenant, tenant_global_variables.cProfile  );
            notification_light( "blueLedFlashing", 3 , 100 );

            Serial.println( " _+_+_+_+_  _+_+_+_+_  _+_+_+_+_  _+_+_+_+_  _+_+_+_+_ 333333" );
            // connecting to wifi 
            wifi_connect_result = initWiFi( system_global_variables.STANDARD_WIFI_SSID , system_global_variables.STANDARD_WIFI_PASSWORD );
            Serial.print( "wifi_connect_result:: " ); Serial.println( wifi_connect_result.bOperationLogic );
            if ( !wifi_connect_result.bOperationLogic ) {
                loggingService( "Device could not connect to Wifi" , funcID , funcName , tenant_global_variables.cTenant, tenant_global_variables.cProfile  );
                notification_light( "redLedFlashing", 3 , 100 );
                notification_sound( "Error_Triple" , 10 );
                morse_code_data_transfer("0x56923"); // could not connect to Wifi
                return;
            }

            // Serial.println( " _+_+_+_+_  _+_+_+_+_  _+_+_+_+_  _+_+_+_+_  _+_+_+_+_ 44444" );
            // // extracting hardware ID
            // Hardware____ID = getMacAddress();
            // Serial.print( "sChipModel:: " ); Serial.println( Hardware____ID.sChipModel.c_str() );
            // Serial.print( "iChipRevision:: " ); Serial.println( Hardware____ID.iChipRevision );
            // Serial.print( "iChipCores:: " ); Serial.println( Hardware____ID.iChipCores );
            // Serial.print( "uChipId:: " ); Serial.println( Hardware____ID.uChipId );
            // Serial.print( "baseMacChrSOFTAP:: " ); Serial.println( Hardware____ID.baseMacChrSOFTAP );
            // Serial.print( "baseMacChrBT:: " ); Serial.println( Hardware____ID.baseMacChrBT );
            // Serial.print( "baseMacChrETH:: " ); Serial.println( Hardware____ID.baseMacChrETH );
            // Serial.print( "baseMacChrWiFi:: " ); Serial.println( Hardware____ID.baseMacChrWiFi );


            // ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            // // Testing Wifi Connectivity by ping Google IP
            // Serial.println( " _+_+_+_+_  _+_+_+_+_  _+_+_+_+_  _+_+_+_+_  _+_+_+_+_ 555555" );
            // Ping_IP = ping_ip_google();
            // if ( !Ping_IP.bOperationLogic ) {
            //     loggingService( "Wifi ping Google IP failed" , funcID , funcName , tenant_global_variables.cTenant, tenant_global_variables.cProfile  );
            //     notification_light( "redLedFlashing", 3 , 100 );
            //     morse_code_data_transfer("0x85772"); // could not ping google IP address
            //     return;
            // }
            // Serial.println("Google IP Ping - Success!!");
            // ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            
            // //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
            // // Testing DNS by ping Google hostname
            // Serial.println( " _+_+_+_+_  _+_+_+_+_  _+_+_+_+_  _+_+_+_+_  _+_+_+_+_ 66666" );
            // Ping_Host = ping_host_google();
            // if ( !Ping_Host.bOperationLogic ) {
            //     loggingService( "Wifi ping Google host failed" , funcID , funcName , tenant_global_variables.cTenant, tenant_global_variables.cProfile  );
            //     notification_light( "redLedFlashing", 3 , 100 );
            //     morse_code_data_transfer("0x75422"); // could not ping google hostname
            //     return;
            // }
            // Serial.println("Google Host Ping - Success!!");
            // ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            while(true){

                Serial.println( " _+_+_+_+_  _+_+_+_+_  _+_+_+_+_  _+_+_+_+_  _+_+_+_+_ 77777" );
                // check_Lock_Assignment_2_Any_Tenant();
                // check_Lock_Assignment_2_Any_Tenant_X222222();
                // check_Lock_Assignment_2_Any_Tenant_X3333();
                check_Lock_Assignment_2_Any_Tenant_X4444();
                delay(5000);
            }

            


            // Prior to wiping or opening the device, some checks has to be done on the server, to ensure the device is not manipulated, 
            //      and acutally does not belong to existing user
            

            // Checking if the Device registered to (global-hardware-table & a tenant)
            if (false){
                // Serial.println("Submodule: Yes & Yes - Device registered to (global-hardware-table & a tenant)");
                
                // Yes & Yes - Device registered to (global-hardware-table & a tenant)
                // Wifi - Go to eKeysmith - does not have config on it, but it is registed - potenional config wipe or device manipulation
            } else if (false){
                // Serial.println("Submodule: Yes & No - Device registered to (global-hardware-table & a tenant)");

                // Yes & No - Device registered to (global-hardware-table & a tenant)
                // DownloadLatestImage via WiFi
                // Keep Checking for assigment to a tenant
            } else if (false){
                // Serial.println("Submodule: No & Yes - Device registered to (global-hardware-table & a tenant)");

                // No & Yes - Device registered to (global-hardware-table & a tenant)
                // Wait for Tenant instructions
            } else {
                // Serial.println("Submodule: No & No - Device registered to (global-hardware-table & a tenant)");

                // No & No - Device registered to (global-hardware-table & a tenant)
                // Wipe E2PROM\DownloadImage\CallHome\Regsiter - (No approval)
                // DownloadLatestImage via WiFi
                // Register to global hardware repo (if device already does not exists, User has to put the MAC address details has to be put in manually)
                // CallHome

            }


        }


        

               

        // Wait a bit before scanning again
        delay(1000);

    }
}




