#include "Help.h"

#include <iomanip>
#include <iostream>

#include "CommandsRegistry.h"

namespace repl::commands
{
    void Help::run(const int& argc, char* argv[])
    {
        std::cout << "Usage: [OPTIONS]\n"
            << "Options:\n";
        for (const auto& command : commands.getCommands())
        {
            std::cout << "  " << std::left << std::setw(20) << command->getName() << command->getDescription() << "\n";
        }

        std::cout << std::endl;
    }
}
