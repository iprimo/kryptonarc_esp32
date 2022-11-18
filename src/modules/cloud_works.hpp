//  https://randomnerdtutorials.com/esp32-useful-wi-fi-functions-arduino/
#include "Arduino.h"
#include "WiFi.h"
#include "WiFiClientSecure.h"
#include "HTTPClient.h"
#include "system_structs.cpp"
#include "ESP32Ping.h"

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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void check_Lock_Assignment_2_Any_Tenant() {

    WiFiClientSecure client;

    
//    http.begin("http://jsonplaceholder.typicode.com/posts");  //Specify destination for HTTP request
//    http.addHeader("Content-Type", "text/plain");             //Specify content-type header
    
    Serial.println("_+_+_+_+_+_ . AA11");

    // client.setCertificate( system_global_variables.server_hw_gw_certificate );
    // client.setCACert( system_global_variables.server_hw_gw_certificate );
    // client.setCACert( server_hw_gw_certificate );
    // client.setCertificate( server_hw_gw_certificate ); // for client verification
    //client.setPrivateKey(test_client_key);	// for client verification
    

    Serial.println("_+_+_+_+_+_ . AA22");

    Serial.print("connecting to "); Serial.println(host_domain_subdomain);
    if (!client.connect(host_domain_subdomain, httpsPort)) { // establishing connection with the server(api.github.com) at port 443
    Serial.println("_+_+_+_+_+_ . AA33");
        Serial.println("connection failed");
        return; // this line will return the function to the starting of void setup()
    }

    Serial.println("_+_+_+_+_+_ . AA44");


    if (client.verify( system_global_variables.server_hw_gw_fingerprint , host_domain_subdomain)) { // verfying fingerprint with the server
        Serial.println("_+_+_+_+_+_ . AA55");
        Serial.println("certificate matches");
    } else {
        Serial.println("_+_+_+_+_+_ . AA66");
        Serial.println("certificate doesn't match");
    }




}


// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// void check_Lock_Assignment_2_Any_Tenant() {

//     WiFiClientSecure client;

    
// //    http.begin("http://jsonplaceholder.typicode.com/posts");  //Specify destination for HTTP request
// //    http.addHeader("Content-Type", "text/plain");             //Specify content-type header

//     // client.setCACert( system_global_variables.server_hw_gw_certificate );
//     client.setCACert( server_hw_gw_certificate );
//     // client.setCertificate( server_hw_gw_certificate ); // for client verification
//     //client.setPrivateKey(test_client_key);	// for client verification
    

//     Serial.print("connecting to "); Serial.println(host_domain_subdomain);
//     if (!client.connect(host_domain_subdomain, httpsPort)) { // establishing connection with the server(api.github.com) at port 443
//         Serial.println("connection failed");
//         return; // this line will return the function to the starting of void setup()
//     }

//     Serial.println("_+_+_+_+_+_ . 88888");


//     if (client.verify(fingerprint, host_domain_subdomain)) { // verfying fingerprint with the server
//         Serial.println("certificate matches");
//     } else {
//         Serial.println("certificate doesn't match");
//     }
//     Serial.println("_+_+_+_+_+_ . 99999");



// }



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void check_Lock_Assignment_2_Any_Tenant_X222222() { 
    // https.begin( host_domain_subdomain , system_global_variables.server_hw_gw_fingerprint);

    Serial.println("BBBB 1111");
    HTTPClient https;
    WiFiClientSecure newSecure;
    Serial.println("BBBB 2222");
    int checkBegin = https.begin(newSecure, "hw_direct.dev.kryptonarc.com", 443, "", false);
    Serial.println(checkBegin);
    
    Serial.println("BBBB 3333");

    // int code = https.GET();
    int code = https.POST("hot_stuff__payload_from_ESP32  ");
    String payload = https.getString();
    Serial.println("BBBB 4444");
    Serial.println(code);
    Serial.println("BBBB 5555");
    Serial.println(payload);

    // !
    https.end();
    newSecure.stop();
}






////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void check_Lock_Assignment_2_Any_Tenant_X3333() { 

    const char* host = "hw_direct.dev.kryptonarc.com"; // Server from which data is to be fetched
    const int httpsPort = 443; // Default port for HTTPS 

    // Use web browser to view and copy
    // SHA1 fingerprint of the certificate
    const char* fingerprint = "F1 13 62 10 51 7B 3A F9 1C 96 D8 79 DE 39 2B C3 95 0A EA 57"; // Fingerprint/Thumbprint for website api.github.com
    
    WiFiClientSecure client;  // Use WiFiClientSecure class to create client instance
    Serial.print("connecting to ");
    Serial.println(host);
    if (!client.connect(host, httpsPort)) { // establishing connection with the server(api.github.com) at port 443
        Serial.println("connection failed");
        return; // this line will return the function to the starting of void setup()
    }

    if (client.verify(fingerprint, host)) { // verfying fingerprint with the server
        Serial.println("certificate matches");
    } else {
        Serial.println("certificate doesn't match");
    }

    // String url = "/repos/esp8266/Arduino/commits/master/status"; //address from which we need to get the data inside the server.
    // Serial.print("requesting URL: ");
    // Serial.println(url);

    // client.print(String("GET ") + url + " HTTP/1.1\r\n" +
    //             "Host: " + host + "\r\n" +
    //             "User-Agent: BuildFailureDetectorESP8266\r\n" +
    //             "Connection: close\r\n\r\n");
    // /*
    // * GET /repos/esp8266/Arduino/commits/master/status HTTP/1.1
    // * Host : api.github.com
    // * User-Agent : BuildFailureDetectorESP8266
    // * Connection : close
    // */

    // Serial.println("request sent");
    // while (client.connected()) { // until the client is connected, read out the response
    //     String line = client.readStringUntil('\n');
    //     if (line == "\r") {
    //     Serial.println("headers received");
    //     break;
    //     }
    // }
    // String line = client.readStringUntil('\n');
    // if (line.startsWith("{\"state\":\"success\"")) {
    //     Serial.println("esp8266/Arduino CI successfull!");
    // } else {
    //     Serial.println("esp8266/Arduino CI has failed");
    // }
    // Serial.println("reply was:");
    // Serial.println("==========");
    // Serial.println(line);
    // Serial.println("==========");
    // Serial.println("closing connection");i

}





////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void check_Lock_Assignment_2_Any_Tenant_X4444() { 
    WiFiClientSecure client;
    const char* server = "hw_direct.dev.kryptonarc.com"; // Server from which data is to be fetched
    const char* test_root_ca = \
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

    client.setCACert( test_root_ca );
    Serial.println("\nStarting connection to server...");
    int conn = client.connect(server, 443);

    Serial.println("HTTP - GET!");
    if (!conn)
        Serial.println("Connection failed!");
    else {
        Serial.println("Connected to server!");

        
        // Make a HTTP request:
        client.println("GET /raw_hw_check HTTP/1.1");
        client.println("Host: hw_direct.dev.kryptonarc.com");
        client.println("Connection: close");
        client.println();

        while (client.connected()) {
            String line = client.readStringUntil('\n');
            if (line == "\r") {
                Serial.println("headers received");
                break;
            }
        }
        // if there are incoming bytes available
        // from the server, read them and print them:
        while (client.available()) {
            char c = client.read();
            Serial.write(c);
        }

        

        client.stop();
    }


}

