#ifndef HELP_H
#define HELP_H

#include "CommandBase.h"

namespace repl::commands
{
    class CommandsRegistry;
}

namespace repl::commands
{
    class Help final : public CommandBase
    {
       const CommandsRegistry& commands;
    public:
        Help(
            PasswordManager& passwordManager,
            const CommandsRegistry& commands
            ) : CommandBase(passwordManager, "help", "Show help"), commands(commands) {}

        void run(const int& argc, char* argv[]) override;
    };

}

#endif //HELP_H
