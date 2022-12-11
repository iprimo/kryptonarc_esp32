//  https://randomnerdtutorials.com/esp32-useful-wi-fi-functions-arduino/
#include "Arduino.h"
#include "WiFi.h"
#include "WiFiClientSecure.h"
#include "HTTPClient.h"
#include "system_structs.cpp"
#include "ESP32Ping.h"
#include "ArduinoJson.h"

extern SYSTEM_GLOBAL_VAR system_global_variables;
extern TENANT_GLOBAL_VAR tenant_global_variables;

// https://medium.com/@sanghviyash6/migrating-any-http-request-to-https-on-esp32-5545a6de7845
// https://medium.com/@sanghviyash6/migrating-any-http-request-to-https-on-esp32-5545a6de7845

// https://www.youtube.com/watch?v=dsmMzS3Qvg0&ab_channel=techiesms
// https://www.youtube.com/watch?v=dsmMzS3Qvg0&ab_channel=techiesms
// https://github.com/techiesms/ESP8266-Series/blob/master/HTTPSRequest/HTTPSRequest.ino
// https://github.com/techiesms/ESP8266-Series/blob/master/HTTPSRequest/HTTPSRequest.ino


// const char* host_domain_subdomain = "api.github.com"; // Server from which data is to be fetched
// const char* host_domain_subdomain = "https://hw_direct.dev.kryptonarc.com/raw_hw_check"; // Server from which data is to be fetched
const char* host_domain_subdomain = "hw_direct.dev.kryptonarc.com"; // Server from which data is to be fetched
const int httpsPort = 443; // Default port for HTTPS 


