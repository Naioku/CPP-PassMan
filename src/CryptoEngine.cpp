#include "CryptoEngine.h"
#include <sodium.h>
#include <stdexcept>
#include <vector>


constexpr size_t NONCE_SIZE = crypto_secretbox_NONCEBYTES;
constexpr size_t KEY_SIZE = crypto_secretbox_KEYBYTES;
constexpr size_t SALT_SIZE = crypto_pwhash_SALTBYTES;

CryptoEngine::CryptoEngine()
{
    if (sodium_init() < 0)
    {
        throw std::runtime_error("libsodium init failed");
    }
}

std::string CryptoEngine::encrypt(const std::string& plaintext, const std::string& password) const
{
    unsigned char salt[SALT_SIZE];
    randombytes_buf(salt, sizeof salt);

    unsigned char key[KEY_SIZE];
    if (crypto_pwhash(
        key,
        KEY_SIZE,
        password.c_str(),
        password.length(),
        salt,
        crypto_pwhash_OPSLIMIT_INTERACTIVE,
        crypto_pwhash_MEMLIMIT_INTERACTIVE,
        crypto_pwhash_ALG_DEFAULT) != 0)
    {
        throw std::runtime_error("key derivation failed");
    }

    unsigned char nonce[NONCE_SIZE];
    randombytes_buf(nonce, sizeof nonce);

    std::vector<unsigned char> ciphertext(crypto_secretbox_MACBYTES + plaintext.size());
    crypto_secretbox_easy(
        ciphertext.data(),
        reinterpret_cast<const unsigned char*>(plaintext.c_str()),
        plaintext.size(),
        nonce,
        key);

    std::string result;
    result.append(reinterpret_cast<char*>(salt), SALT_SIZE);
    result.append(reinterpret_cast<char*>(nonce), NONCE_SIZE);
    result.append(reinterpret_cast<char*>(ciphertext.data()), ciphertext.size());

    return result;
}

std::string CryptoEngine::decrypt(const std::string& ciphertext, const std::string& password) const
{
    if (ciphertext.size() < SALT_SIZE + NONCE_SIZE + crypto_secretbox_MACBYTES)
    {
        throw std::runtime_error("text too short");
    }

    const auto* salt = reinterpret_cast<const unsigned char*>(ciphertext.data());
    const auto* nonce = reinterpret_cast<const unsigned char*>(ciphertext.data() + SALT_SIZE);
    const auto* encryptedData = reinterpret_cast<const unsigned char*>(ciphertext.data() + SALT_SIZE + NONCE_SIZE);
    const size_t encryptedDataLen = ciphertext.size() - SALT_SIZE - NONCE_SIZE;

    unsigned char key[KEY_SIZE];
    if (crypto_pwhash(
        key,
        KEY_SIZE,
        password.c_str(),
        password.length(),
        salt,
        crypto_pwhash_OPSLIMIT_INTERACTIVE,
        crypto_pwhash_MEMLIMIT_INTERACTIVE,
        crypto_pwhash_ALG_DEFAULT) != 0)
    {
        throw std::runtime_error("key derivation failed");
    }

    std::vector<unsigned char> decryptedData(encryptedDataLen - crypto_secretbox_MACBYTES);
    if (crypto_secretbox_open_easy(decryptedData.data(), encryptedData, encryptedDataLen, nonce, key) != 0)
    {
        throw std::runtime_error("decryption failed (bad password?)");
    }

    return {reinterpret_cast<char*>(decryptedData.data()), decryptedData.size()};
}
