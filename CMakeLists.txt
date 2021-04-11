cmake_minimum_required(VERSION 3.11)
project (raylib-aseprite
    VERSION 0.0.1
    DESCRIPTION "raylib-aseprite"
    HOMEPAGE_URL "https://github.com/robloach/raylib-aseprite"
    LANGUAGES C)

# Include Directory
add_subdirectory(include)

# Examples
option(BUILD_RAYLIB_ASEPRITE_EXAMPLE "Examples" ON)
if(BUILD_RAYLIB_ASEPRITE_EXAMPLE)
    add_subdirectory(example)
endif()

# Testing
# TODO: Add Testing
# include(CTest)
# enable_testing()
# if(BUILD_TESTING AND BUILD_RAYLIB_ASEPRITE_EXAMPLES)
#     set(CTEST_CUSTOM_TESTS_IGNORE
#         pkg-config--static
#     )
#     add_subdirectory(test)
# endif()
