#ifndef LED_ACTIONS_HPP
#define LED_ACTIONS_HPP

#include "iostream"
#include "string.h"
#include "modules/system_structs.hpp"
#include "modules/e2prom_works.hpp"
#include "modules/servo.hpp"
#include "modules/led_works.hpp"

// LED: 
//    Blue: (orange)
//          Flashing slow: 
//                Bluetooth - Not connected - attemping to connect
//          Solid: 
//                Bluetooth - Connected
//          Flashing fast: 
//                Bluetooth - Disconnected - trying to reconnect
//    Green:
//          Flashing Slow:
//                WiFi - Not connected - attemping to connect
//          Solid: 
//                WiFi - Connected
//    Red:
//          Fast flashing - limited to 10x times (with Solid Blue)
//                Data receving from Cloud "0x1"

void turns_off_all_led() {
      software_parameters_variables.global_red_flashing_on = false ;
      software_parameters_variables.global_blue_flashing_on = false ;
      software_parameters_variables.global_green_flashing_on = false ;
}

void led_initialization () {
      pinMode ( software_parameters_fixed.LED_PIN_RED, OUTPUT );
      pinMode ( software_parameters_fixed.LED_PIN_BLUE, OUTPUT );
      pinMode ( software_parameters_fixed.LED_PIN_GREEN, OUTPUT );
}

void led_action_startup() {
      digitalWrite(software_parameters_fixed.LED_PIN_RED, HIGH);
      digitalWrite(software_parameters_fixed.LED_PIN_GREEN, HIGH);
      digitalWrite(software_parameters_fixed.LED_PIN_BLUE, HIGH);  // orange
}

bool led_static_action( const char* new_status, const char* led_static_x_action ) {

      int led_pin = 0;
      // Pin selection
      if ( strcmp( new_status, "red" ) == 0 ) { 
            led_pin = software_parameters_fixed.LED_PIN_RED ;
      } else if ( strcmp( new_status, "green" ) == 0 ) { 
            led_pin = software_parameters_fixed.LED_PIN_GREEN ;
      } else if ( strcmp( new_status, "blue" ) == 0 ) { 
            led_pin = software_parameters_fixed.LED_PIN_BLUE ;
      } else {
            Serial.println(">>>   led pin failed ");
            return false;      
      }
      
      // Action selection
      if ( strcmp( led_static_x_action, "on" ) == 0 ) { 
            digitalWrite(led_pin, LOW);
      } else if ( strcmp( led_static_x_action, "off" ) == 0 ) { 
            digitalWrite(led_pin, HIGH);
      } else {
            Serial.println(">>>   led color failed ");
            return false;      
      }
      return true;   
}

