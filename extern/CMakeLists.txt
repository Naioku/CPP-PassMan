﻿include(FetchContent)

FetchContent_Declare(
        sodium
        GIT_REPOSITORY https://github.com/robinlinden/libsodium-cmake.git
        GIT_TAG e5b985ad0dd235d8c4307ea3a385b45e76c74c6a
)
set(SODIUM_DISABLE_TESTS ON)
set(ENABLE_SHARED OFF CACHE INTERNAL "Disable shared build")
set(ENABLE_STATIC ON CACHE INTERNAL "Enable static build")
FetchContent_MakeAvailable(sodium)

# It is recommended way but currently 2025-04-25 is not working - directories in _deps are empty.
# I don't know why especially yesterday worked well.
#FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz)

FetchContent_Declare(
        json
        GIT_REPOSITORY https://github.com/nlohmann/json
        GIT_TAG v3.12.0)
FetchContent_MakeAvailable(json)

FetchContent_Declare(
        cxxopts
        GIT_REPOSITORY https://github.com/jarro2783/cxxopts.git
        GIT_TAG v3.2.1)
FetchContent_MakeAvailable(cxxopts)

add_subdirectory(gtest)