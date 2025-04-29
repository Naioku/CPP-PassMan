#include "Add.h"

#include <cxxopts.hpp>
#include <iostream>

#include "PasswordManager.h"

namespace repl::commands
{
    void Add::run(const int& argc, char* argv[])
    {
        cxxopts::Options options(name, description);

        options.add_options()
            ("h,help", "Show help.")
            ("n,name", "Entry name.", cxxopts::value<std::string>())
            ("l,login", "Login.", cxxopts::value<std::string>())
            ("p,password", "Password. Omit in case You want to generate one.", cxxopts::value<std::string>()->default_value(""))
            ("o,notes", "Notes.", cxxopts::value<std::string>()->default_value(""));

        const auto result = options.parse(argc, argv);

        if (result.count("help"))
        {
            std::cout << options.help() << std::endl;
            return;
        }

        std::string name, login, password, notes;
        if (result.count("name") && result.count("login"))
        {
            name = result["name"].as<std::string>();
            login = result["login"].as<std::string>();
            password = result["password"].as<std::string>();
            notes = result["notes"].as<std::string>();
        }
        else
        {
            std::cout << "Enter name: ";
            std::getline(std::cin, name);

            std::cout << "Enter login: ";
            std::getline(std::cin, login);

            std::cout << "Enter password (don't type anything and press ENTER to use generator): ";
            std::getline(std::cin, password);

            std::cout << "Enter notes (optional): ";
            std::getline(std::cin, notes);
        }

        if (password.empty())
        {
            password = passwordManager.generatePassword();
        }

        passwordManager.addEntry({name, login, password, notes});
    }
}
