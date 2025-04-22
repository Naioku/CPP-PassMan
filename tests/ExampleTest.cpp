#include "PasswordEntry.h"
#include "PasswordManager.h"
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

    const std::vector<PasswordEntry> entries = manager.getEntries();
    ASSERT_EQ(entries.size(), 1);
    EXPECT_EQ(entries[0].name, entry.name);
    EXPECT_EQ(entries[0].login, entry.login);
    EXPECT_EQ(entries[0].password, entry.password);
    EXPECT_EQ(entries[0].notes, entry.notes);
}
