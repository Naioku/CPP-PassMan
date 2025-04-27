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

TEST(IntegrationTestSuiteStorage, FileOverriding)
{
    const std::string filePath = "test_output.dat";
    const std::string password = "key123";

    const Storage storage{std::make_shared<CryptoEngine>(), filePath};

    if (std::filesystem::exists(filePath))
    {
        std::filesystem::remove(filePath);
    }

    PasswordEntry passwordEntry1{
        "gmail",
        "john",
        "pass",
        "note"
    };

    const std::map<std::string, PasswordEntry> savedEntries1 = {
        {
            passwordEntry1.name,
            passwordEntry1
        }
    };

    storage.saveToFile(savedEntries1, password);
    ASSERT_TRUE(std::filesystem::exists(filePath));

    PasswordEntry passwordEntry2{
        "gmail2",
        "john2",
        "pass2",
        "note2"
    };

    const std::map<std::string, PasswordEntry> savedEntries2 = {
        {
            passwordEntry2.name,
            passwordEntry2
        }
    };

    storage.saveToFile(savedEntries2, password);
    ASSERT_TRUE(std::filesystem::exists(filePath));

    const std::map<std::string, PasswordEntry> loadedEntries = storage.loadFromFile(password);
    const PasswordEntry& loadedEntry = loadedEntries.at(passwordEntry2.name);
    EXPECT_EQ(loadedEntry.name, passwordEntry2.name);
}
