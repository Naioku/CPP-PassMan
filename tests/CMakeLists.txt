add_executable(Tests
        ExampleTest.cpp
)

target_link_libraries(Tests
        PassManLib
        gtest
        gtest_main
)