cmake_minimum_required(VERSION 3.31)
project(PassMan)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(extern)
add_subdirectory(src)
add_subdirectory(tests)

add_executable(PassMan app/main.cpp)

if (MINGW)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc -pthread")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
endif()
target_link_libraries(PassMan PassManLib)