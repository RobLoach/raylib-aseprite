cmake_minimum_required(VERSION 3.11)
project (raylib-aseprite
    VERSION 0.2.0
    DESCRIPTION "raylib-aseprite"
    HOMEPAGE_URL "https://github.com/robloach/raylib-aseprite"
    LANGUAGES C)

# Include Directory
add_subdirectory(include)

# Examples
option(RAYLIB_ASEPRITE_BUILD_EXAMPLE "Example" ON)
if(RAYLIB_ASEPRITE_BUILD_EXAMPLE)
    add_subdirectory(example)
endif()

# Testing
include(CTest)
enable_testing()
if(BUILD_TESTING AND RAYLIB_ASEPRITE_BUILD_EXAMPLE)
    set(CTEST_CUSTOM_TESTS_IGNORE
        pkg-config--static
    )
    add_subdirectory(test)
endif()
