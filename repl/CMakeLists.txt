add_executable(PassMan main.cpp
        commands/CommandBase.h
        commands/Add.cpp
        commands/Add.h
        commands/Remove.cpp
        commands/Remove.h
        commands/List.cpp
        commands/List.h
        commands/Help.cpp
        commands/Help.h
        commands/CommandsRegistry.h
)

target_link_libraries(PassMan PassManLib)
