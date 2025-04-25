#ifndef PASSWORDENTRY_H
#define PASSWORDENTRY_H
#include <optional>
#include <string>
#include <nlohmann/json.hpp>

struct PasswordEntry
{
    std::string name;
    std::string login;
    std::string password;
    std::optional<std::string> notes;

    nlohmann::json toJson() const
    {
        return nlohmann::json{
                {"name", name},
                {"login", login},
                {"password", password},
                {"notes", notes}
        };
    }

    static PasswordEntry fromJson(const nlohmann::json& j)
    {
        return {
            j["name"].get<std::string>(),
            j["login"].get<std::string>(),
            j["password"].get<std::string>(),
            j["notes"].get<std::string>()
        };
    }
};

#endif //PASSWORDENTRY_H
