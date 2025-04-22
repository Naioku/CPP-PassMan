project(PassManLib)

add_library(PassManLib STATIC
        ExampleClass.h
        ExampleClass.cpp
)

target_include_directories(PassManLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})