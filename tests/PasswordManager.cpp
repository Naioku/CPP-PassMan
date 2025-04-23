#include "PasswordEntry.h"
#include "PasswordManager.h"

#include "Utils.h"
#include "gtest/gtest.h"

class PasswordManagerFixture : public testing::Test
{
protected:
    std::unique_ptr<PasswordManager> manager = std::make_unique<PasswordManager>();

    void SetUp() override
    {
        manager->addEntry({
            "Gmail1",
            "John1",
            "pass1234",
            std::nullopt
        });

        manager->addEntry({
            "Gmail2",
            "John2",
            "pass1234",
            std::nullopt
        });

        manager->addEntry({
            "Gmail3",
            "John3",
            "pass1234",
            std::nullopt
        });
    }
};

TEST_F(PasswordManagerFixture, Add)
{
    const PasswordEntry entry
    {
        "Gmail4",
        "John4",
        "pass1234",
        std::nullopt
    };

    manager->addEntry(entry);

    const std::map<std::string, PasswordEntry> entries = manager->getEntries();
    ASSERT_EQ(entries.size(), 4);

    auto& [name, login, password, notes] = entries.at(entry.name);
    EXPECT_EQ(name, entry.name);
    EXPECT_EQ(login, entry.login);
    EXPECT_EQ(password, entry.password);
    EXPECT_EQ(notes, entry.notes);
}

TEST_F(PasswordManagerFixture, AddDuplicate)
{
    const PasswordEntry entry
    {
        "Gmail1",
        "John",
        "pass1234",
        std::nullopt
    };

    EXPECT_THROW(manager->addEntry(entry), std::invalid_argument);
}

TEST_F(PasswordManagerFixture, Remove)
{
    const size_t prevSize = manager->getEntries().size();

    manager->removeEntry("Gmail1");
    EXPECT_EQ(manager->getEntries().size(), prevSize - 1);
}

TEST_F(PasswordManagerFixture, RemoveNonExisting)
{
    EXPECT_THROW(manager->removeEntry("Non existing entry"), std::invalid_argument);
}

TEST_F(PasswordManagerFixture, FilteringByNameCaseSensitive)
{
    const std::vector<PasswordEntry> entries = manager->getEntries("Gma");
    ASSERT_EQ(entries.size(), 3);

    for (const auto& entry : entries)
    {
        EXPECT_TRUE(Utils::isSubsting(entry.name, "Gma"));
    }
}

TEST_F(PasswordManagerFixture, FilteringByNameCaseInsensitive)
{
    const std::vector<PasswordEntry> entries = manager->getEntries("gmail");
    ASSERT_EQ(entries.size(), 3);

    for (const auto& entry : entries)
    {
        EXPECT_TRUE(Utils::isSubsting(entry.name, "Gmail"));
    }
}
