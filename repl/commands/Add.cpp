
#include "Add.h"

#include <cxxopts.hpp>
#include <iostream>

#include "PasswordManager.h"

namespace repl::commands
{
    void Add::run(const int& argc, char* argv[])
    {
        std::cout << "add" << std::endl;

        cxxopts::Options addOptions(name, description);

        addOptions.add_options()
            ("n,name", "Entry name", cxxopts::value<std::string>())
            ("l,login", "Login", cxxopts::value<std::string>())
            ("p,password", "Password", cxxopts::value<std::string>())
            ("o,notes", "Notes", cxxopts::value<std::string>()->default_value(""))
            ("h,help", "Show help");

        const auto addResult = addOptions.parse(argc, argv);

        std::cout << addResult.arguments_string() << std::endl;

        if (addResult.count("help"))
        {
            std::cout << addOptions.help() << std::endl;
            return;
        }

        std::string name, login, password, notes;
        if (addResult.count("name") && addResult.count("login") && addResult.count("password"))
        {
            name = addResult["name"].as<std::string>();
            login = addResult["login"].as<std::string>();
            password = addResult["password"].as<std::string>();
            notes = addResult.count("notes") ? addResult["notes"].as<std::string>() : "";
        }
        else
        {
            std::cout << "Enter name: ";
            std::getline(std::cin, name);

            std::cout << "Enter login: ";
            std::getline(std::cin, login);

            std::cout << "Enter password: ";
            std::getline(std::cin, password);

            std::cout << "Enter notes (optional): ";
            std::getline(std::cin, notes);
        }

        passwordManager.addEntry({name, login, password, notes});
    }
}
