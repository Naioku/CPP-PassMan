
#ifndef SETTINGS_H
#define SETTINGS_H
#include "CommandBase.h"

namespace repl::commands
{
    constexpr size_t PASSWORD_MIN_SIZE = 20;

    class Settings final : public CommandBase
    {
    public:
        explicit Settings(PasswordManager& passwordManager)
            : CommandBase(passwordManager, "settings", "Display/change app settings.") {}

        void run(const int& argc, char* argv[]) override;
    };

}

#endif //SETTINGS_H
