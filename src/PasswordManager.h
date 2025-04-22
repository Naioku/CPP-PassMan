#ifndef PASSWORDMANAGER_H
#define PASSWORDMANAGER_H
#include <vector>

#include "PasswordEntry.h"


class PasswordManager {
    std::vector<PasswordEntry> entries;

public:
    std::vector<PasswordEntry> getEntries() const { return entries; }

    void addEntry(const PasswordEntry& entry);
};



#endif //PASSWORDMANAGER_H
