#include "PasswordManager.h"

#include <algorithm>
#include <ranges>
#include <stdexcept>

#include "Utils.h"


std::vector<PasswordEntry> PasswordManager::getEntries(const std::string& name) const
{
    std::vector<PasswordEntry> result;
    for (const auto& [entryName, entry] : entries)
    {
        if (Utils::isSubsting(entryName, name, false))
        {
            result.push_back(entry);
        }
    }

    return result;
}

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

void PasswordManager::changeDataSavingPath(const std::string& path) const
{
    storage->setPath(path);
}

void PasswordManager::saveData(const std::string& password) const
{
    storage->saveToFile(entries, password);
}

void PasswordManager::loadData(const std::string& password)
{
    entries = storage->loadFromFile(password);
}

std::string PasswordManager::generatePassword() const
{
    return passwordGenerator->generate();
}
