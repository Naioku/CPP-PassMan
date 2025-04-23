#include "Utils.h"

#include "gtest/gtest.h"

TEST(UtilsTestSuite, ToLower)
{
    const std::string inStr = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const std::string outStr = Utils::toLower(inStr);
    EXPECT_EQ(outStr, "abcdefghijklmnopqrstuvwxyz");
}

TEST(UtilsTestSuite, ToLowerPolishChars)
{
    const std::string inStr = "ZAŻÓŁĆ GĘŚLĄ JAŹŃ";
    const std::string outStr = Utils::toLower(inStr);
    EXPECT_EQ(outStr, "zażółć gęślą jaźń");
}

TEST(UtilsTestSuite, IsSubstringCaseSensitive)
{
    const std::string str = "AbCD";
    const std::string prefix = "bC";

    EXPECT_TRUE(Utils::isSubsting(str, prefix));
}

TEST(UtilsTestSuite, IsSubstringCaseInensitive)
{
    const std::string str = "AbCD";
    const std::string prefix = "bc";

    EXPECT_TRUE(Utils::isSubsting(str, prefix, false));
}