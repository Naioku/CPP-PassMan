#include "Remove.h"

#include <cxxopts.hpp>
#include <iostream>

#include "PasswordManager.h"

namespace repl::commands
{
    void Remove::run(const int& argc, char* argv[])
    {
        std::cout << "remove" << std::endl;

        cxxopts::Options addOptions(name,description);

        addOptions.add_options()
            ("n,name", "Entry name", cxxopts::value<std::string>())
            ("h,help", "Show help");

        const auto addResult = addOptions.parse(argc, argv);

        if (addResult.count("help"))
        {
            std::cout << addOptions.help() << std::endl;
            return;
        }

        std::string name;
        if (addResult.count("name"))
        {
            name = addResult["name"].as<std::string>();
        }
        else
        {
            std::cout << "Enter name: ";
            std::getline(std::cin, name);
        }

        passwordManager.removeEntry(name);
    }
}
