﻿#ifndef STORAGE_H
#define STORAGE_H
#include <map>
#include <memory>
#include <nlohmann/json.hpp>

#include "ICryptoEngine.h"
#include "PasswordEntry.h"

class Storage {
    std::string path;
    std::shared_ptr<ICryptoEngine> cryptoEngine{};

public:
    explicit Storage(std::shared_ptr<ICryptoEngine> cryptoEngine, std::string path);

    std::string getPath() { return path; }
    void setPath(std::string path) { this->path = std::move(path); }

    void saveToFile(const std::map<std::string, PasswordEntry>& entries, const std::string& password) const;
    std::map<std::string, PasswordEntry> loadFromFile(const std::string& password) const;
};



#endif //STORAGE_H