void flashing_led_green( const char* flashing_action = "continue" , const char* flashing_speed = "continue" , const bool over_write_others = false , int flash_counter = -1 , bool leave_on_after_flashing = false) {

      // flashing counter
      if ( flash_counter != -1 && software_parameters_variables.global_green_flashing_target_counter == -1 ){
            // counter setup - incoming counter value - counter no already set
            software_parameters_variables.global_green_flashing_target_counter = flash_counter;
            software_parameters_variables.global_green_flashing_current_counter = 0 ;
            software_parameters_variables.global_green_leave_on_after_flashing = leave_on_after_flashing ;

      } else if ( software_parameters_variables.global_green_flashing_target_counter == -1 ){
            // pass - no counter set - pass
            
      } else if ( software_parameters_variables.global_green_flashing_target_counter != -1 &&  
                  software_parameters_variables.global_green_flashing_current_counter >= software_parameters_variables.global_green_flashing_target_counter ){
            // counter reached - stop flashing 
            software_parameters_variables.global_green_flashing_target_counter = -1 ;
            software_parameters_variables.global_green_flashing_current_counter = -1 ;
            // software_parameters_variables.global_green_flashing_on = false ;
            
            if ( software_parameters_variables.global_green_leave_on_after_flashing ) {
                  // turns on after flashing
                  flashing_action = "on" ;
                  flashing_speed = "fix_light_on";
                  software_parameters_variables.global_green_leave_on_after_flashing = false;
            } else {
                  // turns off after flashing
                  software_parameters_variables.global_green_flashing_on = false ;
            }
      }
      
      ///// ///// ///// ///// ///// ///// ///// ///// /////  ///// 
      // Overwriting other flashing
      if(  strcmp( flashing_speed, "very_fast_flashing" ) == 0  ){ 
            software_parameters_variables.global_green_flashing_on_delay = software_parameters_variables.global_very_fast_flashing_on_delay;
            software_parameters_variables.global_green_flashing_off_delay = software_parameters_variables.global_very_fast_flashing_off_delay;

      } else if(  strcmp( flashing_speed, "fast_flashing" ) == 0  ){ 
            software_parameters_variables.global_green_flashing_on_delay = software_parameters_variables.global_fast_flashing_on_delay;
            software_parameters_variables.global_green_flashing_off_delay = software_parameters_variables.global_fast_flashing_off_delay;

      } else if(  strcmp( flashing_speed, "normal_flashing" ) == 0  ){ 
            software_parameters_variables.global_green_flashing_on_delay = software_parameters_variables.global_normal_flashing_on_delay;
            software_parameters_variables.global_green_flashing_off_delay = software_parameters_variables.global_normal_flashing_off_delay;
    
      } else if(  strcmp( flashing_speed, "slow_flashing" ) == 0  ){ 
            software_parameters_variables.global_green_flashing_on_delay = software_parameters_variables.global_slow_flashing_on_delay;
            software_parameters_variables.global_green_flashing_off_delay = software_parameters_variables.global_slow_flashing_off_delay;

      } else if(  strcmp( flashing_speed, "very_slow_flashing" ) == 0  ){ 
            software_parameters_variables.global_green_flashing_on_delay = software_parameters_variables.global_very_slow_flashing_on_delay;
            software_parameters_variables.global_green_flashing_off_delay = software_parameters_variables.global_very_slow_flashing_off_delay;

      } else if(  strcmp( flashing_speed, "fix_light_on" ) == 0  ){ 
            software_parameters_variables.global_green_flashing_on_delay = software_parameters_variables.global_fix_flashing_on_delay;
            software_parameters_variables.global_green_flashing_off_delay = software_parameters_variables.global_fix_flashing_off_delay;
      
      } else { 
            // continue 
      }

      ///// ///// ///// ///// ///// ///// ///// ///// /////  ///// 
      // Overwriting other flashing
      if( over_write_others ){ turns_off_all_led(); }
      
      ///// ///// ///// ///// ///// ///// ///// ///// /////  ///// 
      // time diff
      int tmp_diff = software_parameters_variables.global_current_millis - software_parameters_variables.global_green_flashing_previous_millis_timer ;

      ///// ///// ///// ///// ///// ///// ///// ///// /////  ///// 
      // Action selection
      if ( strcmp( flashing_action, "on" ) == 0 ) { 
            software_parameters_variables.global_green_flashing_on = true ;
      } else if ( strcmp( flashing_action, "off" ) == 0 ) { 
            software_parameters_variables.global_green_flashing_on = false ;
      } else {
            // match continue
      }
      
      ///// ///// ///// ///// ///// ///// ///// ///// /////  ///// 
      // LED action 
      if ( !software_parameters_variables.global_green_flashing_on ) {
            // turn off everything
            led_static_action( "green", "off" );

      } else if ( software_parameters_variables.global_green_flashing_temp_var && tmp_diff > software_parameters_variables.global_green_flashing_off_delay ) { // delay to stay off
            software_parameters_variables.global_green_flashing_temp_var = false ;
            software_parameters_variables.global_green_flashing_previous_millis_timer = software_parameters_variables.global_current_millis ;
            led_static_action( "green", "on" );
           
            // flashing counter - counting
            if ( software_parameters_variables.global_green_flashing_current_counter < software_parameters_variables.global_green_flashing_target_counter ){ software_parameters_variables.global_green_flashing_current_counter++ ; }

      } else if ( !software_parameters_variables.global_green_flashing_temp_var && tmp_diff > software_parameters_variables.global_green_flashing_on_delay ) { // delay to stay on
            software_parameters_variables.global_green_flashing_temp_var = true ;
            software_parameters_variables.global_green_flashing_previous_millis_timer = software_parameters_variables.global_current_millis ;
            led_static_action( "green", "off" );

            // flashing counter - counting
            if ( software_parameters_variables.global_green_flashing_current_counter < software_parameters_variables.global_green_flashing_target_counter ){ software_parameters_variables.global_green_flashing_current_counter++ ; }
      } else {
            // waiting not action taken
      }
}

