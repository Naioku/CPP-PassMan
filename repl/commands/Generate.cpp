#include "Generate.h"

#include <iostream>

#include "PasswordManager.h"

namespace repl::commands
{
    void Generate::run(const int& argc, char* argv[])
    {
        std::cout << passwordManager.generatePassword() << std::endl;
    }
}
