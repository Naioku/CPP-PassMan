#include <complex>
#include <iostream>
#include <cxxopts.hpp>

#include "PasswordManager.h"
#include "commands/CommandsRegistry.h"
#include "commands/Add.h"
#include "commands/Help.h"
#include "commands/List.h"
#include "commands/Remove.h"

std::vector<std::string> splitInputIntoArgs(const std::string& input);
void passMan(const int& argc, char* argv[], const repl::commands::CommandsRegistry&);

//     {CHANGE_PATH, {"change-path", "c", changePath, "Change data saving path"}},
//     {SAVE, {"save", "s", save, "Save data"}},
//     {LOAD, {"load", "l", load, "Load data"}},
// };


int main(const int argc, char* argv[])
{
    PasswordManager passwordManager{};
    repl::commands::CommandsRegistry commandsRegistry{};

    commandsRegistry.registerCommand<repl::commands::Help>(passwordManager, commandsRegistry);
    commandsRegistry.registerCommand<repl::commands::Add>(passwordManager);
    commandsRegistry.registerCommand<repl::commands::Remove>(passwordManager);
    commandsRegistry.registerCommand<repl::commands::List>(passwordManager);

    while (true)
    {
        std::cout << "> ";
        std::string input;
        std::getline(std::cin, input);

        if (input == "exit") break;
        if (input.empty()) continue;

        auto args = splitInputIntoArgs(input);

        std::vector<char*> argv_cxx;
        for (auto& arg : args)
        {
            argv_cxx.push_back(const_cast<char*>(arg.c_str()));
        }

        passMan(static_cast<int>(argv_cxx.size()), argv_cxx.data(), commandsRegistry);
    }

    return 0;
}

std::vector<std::string> splitInputIntoArgs(const std::string& input)
{
    std::vector<std::string> args;
    std::string currentArg;
    bool insideDoubleQuotes = false;
    bool insideSingleQuotes = false;
    bool escapeNext = false;

    for (const char c : input)
    {
        if (escapeNext)
        {
            currentArg += c;
            escapeNext = false;
        }
        else if (c == '\\')
        {
            escapeNext = true;
        }
        else if (c == '"' && !insideSingleQuotes)
        {
            insideDoubleQuotes = !insideDoubleQuotes;
        }
        else if (c == '\'' && !insideDoubleQuotes)
        {
            insideSingleQuotes = !insideSingleQuotes;
        }
        else if (std::isspace(c) && !insideDoubleQuotes && !insideSingleQuotes)
        {
            if (!currentArg.empty())
            {
                args.push_back(currentArg);
                currentArg.clear();
            }
        }
        else
        {
            currentArg += c;
        }
    }

    if (insideDoubleQuotes || insideSingleQuotes)
    {
        throw std::runtime_error("Unclosed quote detected in input.");
    }

    if (!currentArg.empty())
    {
        args.push_back(currentArg);
    }

    return args;
}

void passMan(const int& argc, char* argv[], const repl::commands::CommandsRegistry& commandsRegistry)
{
    try
    {
        for (const auto& command : commandsRegistry.getCommands())
        {
            if (argv[0] == command->getName())
            {
                command->run(argc, argv);
                return;
            }
        }

        throw std::runtime_error("No valid command provided. Use --help for usage.\n");
    }
    catch (const cxxopts::exceptions::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}