void flashing_led_blue( const char* flashing_action = "continue" , const char* flashing_speed = "continue" , const bool over_write_others = false , int flash_counter = -1 , bool leave_on_after_flashing = false) {
      
      ///// ///// ///// ///// ///// ///// ///// ///// /////  ///// 
      // flashing counter
      if ( flash_counter != -1 && software_parameters_variables.global_blue_flashing_target_counter == -1 ){
            // counter setup - incoming counter value - counter no already set
            software_parameters_variables.global_blue_flashing_target_counter = flash_counter;
            software_parameters_variables.global_blue_flashing_current_counter = 0 ;
            software_parameters_variables.global_blue_leave_on_after_flashing = leave_on_after_flashing ;

      } else if ( software_parameters_variables.global_blue_flashing_target_counter == -1 ){
            // pass - no counter set - pass
            
      } else if ( software_parameters_variables.global_blue_flashing_target_counter != -1 &&  
                  software_parameters_variables.global_blue_flashing_current_counter >= software_parameters_variables.global_blue_flashing_target_counter ){
            // counter reached - stop flashing 
            software_parameters_variables.global_blue_flashing_target_counter = -1 ;
            software_parameters_variables.global_blue_flashing_current_counter = -1 ;
            // software_parameters_variables.global_blue_flashing_on = false ;
            
            if ( software_parameters_variables.global_blue_leave_on_after_flashing ) {
                  // turns on after flashing
                  flashing_action = "on" ;
                  flashing_speed = "fix_light_on";
                  software_parameters_variables.global_blue_leave_on_after_flashing = false;
            } else {
                  // turns off after flashing
                  software_parameters_variables.global_blue_flashing_on = false ;
            }
      }

      ///// ///// ///// ///// ///// ///// ///// ///// /////  ///// 
      // Overwriting other flashing
      if(  strcmp( flashing_speed, "very_fast_flashing" ) == 0  ){ 
            software_parameters_variables.global_blue_flashing_on_delay = software_parameters_variables.global_very_fast_flashing_on_delay;
            software_parameters_variables.global_blue_flashing_off_delay = software_parameters_variables.global_very_fast_flashing_off_delay;

      } else if(  strcmp( flashing_speed, "fast_flashing" ) == 0  ){ 
            software_parameters_variables.global_blue_flashing_on_delay = software_parameters_variables.global_fast_flashing_on_delay;
            software_parameters_variables.global_blue_flashing_off_delay = software_parameters_variables.global_fast_flashing_off_delay;

      } else if(  strcmp( flashing_speed, "normal_flashing" ) == 0  ){ 
            software_parameters_variables.global_blue_flashing_on_delay = software_parameters_variables.global_normal_flashing_on_delay;
            software_parameters_variables.global_blue_flashing_off_delay = software_parameters_variables.global_normal_flashing_off_delay;
    
      } else if(  strcmp( flashing_speed, "slow_flashing" ) == 0  ){ 
            software_parameters_variables.global_blue_flashing_on_delay = software_parameters_variables.global_slow_flashing_on_delay;
            software_parameters_variables.global_blue_flashing_off_delay = software_parameters_variables.global_slow_flashing_off_delay;

      } else if(  strcmp( flashing_speed, "very_slow_flashing" ) == 0  ){ 
            software_parameters_variables.global_blue_flashing_on_delay = software_parameters_variables.global_very_slow_flashing_on_delay;
            software_parameters_variables.global_blue_flashing_off_delay = software_parameters_variables.global_very_slow_flashing_off_delay;

      } else if(  strcmp( flashing_speed, "fix_light_on" ) == 0  ){ 
            software_parameters_variables.global_blue_flashing_on_delay = software_parameters_variables.global_fix_flashing_on_delay;
            software_parameters_variables.global_blue_flashing_off_delay = software_parameters_variables.global_fix_flashing_off_delay;

      } else { 
            // continue 
      }

      ///// ///// ///// ///// ///// ///// ///// ///// /////  ///// 
      // Overwriting other flashing
      if( over_write_others ){ turns_off_all_led(); }
      
      ///// ///// ///// ///// ///// ///// ///// ///// /////  ///// 
      // time diff
      int tmp_diff = software_parameters_variables.global_current_millis - software_parameters_variables.global_blue_flashing_previous_millis_timer ;

      ///// ///// ///// ///// ///// ///// ///// ///// /////  ///// 
      // Action selection
      if ( strcmp( flashing_action, "on" ) == 0 ) { 
            software_parameters_variables.global_blue_flashing_on = true ;
      } else if ( strcmp( flashing_action, "off" ) == 0 ) { 
            software_parameters_variables.global_blue_flashing_on = false ;
      } else {
            // match continue
      }


      ///// ///// ///// ///// ///// ///// ///// ///// /////  ///// 
      // LED action 
      if ( !software_parameters_variables.global_blue_flashing_on ) {
            // turn off everything
            led_static_action( "blue", "off" );

      } else if ( software_parameters_variables.global_blue_flashing_temp_var && tmp_diff > software_parameters_variables.global_blue_flashing_off_delay ) { // delay to stay off
            software_parameters_variables.global_blue_flashing_temp_var = false ;
            software_parameters_variables.global_blue_flashing_previous_millis_timer = software_parameters_variables.global_current_millis ;
            led_static_action( "blue", "on" );

            // flashing counter - counting
            if ( software_parameters_variables.global_blue_flashing_current_counter < software_parameters_variables.global_blue_flashing_target_counter ){ software_parameters_variables.global_blue_flashing_current_counter++ ; }

      } else if ( !software_parameters_variables.global_blue_flashing_temp_var && tmp_diff > software_parameters_variables.global_blue_flashing_on_delay ) { // delay to stay on
            software_parameters_variables.global_blue_flashing_temp_var = true ;
            software_parameters_variables.global_blue_flashing_previous_millis_timer = software_parameters_variables.global_current_millis ;
            led_static_action( "blue", "off" );

            // flashing counter - counting
            if ( software_parameters_variables.global_blue_flashing_current_counter < software_parameters_variables.global_blue_flashing_target_counter ){ software_parameters_variables.global_blue_flashing_current_counter++ ; }
            
      } else {
            // waiting not action taken
      }
}

