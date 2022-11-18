#include <add.hpp>
#include <gtest/gtest.h>

TEST(add, test_add_adds_two_values) {
    int expected = 2 + 3;
    int actual = add (2, 3);

    ASSERT_EQ(expected, actual);
}