// # https://stackoverflow.com/questions/68568043/esp32-https-post-json-to-aws
// # https://stackoverflow.com/questions/68568043/esp32-https-post-json-to-aws
void postToAmazonSecure(String jsonToSend){
    WiFiClientSecure client;
    
    const char* emonDataAPI = system_global_variables.server_hardware_direct_ca_domain;
    const char* emonDataAPIPath = system_global_variables.server_hardware_direct_ca_path;
    const char* certificate_root_ca = system_global_variables.server_hardware_direct_ca_certificate ;
    Serial.print("connecting to : '");
    Serial.print(emonDataAPI);
    Serial.println("'");
    Serial.println( emonDataAPI );
    client.setCACert(certificate_root_ca);
    client.connect( emonDataAPI , 443);
    
    Serial.print("requesting URL: '");
    Serial.print(emonDataAPI);
    Serial.println("'");
    String requestString = String("POST ") + emonDataAPIPath + " HTTP/1.1\r\n" +
        "Host: " + emonDataAPI + "\r\n" +
        "User-Agent: KryptonArcHWAgent" + "ESP32" + "agentVersion" + "1" + "\r\n" +
        "Connection: close\r\n" +
        "Content-Type: application/json\r\n" +
        //"Authorization: Bearer " + authorization_code + "\r\n" +
        "Content-Length: " + jsonToSend.length() + "\r\n" +
        "\r\n" +
        jsonToSend + "\r\n";
        Serial.println(requestString);
    client.print(requestString);
    
    Serial.println("request sent");
    unsigned long timeout = millis();
    while (client.available() == 0) {
        if (millis() - timeout > 5000) {
            Serial.println(">>> Client Timeout !");
            client.stop();
            return;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////
// hardware direct status check
void post2_hw_direct_statuscheck___Backup(
    // String sE01, String sE02, String sE03, String sE04, String sE05, String sE06, String sE07, String sE08, String sE09, String sE10
    ){
    int  conn;
    DynamicJsonDocument doc( 512 );
    WiFiClientSecure client;
    
    doc["sE01"] = "sE01____tttt";
    doc["sE02"] = "sE02____tttt";
    doc["sE03"] = "sE03____tttt";
    doc["sE04"] = "sE04____tttt";
    doc["sE05"] = "sE05____tttt";
    doc["sE06"] = "sE06____tttt";
    doc["sE07"] = "sE07____tttt";
    doc["sE08"] = "sE08____tttt";
    doc["sE09"] = "sE09____tttt";
    doc["sE10"] = "sE10____tttt";

    String json;
    serializeJson(doc, json);

    const char* emonDataAPI = system_global_variables.server_hardware_direct_ca_domain;
    const char* emonDataAPIPath = "/raw_hw/statuscheck";
    const char* certificate_root_ca = system_global_variables.server_hardware_direct_ca_certificate ;
    Serial.print("connecting to : '");
    Serial.print(emonDataAPI);
    Serial.println("'");
    Serial.println( emonDataAPI );
    client.setCACert(certificate_root_ca);
    conn = client.connect( emonDataAPI , 443);
    
    if (conn == 1) {

        Serial.print("requesting URL: '");
        Serial.print(emonDataAPI);
        Serial.println("'");
        String requestString = String("POST ") + emonDataAPIPath + " HTTP/1.1\r\n" +
            "Host: " + emonDataAPI + "\r\n" +
            "User-Agent: KryptonArcHWAgent" + "ESP32" + "agentVersion" + "1" + "\r\n" +
            "Connection: close\r\n" +
            "Content-Type: application/json\r\n" +
            "Cache-Control: no-cache\r\n" +
            //"Authorization: Bearer " + authorization_code + "\r\n" +
            "Content-Length: " + json.length() + "\r\n" +
            "\r\n" +
            json + "\r\n";
        Serial.println(requestString);
        
        
        
        // client.print(requestString);
        if (client.println() == 0)
        {
            Serial.println(F("Failed to send request"));
            return;
        }
        
        Serial.println("request sent");
        Serial.println("Waiting for reply... ");
        unsigned long timeout = millis();
        
        while (client.available() == 0) {
            Serial.print(".");
            if (millis() - timeout > 5000) {
                Serial.println(">>> Client Timeout !");
                client.stop();
                // return "request timeout";
                return;
            }
        }

        

        // Serial.println();
        // Serial.println("Got response");
        // Serial.println("return status: ");
        // String response = client.readStringUntil('\n');
        // Serial.println(response.c_str());

        ////////////////////////////////////////////////////////////////////////////////////////
        //Print Server Response
        Serial.println("whole returned data");
        while (client.available()) {
            char c = client.read();
            Serial.write(c);

            // String response = client.readStringUntil('\n');
            // Serial.println(response.c_str());


            // String line = client.readStringUntil('\n');
            // if (line.startsWith("{\"state\":\"success\"")) {
            // Serial.println("esp8266/Arduino CI successfull!");
            // } else {
            // Serial.println("esp8266/Arduino CI has failed");
            // }

        }
        
        Serial.println(); 
        Serial.println("closing connection");
        client.stop();



    // JSON
    // Allocate the JSON document
    const size_t capacity = JSON_ARRAY_SIZE(10) + 10 * JSON_OBJECT_SIZE(2) + 10 * JSON_OBJECT_SIZE(3) + 10 * JSON_OBJECT_SIZE(5) + 10 * JSON_OBJECT_SIZE(8) + 3730;
    DynamicJsonDocument doc(capacity);

    // Parse JSON object
    DeserializationError error = deserializeJson(doc, client);

    if (error)
    {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.c_str());
        return;
    }

    JsonObject root_0 = doc[0];
    Serial.println("JSON Docss");
    Serial.println(root_0);


    // Get the Name:
    const char *root_0_name = root_0["message"];
    Serial.println("message >>> ");
    Serial.println(root_0_name);

        return;
    } else {
        client.stop();
        Serial.println("Connection Failed");
        return;
    }

}



////////////////////////////////////////////////////////////////////////////////////
// hardware direct status check
//  https://github.com/witnessmenow/arduino-sample-api-request/blob/master/ESP32/HTTP_GET_JSON/HTTP_GET_JSON.ino
void post2_hw_direct_statuscheck(
    String sE01, String sE02, String sE03, String sE04, String sE05, String sE06, String sE07, String sE08, String sE09, String sE10
    ){
    int  conn;
    DynamicJsonDocument doc( 512 );
    WiFiClientSecure client;
    
    doc["sE01"] = sE01; // "sE01____tttt";
    doc["sE02"] = sE02; // "sE02____tttt";
    doc["sE03"] = sE03; // "sE03____tttt";
    doc["sE04"] = sE04; // "sE04____tttt";
    doc["sE05"] = sE05; // "sE05____tttt";
    doc["sE06"] = sE06; // "sE06____tttt";
    doc["sE07"] = sE07; // "sE07____tttt";
    doc["sE08"] = sE08; // "sE08____tttt";
    doc["sE09"] = sE09; // "sE09____tttt";
    doc["sE10"] = sE10; // "sE10____tttt";

    String json;
    serializeJson(doc, json);

    const char* emonDataAPI = system_global_variables.server_hardware_direct_ca_domain;
    const char* emonDataAPIPath = "/raw_hw/statuscheck";
    const char* certificate_root_ca = system_global_variables.server_hardware_direct_ca_certificate ;
    Serial.print("connecting to : '");
    Serial.print(emonDataAPI);
    Serial.println("'");
    Serial.println( emonDataAPI );
    client.setCACert(certificate_root_ca);
    conn = client.connect( emonDataAPI , 443);
    
    if (conn == 1) {

        Serial.print("requesting URL: '");
        Serial.print(emonDataAPI);
        Serial.println("'");
        String requestString = String("POST ") + emonDataAPIPath + " HTTP/1.1\r\n" +
            "Host: " + emonDataAPI + "\r\n" +
            "User-Agent: KryptonArcHWAgent" + "ESP32" + "agentVersion" + "1" + "\r\n" +
            "Connection: close\r\n" +
            "Content-Type: application/json\r\n" +
            // "Cache-Control: no-cache\r\n" +
            //"Authorization: Bearer " + authorization_code + "\r\n" +
            "Content-Length: " + json.length() + "\r\n" +
            "\r\n" +
            json + "\r\n";
        Serial.println(requestString);
        
        
        
        client.print(requestString);
        // if (client.println() == 0)
        // {
        //     Serial.println(F("Failed to send request"));
        //     return;
        // }
        
        Serial.println("request sent");
        Serial.println("Waiting for reply... ");
        unsigned long timeout = millis();
        
        while (client.available() == 0) {
            Serial.print(".");
            if (millis() - timeout > 5000) {
                Serial.println(">>> Client Timeout !");
                client.stop();
                // return "request timeout";
                return;
            }
        }

        

        // Serial.println();
        // Serial.println("Got response");
        // Serial.println("return status: ");
        // String response = client.readStringUntil('\n');
        // Serial.println(response.c_str());

        ////////////////////////////////////////////////////////////////////////////////////////
        //Print Server Response

        // Check HTTP status
        char status[32] = {0};
        client.readBytesUntil('\r', status, sizeof(status));
        if (strcmp(status, "HTTP/1.1 200 OK") != 0)
        {
            Serial.print(F("Unexpected response: "));
            Serial.println(status);
            return;
        }

        // Skip HTTP headers
        char endOfHeaders[] = "\r\n\r\n";
        if (!client.find(endOfHeaders))
        {
            Serial.println(F("Invalid response"));
            return;
        }

        // This is probably not needed for most, but I had issues
        // with the Tindie api where sometimes there were random
        // characters coming back before the body of the response.
        // This will cause no hard to leave it in
        // peek() will look at the character, but not take it off the queue
        while (client.available() && client.peek() != '{')
        {
            char c = 0;
            client.readBytes(&c, 1);
            Serial.print(c);
            Serial.println("BAD");
        }

        //  // While the client is still availble read each
        //  // byte and print to the serial monitor
        //  while (client.available()) {
        //    char c = 0;
        //    client.readBytes(&c, 1);
        //    Serial.print(c);
        //  }

        //Use the ArduinoJson Assistant to calculate this:
        //StaticJsonDocument<192> docReturned;
        DynamicJsonDocument docReturned(64); //For ESP32/ESP8266 you'll mainly use dynamic.

        DeserializationError error = deserializeJson(docReturned, client);

        if (!error) {
            const char*  s__E_Message = docReturned["sEMessage"];

            Serial.print("s__E_Message: ");
            Serial.println(s__E_Message);
            
        } else {
            Serial.print(F("deserializeJson() failed: "));
            Serial.println(error.f_str());
            return;
        }

        Serial.println(); 
        Serial.println("closing connection");
        client.stop();




        return;
    } else {
        client.stop();
        Serial.println("Connection Failed");
        return;
    }

}


