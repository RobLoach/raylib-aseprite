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
    AsepriteTag down = LoadAsepriteTag(george, "Walk-Down");
    AsepriteTag left = LoadAsepriteTag(george, "Walk-Left");
    AsepriteTag right = LoadAsepriteTag(george, "Walk-Right");
    AsepriteTag up = LoadAsepriteTag(george, "Walk-Up");
    AsepriteTag* current = &down;

    // Center George on the screen.
    const float scale = 6;
    const int speed = 4;
    Vector2 position = {
        GetScreenWidth() / 2 - GetAsepriteWidth(george) / 2 * scale,
        GetScreenHeight() / 2 - GetAsepriteHeight(george) / 2 * scale
    };
    //--------------------------------------------------------------------------------------

    while(!WindowShouldClose()) {

        // Update
        //----------------------------------------------------------------------------------

        // Update the active moving animation.
        if (IsKeyDown(KEY_UP)) {
            current = &up;
            position.y -= speed;
            current->paused = false;
        }
        else if (IsKeyDown(KEY_RIGHT)) {
            current = &right;
            position.x += speed;
            current->paused = false;
        }
        else if (IsKeyDown(KEY_DOWN)) {
            current = &down;
            position.y += speed;
            current->paused = false;
        }
        else if (IsKeyDown(KEY_LEFT)) {
            current = &left;
            position.x -= speed;
            current->paused = false;
        }
        else {
            current->paused = true;
        }

        // Have George stop walking with two feet on the ground.
        if (current->paused) {
            SetAsepriteTagFrame(current, 1);
        }

        // Update the animation.
        UpdateAsepriteTag(current);

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        {
            ClearBackground(RAYWHITE);

            // Draw the current walking animation.
            DrawAsepriteTagEx(*current, position, 0, scale, WHITE);

            const char* text = "Use arrow keys to walk";
            DrawText(text, GetScreenWidth() / 2 - MeasureText(text, 20) / 2, GetScreenHeight() - 80, 20, GRAY);
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
