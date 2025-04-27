#ifndef LIST_H
#define LIST_H
#include "CommandBase.h"

namespace repl::commands
{
    class List final : public CommandBase
    {
    public:
        explicit List(PasswordManager& passwordManager)
            : CommandBase(passwordManager, "list", "List all entries.") {}

        void run(const int& argc, char* argv[]) override;
    };
}

#endif //LIST_H