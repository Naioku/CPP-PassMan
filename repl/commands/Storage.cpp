#include "Storage.h"

#include <cxxopts.hpp>
#include <iostream>

#include "PasswordManager.h"

namespace repl::commands
{
    void Storage::run(const int& argc, char* argv[])
    {
        cxxopts::Options options(name, description);

        options.add_options()
            ("s,save", "Save data to file (passing main password)", cxxopts::value<std::string>())
            ("l,load", "Load data from file (passing main password)", cxxopts::value<std::string>())
            ("h,help", "Show help");

        if (const auto result = options.parse(argc, argv); result.count("help"))
        {
            std::cout << options.help() << std::endl;
        }
        else if (result.count("save"))
        {
            passwordManager.saveData(result["save"].as<std::string>());
        }
        else if (result.count("load"))
        {
            passwordManager.loadData(result["load"].as<std::string>());
        }
    }
}
