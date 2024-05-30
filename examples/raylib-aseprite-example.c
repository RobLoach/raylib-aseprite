/*******************************************************************************************
*
*   [raylib-aseprite] example - Load a Aseprite file, and display the animated sprite.
*
*   This example has been created using raylib 3.5 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Example by Rob Loach (@RobLoach)
*
*   Copyright (c) 2021 Rob Loach (@RobLoach)
*
********************************************************************************************/

#include "raylib.h"

#define RAYLIB_ASEPRITE_IMPLEMENTATION
#include "raylib-aseprite.h"

int main() {
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "[raylib-aseprite] example");
    SetTargetFPS(60);

    // Load the Aseprite file.
    Aseprite george = LoadAseprite("resources/george.aseprite");

    // Load the standing animations from the Aseprite tags.
    AsepriteTag walking = LoadAsepriteTag(george, "Walk-Down");

    // Center George on the screen.
    const float scale = 4;
    Vector2 position = {
        GetScreenWidth() / 2 - GetAsepriteWidth(george) / 2 * scale,
        GetScreenHeight() / 2 - GetAsepriteHeight(george) / 2 * scale
    };
    //--------------------------------------------------------------------------------------

    while(!WindowShouldClose()) {

        // Update
        //----------------------------------------------------------------------------------
        // Update the active moving animation.
        UpdateAsepriteTag(&walking);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        {
            ClearBackground(RAYWHITE);

            // Draw one frame of George.
            DrawAseprite(george, 0, 100, 100, WHITE);
            DrawAseprite(george, 4, 100, 150, WHITE);
            DrawAseprite(george, 8, 100, 200, WHITE);
            DrawAsepriteFlipped(george, 12, 100, 250, false, true, WHITE);

            // Draw the walking animation.
            DrawAsepriteTagEx(walking, position, 0, scale, WHITE);
        }
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------

    UnloadAseprite(george);    // Unload the Aseprite data.

    CloseWindow();
    //--------------------------------------------------------------------------------------

    return 0;
}
