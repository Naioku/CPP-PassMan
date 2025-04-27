#ifndef CHANGEPATH_H
#define CHANGEPATH_H
#include "CommandBase.h"


namespace repl::commands
{
    class Storage final : public CommandBase
    {
    public:
        explicit Storage(PasswordManager& passwordManager)
            : CommandBase(passwordManager, "storage", "Load/store data.") {}

        void run(const int& argc, char* argv[]) override;
    };
}


#endif //CHANGEPATH_H
