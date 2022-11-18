#include "Arduino.h"
#include "system_structs.cpp"
#include "ESP32Ping.h"


PassingDataStruct ping_ip_google() {
    const char* funcID = "734321";
    const char* funcName = "ping_ip_google";
    PassingDataStruct returning_data;
    const IPAddress remote_ip (8 , 8 , 8 , 8 );

    // Serial.print("Pinging ip ");
    // Serial.println(remote_ip);
    if(Ping.ping(remote_ip)) {
        // Serial.println("Google IP Ping - Success!!");
        returning_data.bOperationLogic = true;
        return returning_data;
    } else {
        // Serial.println("Error :(");
        returning_data.bOperationLogic = false;
        return returning_data;
    }
}


PassingDataStruct ping_host_google() {
    const char* funcID = "894563";
    const char* funcName = "ping_host_google";
    PassingDataStruct returning_data;
    const char* remote_host = "www.google.com";

    // Serial.print("Pinging host ");
    // Serial.println(remote_host);

    if(Ping.ping(remote_host)) {
        // Serial.println("Google Host Ping - Success!!");
        returning_data.bOperationLogic = true;
        return returning_data;
    } else {
        // Serial.println("Error :(");
        returning_data.bOperationLogic = false;
        return returning_data;
    }
}