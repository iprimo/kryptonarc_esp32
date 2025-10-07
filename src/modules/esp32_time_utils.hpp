#ifndef ESP32_TIME_UTILS_HPP
#define ESP32_TIME_UTILS_HPP



    // if ( !software_parameters_variables.timeStampSetUsingFristTimeStamp ){
    //   Serial.println("999999 set first time  >>>  ");
    //   // Setting time stamp using incoming data time stamp
    //   const char* found_ts = find_values_between_substringsV5(receivingString, "timeStamp:", "::");
    //   if (found_ts && strlen(found_ts) > 0) {
    //       strcpy(software_parameters_variables.incoming_data_time_stamp, found_ts);
    //       set_esp32_time_from_string(software_parameters_variables.incoming_data_time_stamp);
    //       software_parameters_variables.timeStampSetUsingFristTimeStamp = true;
    //   } else {
    //       Serial.println("No valid timestamp found in incoming string!");
    //   }
    // }
    // Serial.println("999999 read time  >>>  ");
    // char timebuf[32];
    // get_esp32_time_string(timebuf, sizeof(timebuf));
    // Serial.println(timebuf); // Prints: 2025-09-10T20:53:19Z






#include <sys/time.h>
#include <time.h>
#include <string.h>

// Set ESP32 system time from ISO 8601 timestamp with milliseconds and 'Z'
// Improved: robust to invalid input, sets default time if parsing fails
static inline void set_esp32_time_from_string(const char* iso8601) {
    struct tm tm;
    memset(&tm, 0, sizeof(tm));
    // Remove spaces in time if present (e.g., "20 :53:19" -> "20:53:19")
    char clean[32];
    int j = 0;
    for (int i = 0; iso8601 && iso8601[i] && j < 31; ++i) {
        if (!(iso8601[i] == ' ' && (i > 0 && iso8601[i-1] == 'T'))) {
            clean[j++] = iso8601[i];
        }
    }
    clean[j] = '\0';
    // Try to parse up to seconds (ignore milliseconds and 'Z')
    char* parse_result = strptime(clean, "%Y-%m-%dT%H:%M:%S", &tm);
    if (!parse_result) {
        // Set default time: 2020-02-20 20:20:20
        tm.tm_year = 2020 - 1900;
        tm.tm_mon = 1; // February (0-based)
        tm.tm_mday = 20;
        tm.tm_hour = 20;
        tm.tm_min = 20;
        tm.tm_sec = 20;
    }
    time_t t = mktime(&tm);
    struct timeval now = { .tv_sec = t, .tv_usec = 0 };
    settimeofday(&now, NULL);
}

// Get ESP32 system time as ISO 8601 string (UTC)
static inline void get_esp32_time_string(char* out, size_t out_size) {
    struct timeval now;
    gettimeofday(&now, NULL);
    struct tm *tm_info = gmtime(&now.tv_sec);
    strftime(out, out_size, "%Y-%m-%dT%H:%M:%SZ", tm_info);
}


// // Returns pointer to static buffer with ISO 8601 time string (UTC)
// static inline const char* get_esp32_time_string() {
//     static char out[32];
//     struct timeval now;
//     gettimeofday(&now, NULL);
//     struct tm *tm_info = gmtime(&now.tv_sec);
//     if (tm_info) {
//         strftime(out, sizeof(out), "%Y-%m-%dT%H:%M:%SZ", tm_info);
//     } else {
//         strncpy(out, "1970-01-01T00:00:00Z", sizeof(out));
//         out[sizeof(out)-1] = '\0';
//     }
//     return out;
// }

#endif // ESP32_TIME_UTILS_HPP
