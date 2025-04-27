#ifndef COMMANDSREGISTRY_H
#define COMMANDSREGISTRY_H
#include <memory>
#include <vector>


namespace repl::commands
{
    class CommandBase;

    class CommandsRegistry
    {
        std::vector<std::unique_ptr<CommandBase>> commands;

    public:
        const std::vector<std::unique_ptr<CommandBase>>& getCommands() const { return commands; }

        template<typename T, typename... Args>
        void registerCommand(Args&&... args)
        {
            commands.push_back(std::make_unique<T>(std::forward<Args>(args)...));
        }
    };
}


#endif //COMMANDSREGISTRY_H
