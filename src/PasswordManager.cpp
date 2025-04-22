#include "PasswordManager.h"

void PasswordManager::addEntry(const PasswordEntry& entry)
{
    entries.push_back(entry);
}
