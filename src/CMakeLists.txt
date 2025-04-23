project(PassManLib)

add_library(PassManLib STATIC
        PasswordManager.cpp
        PasswordManager.h
        PasswordEntry.h
        Utils.cpp
        Utils.h
)

target_include_directories(PassManLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})