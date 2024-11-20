cmake_minimum_required(VERSION 3.11)
project (raylib_aseprite
    VERSION 5.5.0
    DESCRIPTION "raylib_aseprite: Use Aseprite files in raylib"
    HOMEPAGE_URL "https://github.com/robloach/raylib-aseprite"
    LANGUAGES C)

# Include Directory
add_subdirectory(include)

# Options
if ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_CURRENT_SOURCE_DIR}")
    set(RAYLIB_ASEPRITE_IS_MAIN TRUE)
else()
    set(RAYLIB_ASEPRITE_IS_MAIN FALSE)
endif()
option(RAYLIB_ASEPRITE_BUILD_EXAMPLES "Examples" ${RAYLIB_ASEPRITE_IS_MAIN})

# Examples
if(RAYLIB_ASEPRITE_BUILD_EXAMPLES)
    add_subdirectory(examples)

    # Testing
    include(CTest)
    enable_testing()
    if(BUILD_TESTING)
        # set(CTEST_CUSTOM_TESTS_IGNORE
        #     pkg-config--static
        # )
        add_subdirectory(test)
    endif()
endif()
