#include "raylib.h"

#define RAYLIB_ASEPRITE_IMPLEMENTATION
#include "raylib-aseprite.h"

int main() {
    InitWindow(640, 480, "[raylib-aseprite] Example");

    ase_t* ase = LoadAseprite("resources/backpacker.aseprite");
    TraceAseprite(ase);

    // Build all the frame information for each tag.
    int frame[ase->tag_count];
    float frameTimer[ase->tag_count];
    for (int i = 0; i < ase->tag_count; i++) {
        frame[i] = ase->tags[i].from_frame;
        frameTimer[i] = (float)(ase->frames[frame[i]].duration_milliseconds) / 1000.0f;
    }

    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Update the frame time.
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

        // Render
        for (int i = 0; i < ase->tag_count; i++) {
            ase_tag_t tag = ase->tags[i];
            DrawText(tag.name, 150, i * 100 + 80, 30, BLACK);
            Vector2 position = {100, i * 100 + 70};
            DrawAsepriteEx(ase, frame[i], position, 0, 4, WHITE);
        }

        EndDrawing();
    }

    UnloadAseprite(ase);
    CloseWindow();
    return 0;
}
