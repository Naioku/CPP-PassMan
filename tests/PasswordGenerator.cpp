#include "PasswordGenerator.h"

#include "gtest/gtest.h"


bool containsLower(const std::string& str) {
    return std::any_of(str.begin(), str.end(), ::islower);
}

bool containsUpper(const std::string& str) {
    return std::any_of(str.begin(), str.end(), ::isupper);
}

bool containsDigit(const std::string& str) {
    return std::any_of(str.begin(), str.end(), ::isdigit);
}

bool containsSymbol(const std::string& str) {
    return std::any_of(str.begin(), str.end(), [](char c) {
        return std::ispunct(static_cast<unsigned char>(c));
    });
}

TEST(PasswordGeneratorTestSuite, WhenCreateObjWithPassSizeLessThan4ShouldThrowException)
{
    EXPECT_THROW(PasswordGenerator passwordGenerator{3}, std::invalid_argument);
}

TEST(PasswordGeneratorTestSuite, GivenGeneratorWhenPassGeneratedShouldMeetRequirements)
{
    const PasswordGenerator generator{20};
    const std::string password = generator.generate();

    EXPECT_EQ(password.length(), 20);
    EXPECT_TRUE(containsLower(password));
    EXPECT_TRUE(containsUpper(password));
    EXPECT_TRUE(containsDigit(password));
    EXPECT_TRUE(containsSymbol(password));
}
