#include <setBuiltInDiode.hpp>
#include <gtest/gtest.h>

TEST ( setBuiltInDiode , test_setBuiltInDiode_sets_built_in_diode_voltage_to_HIGH_if_HIGH_value_has_been_passed ){
  int expected = HIGH;
  setBuiltInDiode( expected );
  ASSERT_EQ( expected , digitalRead( 18 ) );
}


TEST ( setBuiltInDiode , test_setBuiltInDiode_sets_built_in_diode_voltage_to_LOW_if_LOW_value_has_been_passed ){
  int expected = LOW;
  setBuiltInDiode( expected );
  ASSERT_EQ( expected , digitalRead( 18 ) );
}
