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
    Aseprite aseprite = LoadAseprite("resources/numbers.aseprite");
    assert(aseprite.ase != NULL);
    assert(aseprite.ase->frame_count > 20);
    assert(aseprite.ase->frame_count < 40);

    // IsAsepriteValid()
    assert(IsAsepriteValid(aseprite));

    // GetAsepriteWidth()
    assert(GetAsepriteWidth(aseprite) == 64);

    // GetAsepriteHeight()
    assert(GetAsepriteHeight(aseprite) == 64);

    // GetAsepriteTagCount()
    assert(GetAsepriteTagCount(aseprite) == 3);

    // TraceAseprite()
    TraceAseprite(aseprite);

    // GetAsepriteTagCount()
    assert(GetAsepriteTagCount(aseprite) == 3);

    // LoadAsepriteTag()
    AsepriteTag tag = LoadAsepriteTag(aseprite, "Backwards");
    assert(tag.timer > 0);
    Color expected = (Color){0, 135, 81, 255};
    assert(tag.color.r == expected.r);
    assert(tag.color.g == expected.g);
    assert(tag.color.b == expected.b);
    assert(tag.color.a == expected.a);
    assert(TextIsEqual(tag.name, "Backwards"));

    // IsAsepriteTagValid()
    assert(IsAsepriteTagValid(tag));

    // LoadAsepriteTagFromIndex()
    {
        AsepriteTag tag2 = LoadAsepriteTagFromIndex(aseprite, 2);
        assert(tag2.speed == 1.0f);
        assert(tag2.currentFrame == 20);
        assert(TextIsEqual(tag2.name, "Ping-Pong"));
    }

    // SetAsepriteTagFrame()
    {
        AsepriteTag tag = LoadAsepriteTagFromIndex(aseprite, 2);
        SetAsepriteTagFrame(&tag, 4);

        int frame = GetAsepriteTagFrame(tag);
        assert(frame == 4);

        SetAsepriteTagFrame(&tag, -3);
        frame = GetAsepriteTagFrame(tag);
        assert(frame == 9 - 3);
    }

    // GetAsepriteTexture()
    Texture texture = GetAsepriteTexture(aseprite);
    assert(texture.width > 50);
    assert(texture.height > 50);

    BeginDrawing();
    {
        // DrawAseprite()
        DrawAseprite(aseprite, 3, 10, 10, WHITE);
        // DrawAsepriteV()
        DrawAsepriteV(aseprite, 5, (Vector2){10, 20}, WHITE);
        // DrawAsepriteEx()
        DrawAsepriteEx(aseprite, 6, (Vector2){10, 30}, 20, 3, WHITE);
        // DrawAsepritePro()
        DrawAsepritePro(aseprite, 7, (Rectangle){30, 30, 20, 20}, (Vector2){0, 0}, 0.5f, WHITE);

        // DrawAsepriteTag()
        DrawAsepriteTag(tag, 10, 10, WHITE);
        // DrawAsepriteTagV()
        DrawAsepriteTagV(tag, (Vector2){10, 20}, WHITE);
        // DrawAsepriteTagEx()
        DrawAsepriteTagEx(tag, (Vector2){10, 30}, 20, 3, WHITE);
        // DrawAsepriteTagPro()
        DrawAsepriteTagPro(tag, (Rectangle){30, 30, 20, 20}, (Vector2){0, 0}, 0.5f, WHITE);

        // UpdateAsepriteTag()
        UpdateAsepriteTag(&tag);
        UpdateAsepriteTag(NULL); // Expect warning
    }
    EndDrawing();

    // GetAsepriteSliceCount()
    assert(GetAsepriteSliceCount(aseprite) == 2);

    // LoadAsepriteSlice()
    {
        AsepriteSlice slice = LoadAsepriteSlice(aseprite, "Label");
        assert(slice.bounds.x > 20);
        assert(TextIsEqual(slice.name, "Label"));
        assert(slice.bounds.y > 20);
        assert(slice.bounds.width > 2);
        assert(slice.bounds.height > 2);
    }

    // LoadAsperiteSliceFromIndex()
    {
        AsepriteSlice slice = LoadAsperiteSliceFromIndex(aseprite, 1);
        assert(TextIsEqual(slice.name, "Number"));
    }

    // IsAsepriteSliceValid()
    {
        AsepriteSlice slice = LoadAsperiteSliceFromIndex(aseprite, 0);
        assert(IsAsepriteSliceValid(slice));

        AsepriteSlice noSlice;
        noSlice.name = "";
        assert(!IsAsepriteSliceValid(noSlice));

        noSlice = LoadAsperiteSliceFromIndex(aseprite, 100);
        assert(!IsAsepriteSliceValid(noSlice));
    }

    // GenAsepriteSliceDefault()
    AsepriteSlice defaultSlice = GenAsepriteSliceDefault();
    assert(TextLength(defaultSlice.name) == 0);

    // UnloadAseprite()
    UnloadAseprite(aseprite);

    CloseWindow();
    TraceLog(LOG_INFO, "================================");
    TraceLog(LOG_INFO, "raylib-aseprite tests succesful");
    TraceLog(LOG_INFO, "================================");

    return 0;
}
