#include "gtest/gtest.h"
#include <cstdlib>

TEST(DemoTests, Test3)
{
    auto status = std::system("Cmple.exe input=Test_3_Input to_compile=Test_output_3");
    EXPECT_EQ(status, 0);
    
}