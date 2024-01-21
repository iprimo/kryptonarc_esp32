#ifndef MD5_HPP
#define MD5_HPP

#include "MD5Builder.h"

String generateMD5Hash(const char* str) {
  MD5Builder md5;
  md5.begin();
  md5.add(str);
  md5.calculate();
  // Serial.println(" ***  ***  ***  ***  *** str *** : ");
  // Serial.print(str);
  // Serial.println(" ***  ***  ***  ***  *** md5.toString() *** : ");
  // Serial.print(md5.toString());
  
  return md5.toString();
}

#endif // MD5_HPP