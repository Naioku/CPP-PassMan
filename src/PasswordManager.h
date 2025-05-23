﻿#ifndef PASSWORDMANAGER_H
#define PASSWORDMANAGER_H
#include <map>
#include <vector>

#include "CryptoEngine.h"
#include "PasswordEntry.h"
#include "PasswordGenerator.h"
#include "Storage.h"


class PasswordManager {
    std::map<std::string, PasswordEntry> entries;
    std::unique_ptr<Storage> storage{std::make_unique<Storage>(
        std::make_shared<CryptoEngine>(),
        "data.dat")};
    std::unique_ptr<PasswordGenerator> passwordGenerator{std::make_unique<PasswordGenerator>(
        20)};

public:
    std::map<std::string, PasswordEntry> getEntries() const { return entries; }
    std::vector<PasswordEntry> getEntries(const std::string& name) const;

    void addEntry(const PasswordEntry& entry);
    void removeEntry(const std::string& name);

    std::string getDataSavingPath() const { return storage->getPath(); }
    void setDataSavingPath(const std::string& path) const { storage->setPath(path); }
    void saveData(const std::string& password) const;
    void loadData(const std::string& password);

    size_t getGeneratedPasswordSize() const { return passwordGenerator->getPasswordSize(); }
    void setGeneratedPasswordSize(const size_t size) const { passwordGenerator->setPasswordSize(size); }
    std::string generatePassword() const;
};



#endif //PASSWORDMANAGER_H
