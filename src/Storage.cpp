#include "Storage.h"

#include <fstream>
#include <utility>

Storage::Storage(std::shared_ptr<ICryptoEngine> cryptoEngine, std::string path):
    path(std::move(path)), cryptoEngine(std::move(cryptoEngine))
{
}

void Storage::saveToFile(const std::map<std::string, PasswordEntry>& entries, const std::string& password) const
{
    nlohmann::json j;
    for (const auto& [name, entry] : entries)
    {
        j[name] = entry.toJson();
    }

    const std::string encryptedData = cryptoEngine->encrypt(j.dump(), password);

    std::ofstream file(path);
    if (!file)
    {
        throw std::ios_base::failure("File cannot be opened.");
    }

    file << encryptedData;
    file.close();
}

std::map<std::string, PasswordEntry> Storage::loadFromFile(const std::string& password) const
{
    std::ifstream file(path);
    if (!file)
    {
        throw std::ios_base::failure("File cannot be opened.");
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    const std::string decryptedData = cryptoEngine->decrypt(buffer.str(), password);

    const nlohmann::json decryptedJson = nlohmann::json::parse(decryptedData);
    std::map<std::string, PasswordEntry> entries;
    for (const auto& [key, value] : decryptedJson.items())
    {
        entries[key] = PasswordEntry::fromJson(value);
    }

    return entries;
}
