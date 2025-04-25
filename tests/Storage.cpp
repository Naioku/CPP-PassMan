#include "Storage.h"

#include <filesystem>
#include <fstream>

#include "CryptoEngine.h"
#include "gmock/gmock-function-mocker.h"
#include "gtest/gtest.h"

class MockCryptoEngine final : public ICryptoEngine
{
public:
    MOCK_METHOD(std::string, encrypt, (const std::string& plaintext, const std::string& password), (const, override));
    MOCK_METHOD(std::string, decrypt, (const std::string& ciphertext, const std::string& password), (const, override));
};

TEST(IntegrationTestSuiteStorage, SaveAndLoad)
{
    const std::string filePath = "test_output.dat";
    const std::string password = "key123";

    const Storage storage{std::make_shared<CryptoEngine>(), filePath};

    if (std::filesystem::exists(filePath))
    {
        std::filesystem::remove(filePath);
    }

    PasswordEntry passwordEntry{
        "gmail",
        "john",
        "pass",
        "note"
    };

    const std::map<std::string, PasswordEntry> savedEntries = {
        {
            passwordEntry.name,
            passwordEntry
        }
    };

    storage.saveToFile(savedEntries, password);

    ASSERT_TRUE(std::filesystem::exists(filePath));

    const std::map<std::string, PasswordEntry> loadedEntries = storage.loadFromFile(password);
    const PasswordEntry& loadedEntry = loadedEntries.at(passwordEntry.name);
    EXPECT_EQ(loadedEntry.name, passwordEntry.name);

    std::filesystem::remove(filePath);
}
