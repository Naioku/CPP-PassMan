#ifndef CRYPTOENGINE_H
#define CRYPTOENGINE_H
#include <string>

#include "ICryptoEngine.h"


class CryptoEngine final : public ICryptoEngine{
public:
    CryptoEngine();
    std::string encrypt(const std::string& plaintext, const std::string& password) const override;
    std::string decrypt(const std::string& ciphertext, const std::string& password) const override;
};


#endif //CRYPTOENGINE_H
