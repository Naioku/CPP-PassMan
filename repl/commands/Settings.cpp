#include "Settings.h"

#include <cxxopts.hpp>
#include <iostream>

#include "PasswordManager.h"

namespace repl::commands
{
    void Settings::run(const int& argc, char* argv[])
    {
        cxxopts::Options options(name, description);

        options.add_options()
            ("h,help", "Display help.")
            ("d,display", "Display current settings.")
            ("p,path", "Set new path.", cxxopts::value<std::string>())
            ("g,gen-pass-size", "Set size of generated passwords.", cxxopts::value<std::size_t>());

        if (const auto result = options.parse(argc, argv); result.count("help"))
        {
            std::cout << options.help() << std::endl;
        }
        else if (result.count("display"))
        {
            std::cout << "Data saving path: " << passwordManager.getDataSavingPath() << "\n";
            std::cout << "Generated password size: " << passwordManager.getGeneratedPasswordSize() << "\n";
            std::cout << std::endl;
        }
        else if (result.count("path"))
        {
            passwordManager.setDataSavingPath(result["path"].as<std::string>());
        }
        else if (result.count("gen-pass-size"))
        {
            const size_t size = result["gen-pass-size"].as<std::size_t>();
            if (size < PASSWORD_MIN_SIZE)
            {
                std::cerr << "Invalid size. Must be 20 or greater." << std::endl;
                return;
            }

            passwordManager.setGeneratedPasswordSize(size);
        }
    }
}
