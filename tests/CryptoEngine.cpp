#include "CryptoEngine.h"

#include "gtest/gtest.h"

TEST(CryptoEngineTestSuite, Encrypt)
{
    const CryptoEngine engine;
    const std::string plaintext = "secret";
    const std::string password = "supersecure";

    const std::string encrypted = engine.encrypt(plaintext, password);

    EXPECT_NE(encrypted, plaintext);
}

TEST(CryptoEngineTestSuite, Decrypt)
{
    const CryptoEngine engine;
    const std::string plaintext = "secret";
    const std::string password = "supersecure";

    const std::string encrypted = engine.encrypt(plaintext, password);
    const std::string decrypted = engine.decrypt(encrypted, password);

    EXPECT_EQ(decrypted, plaintext);
}

TEST(CryptoEngineTestSuite, WrongPassword)
{
    const CryptoEngine engine;
    const std::string plaintext = "secret";
    const std::string password = "supersecure";
    const std::string encrypted = engine.encrypt(plaintext, password);
    EXPECT_THROW(engine.decrypt(encrypted, "wrongpassword"), std::runtime_error);
}