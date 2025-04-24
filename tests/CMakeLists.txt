add_executable(Tests
        PasswordManager.cpp
        Utils.cpp
        CryptoEngine.cpp
)

target_link_libraries(Tests
        PassManLib
        gtest
        gtest_main
)