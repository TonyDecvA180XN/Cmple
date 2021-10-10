#include "gtest/gtest.h"
#include <cstdlib>

TEST(DemoTests, Test6)
{
    auto status = std::system("Cmple.exe input=Test_6_Input to_compile=Test_output_6");
    EXPECT_EQ(status, 0);
    
}