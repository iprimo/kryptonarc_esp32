#pragma once
#include <Arduino.h>

void setBuiltInDiode( int state ) {
  pinMode( 18, OUTPUT );
  digitalWrite( 18, state );
}