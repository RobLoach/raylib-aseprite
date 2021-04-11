cmake_minimum_required(VERSION 3.11)
project (raylib-aseprite
    VERSION 0.1.0
    DESCRIPTION "raylib-aseprite"
    HOMEPAGE_URL "https://github.com/robloach/raylib-aseprite"
    LANGUAGES C)

# Include Directory
add_subdirectory(include)

# Examples
option(RAYLIB_ASEPRITE_BUILD_EXAMPLE "Examples" ON)
if(RAYLIB_ASEPRITE_BUILD_EXAMPLE)
    add_subdirectory(example)
endif()

# Testing
option(RAYLIB_ASEPRITE_BUILD_TESTS "Testing" ON)
include(CTest)
enable_testing()
if(RAYLIB_ASEPRITE_BUILD_TESTS AND RAYLIB_ASEPRITE_BUILD_EXAMPLE)
    set(CTEST_CUSTOM_TESTS_IGNORE
        pkg-config--static
    )
    add_subdirectory(test)
endif()
