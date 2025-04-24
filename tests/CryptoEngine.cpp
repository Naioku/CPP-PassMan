#include "CryptoEngine.h"

#include "gtest/gtest.h"

TEST(CryptoEngineTestSuite, Encrypt)
{
    CryptoEngine engine;
    const std::string plaintext = "secret";
    const std::string key = "supersecure";

    const std::string encrypted = engine.encrypt(plaintext, key);

    EXPECT_NE(encrypted, plaintext);
}

TEST(CryptoEngineTestSuite, EncryptAndDecrypt)
{
    CryptoEngine engine;
    const std::string plaintext = "secret";
    const std::string key = "supersecure";

    const std::string encrypted = engine.encrypt(plaintext, key);
    const std::string decrypted = engine.decrypt(encrypted, key);

    EXPECT_EQ(decrypted, plaintext);
}