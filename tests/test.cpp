#include <gtest/gtest.h>

#include "test_target.hpp"

TEST(Basic, GTest_test)
{
  EXPECT_EQ(3, testFn());
}