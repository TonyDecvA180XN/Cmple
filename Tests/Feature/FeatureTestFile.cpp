#include "gtest/gtest.h"
#include "feature.h"

namespace FeatureTestSpace1
{
    TEST(FeatureTestCategory1, FeatureTestName1)
    {
        EXPECT_EQ(30, feature(5, 6));
        EXPECT_EQ(6, feature(2, 3));
    }
    TEST(FeatureTestCategory1, FeatureTestName2)
    {
        EXPECT_EQ(30, feature(5, 6));
        EXPECT_EQ(6, feature(2, 3));
    }
    TEST(FeatureTestCategory2, FeatureTestName1)
    {
        EXPECT_EQ(30, feature(5, 6));
        EXPECT_EQ(6, feature(2, 3));
    }
    TEST(FeatureTestCategory2, FeatureTestName2)
    {
        EXPECT_EQ(30, feature(5, 6));
        EXPECT_EQ(6, feature(2, 3));
    }

}
namespace FeatureTestSpace2
{
    TEST(FeatureTestCategory, FeatureTestName)
    {
        EXPECT_EQ(30, feature(5, 6));
        EXPECT_EQ(6, feature(2, 3));
    }

}