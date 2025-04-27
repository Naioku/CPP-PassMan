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
        commands/Storage.cpp
        commands/Storage.h
        commands/Generate.cpp
        commands/Generate.h
        commands/Settings.cpp
        commands/Settings.h
)

target_link_libraries(PassMan PassManLib)
