#include "PasswordEntry.h"
#include "PasswordManager.h"

#include "Utils.h"
#include "gtest/gtest.h"

TEST(PasswordManagerTestSuite, Add)
{
    PasswordManager manager;

    const PasswordEntry entry
    {
        "Gmail",
        "John",
        "pass1234",
        std::nullopt
    };

    manager.addEntry(entry);

    const std::map<std::string, PasswordEntry> entries = manager.getEntries();
    ASSERT_EQ(entries.size(), 1);

    auto& [name, login, password, notes] = entries.at(entry.name);
    EXPECT_EQ(name, entry.name);
    EXPECT_EQ(login, entry.login);
    EXPECT_EQ(password, entry.password);
    EXPECT_EQ(notes, entry.notes);
}

TEST(PasswordManagerTestSuite, AddDuplicate)
{
    PasswordManager manager;

    const PasswordEntry entry
    {
        "Gmail",
        "John",
        "pass1234",
        std::nullopt
    };

    manager.addEntry(entry);
    EXPECT_THROW(manager.addEntry(entry), std::invalid_argument);
}

TEST(PasswordManagerTestSuite, Remove)
{
    PasswordManager manager;

    const PasswordEntry entry
    {
        "Gmail",
        "John",
        "pass1234",
        std::nullopt
    };

    manager.addEntry(entry);

    ASSERT_EQ(manager.getEntries().size(), 1);

    manager.removeEntry(entry.name);
    EXPECT_EQ(manager.getEntries().size(), 0);
}

TEST(PasswordManagerTestSuite, RemoveNonExisting)
{
    PasswordManager manager;
    EXPECT_THROW(manager.removeEntry("Gmail"), std::invalid_argument);
}

TEST(PasswordManagerTestSuite, FilteringByNameCaseSensitive)
{
    PasswordManager manager;

    manager.addEntry(
    {
        "Gmail",
        "John",
        "pass1234",
        std::nullopt
    });

    manager.addEntry({
        "Gmail2",
        "Name",
        "pass1234",
        std::nullopt
    });

    manager.addEntry({
        "Gmail3",
        "Name",
        "pass1234",
        std::nullopt
    });

    const std::vector<PasswordEntry> entries = manager.getEntries("Gma");
    ASSERT_EQ(entries.size(), 3);

    for (auto entry : entries)
    {
        EXPECT_TRUE(Utils::isSubsting(entry.name, "Gma"));
    }
}

TEST(PasswordManagerTestSuite, FilteringByNameCaseInsensitive)
{
    PasswordManager manager;

    manager.addEntry({
        "Gmail",
        "John",
        "pass1234",
        std::nullopt
    });

    manager.addEntry({
        "Gmail2",
        "Name",
        "pass1234",
        std::nullopt
    });

    manager.addEntry({
        "Gmail3",
        "Name",
        "pass1234",
        std::nullopt
    });

    const std::vector<PasswordEntry> entries = manager.getEntries("gmail");
    ASSERT_EQ(entries.size(), 3);

    for (auto entry : entries)
    {
        EXPECT_TRUE(Utils::isSubsting(entry.name, "Gmail"));
    }
}