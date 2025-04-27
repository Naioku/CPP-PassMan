#include "List.h"

#include <cxxopts.hpp>
#include <iomanip>
#include <iostream>

#include "PasswordManager.h"

namespace repl::commands
{
    void List::run(const int& argc, char* argv[])
    {
        std::cout << "list" << std::endl;

        cxxopts::Options addOptions(name, description);

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
}
