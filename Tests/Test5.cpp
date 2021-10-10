#include "gtest/gtest.h"
#include <cstdlib>

TEST(DemoTests, Test5)
{
    auto status = std::system("Cmple.exe input=Test_5_Input to_compile=Test_output_5");
    EXPECT_EQ(status, 0);
    
}