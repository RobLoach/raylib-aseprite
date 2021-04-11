# raylib-aseprite-test
add_executable(raylib-aseprite-test raylib-aseprite-test.c)
target_link_libraries(raylib-aseprite-test PUBLIC
    raylib
    raylib-aseprite)

# Copy the resources
file(GLOB resources resources/*)
set(test_resources)
list(APPEND test_resources ${resources})
file(COPY ${test_resources} DESTINATION "resources/")

# Set up the test
add_test(NAME raylib-aseprite-test COMMAND raylib-aseprite-test)
