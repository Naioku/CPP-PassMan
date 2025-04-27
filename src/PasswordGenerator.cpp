#include "PasswordGenerator.h"

#include <algorithm>
#include <random>
#include <sodium.h>
#include <stdexcept>

PasswordGenerator::PasswordGenerator(const int& passwordSize)
{
    if (passwordSize < 4) {
        throw std::invalid_argument("Password too short for all categories.");
    }

    this->passwordSize = passwordSize;
}

std::string PasswordGenerator::generate() const
{
    std::string result;
    result += generateRandomChar(LOWERCASE);
    result += generateRandomChar(UPPERCASE);
    result += generateRandomChar(DIGITS);
    result += generateRandomChar(SYMBOLS);

    const std::string all = LOWERCASE + UPPERCASE + DIGITS + SYMBOLS;

    for (auto i = 4; i < passwordSize; ++i)
    {
        result += generateRandomChar(all);
    }

    std::ranges::shuffle(result, std::mt19937(std::random_device{}()));

    return result;
}

char PasswordGenerator::generateRandomChar(const std::string& charset)
{
    unsigned char index;
    randombytes_buf(&index, 1);
    return charset[index % charset.size()];
}
