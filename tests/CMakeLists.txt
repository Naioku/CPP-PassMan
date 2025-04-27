add_executable(Tests
        PasswordManager.cpp
        Utils.cpp
        CryptoEngine.cpp
        Storage.cpp
        PasswordGenerator.cpp
)

target_link_libraries(Tests
        PassManLib
        gtest
        gtest_main
        gmock
        gmock_main
)