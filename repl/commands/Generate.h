#ifndef GENERATE_H
#define GENERATE_H
#include "CommandBase.h"


namespace repl::commands
{
    class Generate final : public CommandBase
    {
    public:
        explicit Generate(PasswordManager& passwordManager)
            : CommandBase(passwordManager, "generate", "Generate random password.") {}

        void run(const int& argc, char* argv[]) override;
    };
}


#endif //GENERATE_H
