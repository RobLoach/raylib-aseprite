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
    AsepriteTag standing[4] = {
        LoadAsepriteTag(george, "Stand-Up"),
        LoadAsepriteTag(george, "Stand-Right"),
        LoadAsepriteTag(george, "Stand-Down"),
        LoadAsepriteTag(george, "Stand-Left")
    };

    // Load the moving animations from the Aseprite tags.
    AsepriteTag moving[4] = {
        LoadAsepriteTag(george, "Walk-Up"),
        LoadAsepriteTag(george, "Walk-Right"),
        LoadAsepriteTag(george, "Walk-Down"),
        LoadAsepriteTag(george, "Walk-Left")
    };

    // Start the player facing down.
    int direction = 2;

    // Center the scaled player on the screen.
    const float scale = 4;
    Vector2 playerPosition = {
        GetScreenWidth() / 2 - GetAsepriteWidth(george) / 2 * scale,
        GetScreenHeight() / 2 - GetAsepriteHeight(george) / 2 * scale
    };

    // How fast the player should move around.
    const float speed = 2;

    // Whether or not the player is actively moving.
    bool playerMoving;
    //--------------------------------------------------------------------------------------

    while(!WindowShouldClose()) {

        // Update
        //----------------------------------------------------------------------------------
        if (IsKeyDown(KEY_UP)) {
            direction = 0;
            playerMoving = true;
        }
        else if (IsKeyDown(KEY_RIGHT)) {
            direction = 1;
            playerMoving = true;
        }
        else if (IsKeyDown(KEY_DOWN)) {
            direction = 2;
            playerMoving = true;
        }
        else if (IsKeyDown(KEY_LEFT)) {
            direction = 3;
            playerMoving = true;
        }
        else {
            playerMoving = false;
        }

        if (playerMoving) {
            // Update the active moving animation.
            UpdateAsepriteTag(&moving[direction]);

            // Move the player.
            switch (direction) {
                case 0:
                    playerPosition.y -= speed;
                break;
                case 1:
                    playerPosition.x += speed;
                break;
                case 2:
                    playerPosition.y += speed;
                break;
                case 3:
                    playerPosition.x -= speed;
                break;
            }
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        {
            ClearBackground(RAYWHITE);

            // Draw either the moving, or standing animation.
            if (playerMoving) {
                DrawAsepriteTagEx(moving[direction], playerPosition, 0, scale, WHITE);
            }
            else {
                DrawAsepriteTagEx(standing[direction], playerPosition, 0, scale, WHITE);
            }
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
