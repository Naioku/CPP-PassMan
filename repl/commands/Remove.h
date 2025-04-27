#ifndef REMOVE_H
#define REMOVE_H
#include "CommandBase.h"

namespace repl::commands
{

    class Remove final : public CommandBase
    {
    public:
        explicit Remove(PasswordManager& passwordManager)
            : CommandBase(passwordManager, "remove", "Remove entry.") {}

        void run(const int& argc, char* argv[]) override;
    };

}

#endif //REMOVE_H
