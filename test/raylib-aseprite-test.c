#include <assert.h>

#include "raylib.h"

#define RAYLIB_ASEPRITE_IMPLEMENTATION
#include "raylib-aseprite.h"

int main(int argc, char *argv[]) {
    // Initialization
    SetTraceLogLevel(LOG_ALL);
    TraceLog(LOG_INFO, "================================");
    TraceLog(LOG_INFO, "raylib-aseprite-test");
    TraceLog(LOG_INFO, "================================");

    InitWindow(640, 480, "raylib-aseprite-tests");
    assert(IsWindowReady());

    // Make sure we're running in the correct directory.
    assert(argc > 0);
    const char* dir = GetDirectoryPath(argv[0]);
    assert(ChangeDirectory(dir));

    // LoadAseprite()
    ase_t* ase = LoadAseprite("resources/backpacker.aseprite");
    assert(ase != NULL);
    assert(ase->frame_count > 5);

    // TraceAseprite()
    TraceAseprite(ase);

    // GetAsepriteTexture()
    Texture texture = GetAsepriteTexture(ase);
    assert(texture.width > 2);
    assert(texture.height > 2);

    BeginDrawing();
    {
        // DrawAseprite()
        DrawAseprite(ase, 3, 10, 10, WHITE);
        // DrawAsepriteV()
        DrawAsepriteV(ase, 5, (Vector2){10, 20}, WHITE);
        // DrawAsepriteEx()
        DrawAsepriteEx(ase, 6, (Vector2){10, 30}, 20, 3, WHITE);
        // DrawAsepritePro()
        DrawAsepritePro(ase, 7, (Rectangle){30, 30, 20, 20}, (Vector2){0, 0}, 0.5f, WHITE);
    }
    EndDrawing();

    // UnloadAseprite()
    UnloadAseprite(ase);

    CloseWindow();
    TraceLog(LOG_INFO, "================================");
    TraceLog(LOG_INFO, "raylib-aseprite tests succesful");
    TraceLog(LOG_INFO, "================================");

    return 0;
}
