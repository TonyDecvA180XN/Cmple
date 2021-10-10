#include "gtest/gtest.h"

namespace FeatureTestSpace1
{
    TEST(FeatureTestCategory1, MustPass)
    {
        EXPECT_EQ(30, 30);
        EXPECT_EQ(6, 6);
    }
    TEST(FeatureTestCategory1, MustFail)
    {
        EXPECT_EQ(30, 10);
        EXPECT_EQ(6, 4);
    }

}