void flashing_led_red( const char* flashing_action = "continue" , const char* flashing_speed = "continue" , const bool over_write_others = false , int flash_counter = -1 , bool leave_on_after_flashing = false) {
      
      ///// ///// ///// ///// ///// ///// ///// ///// /////  ///// 
      // flashing counter
      if ( flash_counter != -1 && software_parameters_variables.global_red_flashing_target_counter == -1 ){
            // counter setup - incoming counter value - counter no already set
            software_parameters_variables.global_red_flashing_target_counter = flash_counter;
            software_parameters_variables.global_red_flashing_current_counter = 0 ;
            software_parameters_variables.global_red_leave_on_after_flashing = leave_on_after_flashing ;

      } else if ( software_parameters_variables.global_red_flashing_target_counter == -1 ){
            // pass - no counter set - pass
            
      } else if ( software_parameters_variables.global_red_flashing_target_counter != -1 &&  
                  software_parameters_variables.global_red_flashing_current_counter >= software_parameters_variables.global_red_flashing_target_counter ){
            // counter reached - stop flashing 
            software_parameters_variables.global_red_flashing_target_counter = -1 ;
            software_parameters_variables.global_red_flashing_current_counter = -1 ;

            if ( software_parameters_variables.global_red_leave_on_after_flashing ) {
                  // turns on after flashing
                  flashing_action = "on" ;
                  flashing_speed = "fix_light_on";
                  software_parameters_variables.global_red_leave_on_after_flashing = false;
            } else {
                  // turns off after flashing
                  software_parameters_variables.global_red_flashing_on = false ;
            }
      }

      ///// ///// ///// ///// ///// ///// ///// ///// /////  ///// 
      // Overwriting other flashing
      if(  strcmp( flashing_speed, "very_fast_flashing" ) == 0  ){ 
            software_parameters_variables.global_red_flashing_on_delay = software_parameters_variables.global_very_fast_flashing_on_delay;
            software_parameters_variables.global_red_flashing_off_delay = software_parameters_variables.global_very_fast_flashing_off_delay;

      } else if(  strcmp( flashing_speed, "fast_flashing" ) == 0  ){ 
            software_parameters_variables.global_red_flashing_on_delay = software_parameters_variables.global_fast_flashing_on_delay;
            software_parameters_variables.global_red_flashing_off_delay = software_parameters_variables.global_fast_flashing_off_delay;

      } else if(  strcmp( flashing_speed, "normal_flashing" ) == 0  ){ 
            software_parameters_variables.global_red_flashing_on_delay = software_parameters_variables.global_normal_flashing_on_delay;
            software_parameters_variables.global_red_flashing_off_delay = software_parameters_variables.global_normal_flashing_off_delay;
    
      } else if(  strcmp( flashing_speed, "slow_flashing" ) == 0  ){ 
            software_parameters_variables.global_red_flashing_on_delay = software_parameters_variables.global_slow_flashing_on_delay;
            software_parameters_variables.global_red_flashing_off_delay = software_parameters_variables.global_slow_flashing_off_delay;

      } else if(  strcmp( flashing_speed, "very_slow_flashing" ) == 0  ){ 
            software_parameters_variables.global_red_flashing_on_delay = software_parameters_variables.global_very_slow_flashing_on_delay;
            software_parameters_variables.global_red_flashing_off_delay = software_parameters_variables.global_very_slow_flashing_off_delay;

      } else if(  strcmp( flashing_speed, "fix_light_on" ) == 0  ){ 
            software_parameters_variables.global_red_flashing_on_delay = software_parameters_variables.global_fix_flashing_on_delay;
            software_parameters_variables.global_red_flashing_off_delay = software_parameters_variables.global_fix_flashing_off_delay;
            
      } else { 
            // continue 
      }

      ///// ///// ///// ///// ///// ///// ///// ///// /////  ///// 
      // Overwriting other flashing
      if( over_write_others ){ turns_off_all_led(); }
      
      ///// ///// ///// ///// ///// ///// ///// ///// /////  ///// 
      // time diff
      int tmp_diff = software_parameters_variables.global_current_millis - software_parameters_variables.global_red_flashing_previous_millis_timer ;

      ///// ///// ///// ///// ///// ///// ///// ///// /////  ///// 
      // Action selection
      if ( strcmp( flashing_action, "on" ) == 0 ) { 
            software_parameters_variables.global_red_flashing_on = true ;
      } else if ( strcmp( flashing_action, "off" ) == 0 ) { 
            software_parameters_variables.global_red_flashing_on = false ;
      } else {
            // match continue
      }


      ///// ///// ///// ///// ///// ///// ///// ///// /////  ///// 
      // LED action 
      if ( !software_parameters_variables.global_red_flashing_on ) {
            // turn off everything
            led_static_action( "red", "off" );

      } else if ( software_parameters_variables.global_red_flashing_temp_var && tmp_diff > software_parameters_variables.global_red_flashing_off_delay ) { // delay to stay off
            software_parameters_variables.global_red_flashing_temp_var = false ;
            software_parameters_variables.global_red_flashing_previous_millis_timer = software_parameters_variables.global_current_millis ;
            led_static_action( "red", "on" );

            // flashing counter - counting
            if ( software_parameters_variables.global_red_flashing_current_counter < software_parameters_variables.global_red_flashing_target_counter ){ software_parameters_variables.global_red_flashing_current_counter++ ; }

      } else if ( !software_parameters_variables.global_red_flashing_temp_var && tmp_diff > software_parameters_variables.global_red_flashing_on_delay ) { // delay to stay on
            software_parameters_variables.global_red_flashing_temp_var = true ;
            software_parameters_variables.global_red_flashing_previous_millis_timer = software_parameters_variables.global_current_millis ;
            led_static_action( "red", "off" );

            // flashing counter - counting
            if ( software_parameters_variables.global_red_flashing_current_counter < software_parameters_variables.global_red_flashing_target_counter ){ software_parameters_variables.global_red_flashing_current_counter++ ; }

      } else {
            // waiting not action taken
      }
}


void led_global_action() {
      flashing_led_green();
      flashing_led_blue();
      flashing_led_red();
}




#endif
