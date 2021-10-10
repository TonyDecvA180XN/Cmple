#include "gtest/gtest.h"
#include <cstdlib>

TEST(DemoTests, Test2)
{
    auto status = std::system("Cmple.exe input=Test_2_Input to_compile=Test_output_2");
    EXPECT_EQ(status, 0);
    
}