add_executable(Tests
        PasswordManager.cpp
)

target_link_libraries(Tests
        PassManLib
        gtest
        gtest_main
)