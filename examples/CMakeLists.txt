# raylib
find_package(raylib QUIET)
if (NOT raylib_FOUND)
    include(FetchContent)
        FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.5
    )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
        set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)
        add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
    endif()
endif()

# raylib-aseprite-example
add_executable(raylib-aseprite-example raylib-aseprite-example.c)
target_link_libraries(raylib-aseprite-example PUBLIC
    raylib
    raylib_aseprite
)
set_property(TARGET raylib-aseprite-example PROPERTY C_STANDARD 99)

# raylib-aseprite-numbers
add_executable(raylib-aseprite-numbers raylib-aseprite-numbers.c)
target_link_libraries(raylib-aseprite-numbers PUBLIC
    raylib
    raylib_aseprite
)
set_property(TARGET raylib-aseprite-numbers PROPERTY C_STANDARD 99)

# raylib-aseprite-walk
add_executable(raylib-aseprite-walk raylib-aseprite-walk.c)
target_link_libraries(raylib-aseprite-walk PUBLIC
    raylib
    raylib_aseprite
)
set_property(TARGET raylib-aseprite-walk PROPERTY C_STANDARD 99)

# Copy the resources
file(GLOB resources resources/*)
set(test_resources)
list(APPEND test_resources ${resources})
file(COPY ${test_resources} DESTINATION "resources/")
