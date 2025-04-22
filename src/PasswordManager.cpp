#include "PasswordManager.h"

#include <stdexcept>

void PasswordManager::addEntry(const PasswordEntry& entry)
{
    if (auto [it, entryAdded] = entries.emplace(entry.name, entry); !entryAdded)
    {
        throw std::invalid_argument("Entry already exists");
    }
}

void PasswordManager::removeEntry(const std::string& name)
{
    if (const size_t elementsQuantity = entries.erase(name); elementsQuantity == 0)
    {
        throw std::invalid_argument("Entry not found");
    }
}
