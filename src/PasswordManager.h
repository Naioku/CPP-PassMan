#ifndef PASSWORDMANAGER_H
#define PASSWORDMANAGER_H
#include <map>
#include <vector>

#include "PasswordEntry.h"


class PasswordManager {
    std::map<std::string, PasswordEntry> entries;

public:
    std::map<std::string, PasswordEntry> getEntries() const { return entries; }
    std::vector<PasswordEntry> getEntries(const std::string& name) const;

    void addEntry(const PasswordEntry& entry);
    void removeEntry(const std::string& name);
};



#endif //PASSWORDMANAGER_H
