#include <multiply.hpp>
#include <gtest/gtest.h>

TEST(multiply, test_multiply_multiplies_two_values) {
  int expected = 5 * 2 ;
  int actual = multiply(5, 2);
  ASSERT_EQ(expected, actual);
}

