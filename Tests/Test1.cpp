#include "gtest/gtest.h"
#include <cstdlib>

TEST(DemoTests, Test1)
{
    auto status = std::system("Cmple.exe input=Test_1_Input to_compile=Test_output_1");
    EXPECT_EQ(status, 0);
}