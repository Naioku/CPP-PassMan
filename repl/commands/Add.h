
#ifndef ADD_H
#define ADD_H
#include "CommandBase.h"

namespace repl::commands
{
    class Add final : public CommandBase
    {
    public:
        explicit Add(PasswordManager& passwordManager)
            : CommandBase(passwordManager, "add", "Add new entry.") {}

        void run(const int& argc, char* argv[]) override;
    };

}

#endif //ADD_H
