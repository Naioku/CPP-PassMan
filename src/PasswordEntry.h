#ifndef PASSWORDENTRY_H
#define PASSWORDENTRY_H
#include <optional>
#include <string>

struct PasswordEntry
{
    std::string name;
    std::string login;
    std::string password;
    std::optional<std::string> notes;
};

#endif //PASSWORDENTRY_H
