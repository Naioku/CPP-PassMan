#include <complex>
#include <iostream>
#include <cxxopts.hpp>

#include "PasswordManager.h"

std::vector<std::string> splitInputIntoArgs(const std::string& input);
void passMan(const int& argc, char* argv[]);
void help(const int&, char*[]);
void add(const int&, char*[]);
void remove(const int&, char*[]);
void listEntries(const int&, char*[]);
void changePath(const int&, char*[]);
void save(const int&, char*[]);
void load(const int&, char*[]);

using CommandFunc = void(*)(const int&, char*[]);

const std::string APP_NAME{"PassMan"};

struct Command
{
    std::string name;
    std::string shortcut;
    CommandFunc func;
    std::string description;
};

enum Commands
{
    HELP,
    ADD,
    REMOVE,
    LIST,
    CHANGE_PATH,
    SAVE,
    LOAD,
};

std::unordered_map<Commands, Command> commandsMap = {
    {HELP, {"help", "h", help, "Show help"}},
    {ADD, {"add", "a", add, "Add new entry"}},
    {REMOVE, {"remove", "r", remove, "Remove entry"}},
    {LIST, {"list", "i", listEntries, "List entries"}},
    {CHANGE_PATH, {"change-path", "c", changePath, "Change data saving path"}},
    {SAVE, {"save", "s", save, "Save data"}},
    {LOAD, {"load", "l", load, "Load data"}},
};

PasswordManager passwordManager{};

int main(const int argc, char* argv[])
{
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

        passMan(static_cast<int>(argv_cxx.size()), argv_cxx.data());
    }
}

std::vector<std::string> splitInputIntoArgs(const std::string& input)
{
    std::vector<std::string> args;
    std::string currentArg;
    bool insideDoubleQuotes = false;
    bool insideSingleQuotes = false;
    bool escapeNext = false;

    for (const char c : input) {
        if (escapeNext) {
            currentArg += c;
            escapeNext = false;
        }
        else if (c == '\\') {
            escapeNext = true;
        }
        else if (c == '"' && !insideSingleQuotes) {
            insideDoubleQuotes = !insideDoubleQuotes;
        }
        else if (c == '\'' && !insideDoubleQuotes) {
            insideSingleQuotes = !insideSingleQuotes;
        }
        else if (std::isspace(c) && !insideDoubleQuotes && !insideSingleQuotes) {
            if (!currentArg.empty()) {
                args.push_back(currentArg);
                currentArg.clear();
            }
        }
        else {
            currentArg += c;
        }
    }

    if (insideDoubleQuotes || insideSingleQuotes) {
        throw std::runtime_error("Unclosed quote detected in input.");
    }

    if (!currentArg.empty()) {
        args.push_back(currentArg);
    }

    return args;
}

void passMan(const int& argc, char* argv[])
{
    try
    {
        for (const auto& command : commandsMap | std::views::values)
        {
            if (argv[0] == command.name)
            {
                command.func(argc, argv);
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

void help(const int&, char*[])
{
    std::cout << "Usage: [OPTIONS]\n"
                  << "Options:\n";
    for (const auto& command : commandsMap | std::views::values)
    {
        std::cout << "  " << std::left << std::setw(20) << "-" + command.shortcut + ", " + command.name << command.description << std::endl;
    }
}

void add(const int& argc, char* argv[])
{
    std::cout << "add" << std::endl;

    cxxopts::Options addOptions(
        commandsMap.at(Commands::ADD).name,
        commandsMap.at(Commands::ADD).description);

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

void remove(const int& argc, char* argv[])
{
    std::cout << "remove" << std::endl;

    cxxopts::Options addOptions(
        commandsMap.at(Commands::REMOVE).name,
        commandsMap.at(Commands::REMOVE).description);

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

void listEntries(const int& argc, char* argv[])
{
    std::cout << "list" << std::endl;

    cxxopts::Options addOptions(
        commandsMap.at(Commands::LIST).name,
        commandsMap.at(Commands::LIST).description);

    addOptions.add_options()
        ("h,help", "Show help");

    const auto addResult = addOptions.parse(argc, argv);

    if (addResult.count("help"))
    {
        std::cout << addOptions.help() << std::endl;
        return;
    }

    const auto entries = passwordManager.getEntries();

    size_t nameWidth = 4;
    size_t loginWidth = 5;
    size_t passwordWidth = 8;
    size_t notesWidth = 5;

    for (const auto& [name, login, password, notes] : entries | std::views::values)
    {
        nameWidth = std::max(nameWidth, name.length());
        loginWidth = std::max(loginWidth, login.length());
        passwordWidth = std::max(passwordWidth, password.length());
        if (notes.has_value()) {
            notesWidth = std::max(notesWidth, notes->length());
        }
    }

    constexpr size_t margin = 2;
    nameWidth += margin;
    loginWidth += margin;
    passwordWidth += margin;
    notesWidth += margin;

    const int nameWidthInt = static_cast<int>(nameWidth);
    const int loginWidthInt = static_cast<int>(loginWidth);
    const int passwordWidthInt = static_cast<int>(passwordWidth);
    const int notesWidthInt = static_cast<int>(notesWidth);

    constexpr auto COLOR_CYAN = "\033[1;36m";
    constexpr auto COLOR_RESET = "\033[0m";

    std::cout
        << COLOR_CYAN
        << std::left << std::setw(nameWidthInt) << "Name" << "|"
        << std::left << std::setw(loginWidthInt) << "Login" << "|"
        << std::left << std::setw(passwordWidthInt) << "Password" << "|"
        << std::left << std::setw(notesWidthInt) << "Notes"
        << COLOR_RESET << "\n";

    std::cout << std::string(nameWidth + loginWidth + passwordWidth + notesWidth + 3, '-') << "\n";

    for (const auto& [name, login, password, notes] : entries | std::views::values)
    {
        std::cout
            << std::left << std::setw(nameWidthInt) << name << "|"
            << std::left << std::setw(loginWidthInt) << login << "|"
            << std::left << std::setw(passwordWidthInt) << password << "|"
            << std::left << std::setw(notesWidthInt) << (notes.has_value() ? notes.value() : "") << "\n";
    }

    std::cout << std::endl;
}

void changePath(const int& argc, char* argv[])
{
    std::cout << "changePath" << std::endl;
}

void save(const int& argc, char* argv[])
{
    std::cout << "save" << std::endl;
}

void load(const int& argc, char* argv[])
{
    std::cout << "load" << std::endl;
}
