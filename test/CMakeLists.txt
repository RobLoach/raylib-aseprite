# raylib-aseprite-test
add_executable(raylib-aseprite-test raylib-aseprite-test.c)
target_compile_options(raylib-aseprite-test PRIVATE -Wall -Wextra -Wconversion -Wsign-conversion)
target_link_libraries(raylib-aseprite-test PUBLIC
    raylib
    raylib_aseprite
)
set_property(TARGET raylib-aseprite-test PROPERTY C_STANDARD 99)

# Copy the resources
file(GLOB resources resources/*)
set(test_resources)
list(APPEND test_resources ${resources})
file(COPY ${test_resources} DESTINATION "resources/")

# Set up the test
list(APPEND CMAKE_CTEST_ARGUMENTS "--output-on-failure")
add_test(NAME raylib-aseprite-test COMMAND raylib-aseprite-test)
