#ifndef PASSWORDGENERATOR_H
#define PASSWORDGENERATOR_H
#include <string>


class PasswordGenerator {
    const std::string LOWERCASE = "abcdefghijklmnopqrstuvwxyz";
    const std::string UPPERCASE = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const std::string DIGITS = "0123456789";
    const std::string SYMBOLS = "!@#$%^&*()-_=+[]{};:,.<>?";

    size_t passwordSize;

public:
    explicit PasswordGenerator(const int& passwordSize);
    std::string generate() const;
    void setPasswordSize(const size_t size) { passwordSize = size; }
    size_t getPasswordSize() const { return passwordSize; }

private:
    static char generateRandomChar(const std::string& charset);
};



#endif //PASSWORDGENERATOR_H
