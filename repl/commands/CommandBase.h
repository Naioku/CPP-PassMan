#ifndef ICOMMAND_H
#define ICOMMAND_H
#include <memory>
#include <string>
#include <utility>

class PasswordManager;

namespace repl::commands
{
    class CommandBase
    {
    protected:
        PasswordManager& passwordManager;
        std::string name;
        std::string description;

    public:
        explicit CommandBase(
            PasswordManager& passwordManager,
            std::string name,
            std::string description
        ) : passwordManager(passwordManager),
            name(std::move(name)),
            description(std::move(description)) {}

        virtual ~CommandBase() = default;

        const std::string& getName() const { return name; }
        const std::string& getDescription() const { return description; }

        virtual void run(const int& argc, char* argv[]) = 0;
    };
}

#endif //ICOMMAND_H
