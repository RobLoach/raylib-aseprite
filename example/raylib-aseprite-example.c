/*******************************************************************************************
*
*   [raylib-aseprite] example - Load a Aseprite file, and display the animated sprites.
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
    const int screenWidth = 640;
    const int screenHeight = 480;
    InitWindow(screenWidth, screenHeight, "[raylib-aseprite] example");

    // Load the Aseprite file.
    ase_t* ase = LoadAseprite("resources/backpacker.aseprite");

    // Display information about it.
    TraceAseprite(ase);

    // Build all the frame information for each tag.
    int frame[ase->tag_count];
    float frameTimer[ase->tag_count];
    for (int i = 0; i < ase->tag_count; i++) {
        frame[i] = ase->tags[i].from_frame;
        frameTimer[i] = (float)(ase->frames[frame[i]].duration_milliseconds) / 1000.0f;
    }
    //--------------------------------------------------------------------------------------

    while(!WindowShouldClose()) {

        // Update
        //----------------------------------------------------------------------------------
        float timeSpend = GetFrameTime();
        for (int i = 0; i < ase->tag_count; i++) {
            ase_tag_t tag = ase->tags[i];
            frameTimer[i] -= timeSpend;
            if (frameTimer[i] <= 0) {
                frame[i]++;
                if (frame[i] > tag.to_frame) {
                    frame[i] = tag.from_frame;
                }
                frameTimer[i] = (float)(ase->frames[frame[i]].duration_milliseconds) / 1000.0f;
            }
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Loop through each tag, and display the animated sprite.
        for (int i = 0; i < ase->tag_count; i++) {
            ase_tag_t tag = ase->tags[i];
            DrawText(tag.name, 170, i * 115 + 90, 40, BLACK);
            Vector2 position = {100, i * 115 + 70};

            // Draw the active frame.
            DrawAsepriteEx(ase, frame[i], position, 0, 6, WHITE);
        }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------

    UnloadAseprite(ase);    // Unload Aseprite

    CloseWindow();
    //--------------------------------------------------------------------------------------

    return 0;
}
