/*******************************************************************************************
*
*   [raylib-aseprite] numbers - Load the numbers Aseprite file, and display the different animation directions.
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
    const int textTop = 140;
    const int numberTop = 200;
    InitWindow(screenWidth, screenHeight, "[raylib-aseprite] numbers");

    // Load the Aseprite file.
    Aseprite numbers = LoadAseprite("resources/numbers.aseprite");

    // Load the tag animations from the numbers aseprite.
    AsepriteTag forwards = LoadAsepriteTag(numbers, "Forwards");
    AsepriteTag backwards = LoadAsepriteTag(numbers, "Backwards");
    AsepriteTag pingpong = LoadAsepriteTag(numbers, "Ping-Pong");

    //--------------------------------------------------------------------------------------

    while(!WindowShouldClose()) {

        // Update
        //----------------------------------------------------------------------------------

        // Update the active animation of the walk down tag.
        UpdateAsepriteTag(&forwards);
        UpdateAsepriteTag(&backwards);
        UpdateAsepriteTag(&pingpong);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------

        BeginDrawing();
        {
            ClearBackground(RAYWHITE);
            const int width = GetAsepriteWidth(numbers);

            // Forwards
            DrawText(forwards.name, screenWidth / 4 - width, textTop, 20, forwards.color);
            DrawAsepriteTag(forwards, screenWidth / 4 - width, numberTop, WHITE);

            // Backwards
            DrawText(backwards.name, screenWidth / 2 - width, textTop, 20, backwards.color);
            DrawAsepriteTag(backwards, screenWidth / 2 - width, numberTop, WHITE);

            // Ping-Pong
            DrawText(pingpong.name, screenWidth - screenWidth / 4 - width, textTop, 20, pingpong.color);
            DrawAsepriteTag(pingpong, screenWidth - screenWidth / 4 - width, numberTop, WHITE);
        }
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------

    UnloadAseprite(numbers);    // Unload the Aseprite data.

    CloseWindow();
    //--------------------------------------------------------------------------------------

    return 0;
}
