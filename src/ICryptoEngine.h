#ifndef ICRYPTOENGINE_H
#define ICRYPTOENGINE_H
#include <string>

class ICryptoEngine
{
public:
    virtual ~ICryptoEngine() = default;
    virtual std::string encrypt(const std::string& plaintext, const std::string& password) const = 0;
    virtual std::string decrypt(const std::string& ciphertext, const std::string& password) const = 0;
};

#endif //ICRYPTOENGINE_H
