#include "gtest/gtest.h"
#include <cstdlib>

TEST(DemoTests, Test4)
{
    auto status = std::system("Cmple.exe input=Test_4_Input to_compile=Test_output_4");
    EXPECT_EQ(status, 0);
    
}