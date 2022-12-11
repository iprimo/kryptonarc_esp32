#include "Arduino.h"
#include "system_structs.cpp"
#include "pitches.hpp"

extern SYSTEM_GLOBAL_VAR system_global_variables;

const int led_default_off = HIGH;    // the OFF state of LED
const int led_default_on = LOW;    // the ON state of LED

void notification_reset_all( ) { 
    tone(system_global_variables.buzzerPassive, 0);
    digitalWrite (system_global_variables.ledRed, led_default_off);
    digitalWrite (system_global_variables.ledBlue, led_default_off);
    digitalWrite (system_global_variables.ledGreen, led_default_off);
}

void notification_sound( const char *cNotificationSelector , int sound_repeat ) {
    notification_reset_all();
    if ( cNotificationSelector == "Error_Triple" ){
        int sound_state = LOW; // Helper Local variable
        for (int i = 0; i < (sound_repeat *2 ) ; i++)
        {
            if ( sound_state ){
                sound_state = LOW;
                tone(system_global_variables.buzzerPassive, 200);
            } else {
                sound_state = HIGH;
                tone(system_global_variables.buzzerPassive, 0);
            }
            delay( 100 );
        } 
    } else if ( cNotificationSelector == "Siron___Raising_Error" ){
        for (int i = 0; i < sound_repeat ; i++) {
            for (int i = 200; i <= 800; i++)  // loop from 200 to 800 (frequency)
            {
                tone(system_global_variables.buzzerPassive, i);
                delay(5);
            }
            delay(1000);                      //3 seconds on highest frequency
            for (int i = 800; i >= 200; i--)  // loop from 200 to 800 (frequency)
            {
                tone(system_global_variables.buzzerPassive, i);
                delay(5);
            }
        }
        } else if ( cNotificationSelector == "some_sound" ){
            for (int i = 200; i <= 800; i++)  // loop from 200 to 800 (frequency)
            {
                tone(system_global_variables.buzzerPassive, i);
                delay(2);
            }
            delay(1000);                      //3 seconds on highest frequency
            for (int i = 800; i >= 200; i--)  // loop from 200 to 800 (frequency)
            {
                tone(system_global_variables.buzzerPassive, i);
                delay(2);
            }
    } else {

    }
    notification_reset_all();
}


void notification_light( const char *cNotificationSelector, int flashTimes , int flashSpeed ) {
    notification_reset_all();
    if ( cNotificationSelector == "blueLedFlashing" ) {
        int led_status = LOW; // Local variable to manage flashing
        for (int i = 0; i < (flashTimes*2) ; i++)  // Flashing loop
        {
            if ( led_status ){
                led_status = LOW;
                digitalWrite (system_global_variables.ledBlue, led_status);
            } else {
                led_status = HIGH;
                digitalWrite (system_global_variables.ledBlue, led_status);
            }
            delay( flashSpeed );
            }       
    } else if ( cNotificationSelector == "redLedFlashing" ) {
        int led_status = LOW; // Local variable to manage flashing
        for (int i = 0; i < (flashTimes*2) ; i++)  // Flashing loop
        {
            if ( led_status ){
                led_status = LOW;
                digitalWrite (system_global_variables.ledRed, led_status);
            } else {
                led_status = HIGH;
                digitalWrite (system_global_variables.ledRed, led_status);
            }
            delay( flashSpeed );
            }       
    } else if ( cNotificationSelector == "LedFlashing" ) {
        int led_status = LOW; // Local variable to manage flashing
        for (int i = 0; i < (flashTimes*2) ; i++)  // Flashing loop
        {
            if ( led_status ){
                led_status = LOW;
                digitalWrite (system_global_variables.ledGreen, led_status);
            } else {
                led_status = HIGH;
                digitalWrite (system_global_variables.ledGreen, led_status);
            }
            delay( flashSpeed );
            }       
    } else {

    }
    notification_reset_all();
}

