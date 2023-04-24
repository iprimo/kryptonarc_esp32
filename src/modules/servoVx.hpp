// Recommended PWM GPIO pins on the ESP32 include 2,4,12-19,21-23,25-27,32-33 

#include "ESP32PWM.h"

const int servoPin = 18; // The pin the servo is connected to
const int minPulseWidth = 500; // The minimum pulse width for the servo (in microseconds)
const int maxPulseWidth = 2400; // The maximum pulse width for the servo (in microseconds)
const int servoFrequency = 50; // The PWM frequency for the servo (in Hertz)


void servoInitiateV1() {
  // Allocate the first timer for PWM output
  ESP32PWM::allocateTimer(0);
  
  // Set the PWM frequency for the servo
  ESP32PWM::setFrequency(servoPin, servoFrequency);
  
  // Attach the servo to the PWM output pin
  ESP32PWM::attach(servoPin, minPulseWidth, maxPulseWidth);
}


void servoWorksDriveV1( int target_value  ) {
	ESP32PWM::write(servoPin, target_value );
}
