#ifndef NTP_HPP
#define NTP_HPP

#include "NTPClient.h"
#include "WiFiUdp.h"


const char *ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 0; // Set your GMT offset in seconds
const int daylightOffset_sec = 3600; // Set your daylight saving time offset in seconds



WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, ntpServer, gmtOffset_sec, daylightOffset_sec);


void ntp_initialization () {
  // Initialize NTP client
  timeClient.begin();
}


void ntp_process( ) {
  // Get the current time from the NTP server
  timeClient.update();

  // Print the formatted time
  Serial.println(timeClient.getFormattedTime());

  delay(1000); // Wait for 1 second before updating the time again
}

#endif
