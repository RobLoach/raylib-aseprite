# raylib
find_package(raylib QUIET)
if (NOT raylib_FOUND)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../vendor/raylib ${CMAKE_CURRENT_SOURCE_DIR}/../vendor/raylib)
endif()

# raylib-aseprite-example
add_executable(raylib-aseprite-example raylib-aseprite-example.c)
target_link_libraries(raylib-aseprite-example PUBLIC
    raylib
    raylib-aseprite
)

# raylib-aseprite-numbers
add_executable(raylib-aseprite-numbers raylib-aseprite-numbers.c)
target_link_libraries(raylib-aseprite-numbers PUBLIC
    raylib
    raylib-aseprite
)

# Copy the resources
file(GLOB resources resources/*)
set(test_resources)
list(APPEND test_resources ${resources})
file(COPY ${test_resources} DESTINATION "resources/")
