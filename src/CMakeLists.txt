project(PassManLib)

add_library(PassManLib STATIC
        PasswordManager.cpp
        PasswordManager.h
        PasswordEntry.h
)

target_include_directories(PassManLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})