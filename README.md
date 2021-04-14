# raylib-aseprite

Load [Aseprite](https://aseprite.org) `.aseprite` files to use animated sprites in [raylib](https://raylib.com).

![example/raylib-aseprite-example.png](example/raylib-aseprite-example.png)

## Usage

This is a header-only library. To use it, define `RAYLIB_ASEPRITE_IMPLEMENTATION` in one .c source file before including *raylib-aseprite.h*. You will also have to link the raylib dependency.

### Example

``` c
#include "raylib.h"

#define RAYLIB_ASEPRITE_IMPLEMENTATION
#include "raylib-aseprite.h"

int main() {
    InitWindow(640, 480, "Aseprite Example");

    // Load the backpacker Aseprite file.
    Aseprite backpacker = LoadAseprite("resources/backpacker.aseprite");

    // Load the Walk Down tag.
    AsepriteTag walkdown = LoadAsepriteTag(backpacker, "Walk Down");
    walkdown.speed = 2; // Double the animation speed.

    while(!WindowShouldClose()) {
        // Update the animation frame for walk down.
        UpdateAsperiteTag(&walkdown);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw the 0th frame from the backpacker sprite.
        DrawAseprite(backpacker, 0, 100, 100, WHITE);

        // Draw the Walk Down animation.
        DrawAsepriteTag(walkdown, 200, 100, WHITE);

        EndDrawing();
    }

    // Clean up the backpacker aseprite.
    UnloadAseprite(backpacker);

    CloseWindow();
    return 0;
}
```

### Cheatsheet

``` c
// Aseprite functions
Aseprite LoadAseprite(const char* fileName);                        // Load an .aseprite file
Aseprite LoadAsepriteFromMemory(unsigned char* fileData, unsigned int size);  // Load an aseprite file from memory
bool IsAsepriteReady(Aseprite aseprite);                            // Check if the given Aseprite was loaded successfully
void UnloadAseprite(Aseprite aseprite);                             // Unloads the aseprite file
void TraceAseprite(Aseprite aseprite);                              // Display all information associated with the aseprite
Texture GetAsepriteTexture(Aseprite aseprite);                      // Retrieve the raylib texture associated with the aseprite
int GetAsepriteWidth(Aseprite aseprite);                            // Get the width of the sprite
int GetAsepriteHeight(Aseprite aseprite);                           // Get the height of the sprite
int GetAspriteTagCount(Aseprite aseprite);                          // Get the total amount of available tags
void DrawAseprite(Aseprite aseprite, int frame, int posX, int posY, Color tint);
void DrawAsepriteV(Aseprite aseprite, int frame, Vector2 position, Color tint);
void DrawAsepriteEx(Aseprite aseprite, int frame, Vector2 position, float rotation, float scale, Color tint);
void DrawAsepritePro(Aseprite aseprite, int frame, Rectangle dest, Vector2 origin, float rotation, Color tint);

// Aseprite Tag functions
AsepriteTag LoadAsepriteTag(Aseprite aseprite, const char* name);   // Load a Aseprite tag animation sequence
AsepriteTag LoadAsepriteTagFromIndex(Aseprite aseprite, int index);    // Load a Aseprite tag animation sequence from its index
bool IsAsepriteTagReady(AsepriteTag tag);                           // Check if the given Aseprite tag was loaded successfully
void UpdateAsepriteTag(AsepriteTag* tag);                           // Update the tag animation frame
AsepriteTag GenAsepriteTagDefault();                                // Generate an empty Tag with sane defaults
void DrawAsepriteTag(AsepriteTag tag, int posX, int posY, Color tint);
void DrawAsepriteTagV(AsepriteTag tag, Vector2 position, Color tint);
void DrawAsepriteTagEx(AsepriteTag tag, Vector2 position, float rotation, float scale, Color tint);
void DrawAsepriteTagPro(AsepriteTag tag, Rectangle dest, Vector2 origin, float rotation, Color tint);
```

## Development

To build the example locally, and run tests, use [cmake](https://cmake.org/).

``` bash
git submodule update --init
mkdir build
cd build
cmake ..
make
cd examples
./raylib-aseprite-example
```

This uses [cute_asesprite.h](https://github.com/RandyGaul/cute_headers/blob/master/cute_aseprite.h) to handle loading the aseprite file. Thank you to [Randy Gaul's cute_headers](https://github.com/RandyGaul/cute_headers) for making this all possible.

## License

raylib-aseprite is licensed under an unmodified zlib/libpng license, which is an OSI-certified, BSD-like license that allows static linking with closed source software. Check [LICENSE](LICENSE) for further details.
