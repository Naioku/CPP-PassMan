
#ifndef SETTINGS_H
#define SETTINGS_H
#include "CommandBase.h"

namespace repl::commands
{

    class Settings final : public CommandBase
    {
    public:
        explicit Settings(PasswordManager& passwordManager)
            : CommandBase(passwordManager, "settings", "Display/change app settings.") {}

        void run(const int& argc, char* argv[]) override;
    };

}

#endif //SETTINGS_H
