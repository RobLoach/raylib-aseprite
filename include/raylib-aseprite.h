/**********************************************************************************************
*
*   raylib-aseprite - Aseprite sprite loader for raylib.
*
*   Copyright 2021 Rob Loach (@RobLoach)
*
*   DEPENDENCIES:
*       raylib https://www.raylib.com/
*
*   LICENSE: zlib/libpng
*
*   raylib-aseprite is licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software:
*
*   This software is provided "as-is", without any express or implied warranty. In no event
*   will the authors be held liable for any damages arising from the use of this software.
*
*   Permission is granted to anyone to use this software for any purpose, including commercial
*   applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
*     1. The origin of this software must not be misrepresented; you must not claim that you
*     wrote the original software. If you use this software in a product, an acknowledgment
*     in the product documentation would be appreciated but is not required.
*
*     2. Altered source versions must be plainly marked as such, and must not be misrepresented
*     as being the original software.
*
*     3. This notice may not be removed or altered from any source distribution.
*
**********************************************************************************************/

#ifndef INCLUDE_RAYLIB_ASEPRITE_H_
#define INCLUDE_RAYLIB_ASEPRITE_H_

#include "raylib.h" // NOLINT
#include "./cute_aseprite.h" // NOLINT

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Aseprite {
    ase_t* ase;
} Aseprite;

typedef struct AsepriteTag {
    ase_tag_t* tag;
    Aseprite aseprite;
    int currentFrame;
    float timer;
    int direction;
    float speed;
} AsepriteTag;

Aseprite LoadAseprite(const char* fileName);                        // Load an .aseprite file
Aseprite LoadAsepriteFromMemory(unsigned char* fileData, unsigned int size);  // Load an aseprite file from memory
void UnloadAseprite(Aseprite aseprite);                             // Unloads the aseprite file
void TraceAseprite(Aseprite aseprite);                              // Display all information associated with the aseprite
Texture GetAsepriteTexture(Aseprite aseprite);                      // Retrieve the raylib texture associated with the aseprite
void DrawAseprite(Aseprite aseprite, int frame, int posX, int posY, Color tint);
void DrawAsepriteV(Aseprite aseprite, int frame, Vector2 position, Color tint);
void DrawAsepriteEx(Aseprite aseprite, int frame, Vector2 position, float rotation, float scale, Color tint);
void DrawAsepritePro(Aseprite aseprite, int frame, Rectangle dest, Vector2 origin, float rotation, Color tint);

AsepriteTag LoadAsepriteTag(Aseprite aseprite, const char* name);   // Load a Aseprite tag animation sequence
AsepriteTag LoadAsepriteTagFromId(Aseprite aseprite, int id);       // Load a Aseprite tag animation sequence from its index
void UpdateAsepriteTag(AsepriteTag* tag);                           // Update the tag animation frame if needed
void DrawAsepriteTag(AsepriteTag tag, int posX, int posY, Color tint);
void DrawAsepriteTagV(AsepriteTag tag, Vector2 position, Color tint);
void DrawAsepriteTagEx(AsepriteTag tag, Vector2 position, float rotation, float scale, Color tint);
void DrawAsepriteTagPro(AsepriteTag tag, Rectangle dest, Vector2 origin, float rotation, Color tint);
const char* GetAsepriteTagName(AsepriteTag tag);                    // Retrieve the given tag's name
int GetAspriteTagCount(Aseprite aseprite);                          // Get the total amount of available tags from the loaded Aseprite

#ifdef __cplusplus
}
#endif

#endif  // INCLUDE_RAYLIB_ASEPRITE_H_

#ifdef RAYLIB_ASEPRITE_IMPLEMENTATION
#ifndef RAYLIB_ASEPRITE_IMPLEMENTATION_ONCE
#define RAYLIB_ASEPRITE_IMPLEMENTATION_ONCE

#ifndef CUTE_ASEPRITE_IMPLEMENTATION
#define CUTE_ASEPRITE_IMPLEMENTATION
#endif

#define CUTE_ASEPRITE_WARNING(msg) TraceLog(LOG_WARNING, "ASEPRITE: %s (cute_headers.h:%i)", msg, __LINE__)

#define CUTE_ASEPRITE_ASSERT(condition) if (!(condition)) { TraceLog(LOG_ERROR, "ASEPRITE: Failed assert condition in cute_headers.h:%i", __LINE__); }

// Override how Cute attempts to load files.
#define CUTE_ASEPRITE_FILEIO
#define CUTE_ASEPRITE_SEEK_SET 0
#define CUTE_ASEPRITE_SEEK_END 0
#define CUTE_ASEPRITE_FILE void

CUTE_ASEPRITE_FILE* raylib_aseprite_fopen(const char* file, const char* property) {
    (void)file;
    (void)property;
    return 0;
}

void raylib_aseprite_fseek(CUTE_ASEPRITE_FILE* fp, int sz, int pos) {
    (void)fp;
    (void)sz;
    (void)pos;
}

void raylib_aseprite_fread(char* data, int sz, int num, CUTE_ASEPRITE_FILE* fp) {
    (void)data;
    (void)sz;
    (void)num;
    (void)fp;
}

int raylib_aseprite_ftell(CUTE_ASEPRITE_FILE* fp) {
    (void)fp;
    return 0;
}

void raylib_aseprite_fclose(CUTE_ASEPRITE_FILE* fp) {
    (void)fp;
}

#define CUTE_ASEPRITE_FOPEN raylib_aseprite_fopen
#define CUTE_ASEPRITE_FSEEK raylib_aseprite_fseek
#define CUTE_ASEPRITE_FREAD raylib_aseprite_fread
#define CUTE_ASEPRITE_FTELL raylib_aseprite_ftell
#define CUTE_ASEPRITE_FCLOSE raylib_aseprite_fclose

// Have Cute use raylib's memory functions.
#define CUTE_ASEPRITE_ALLOC(size, ctx) MemAlloc(size)
#define CUTE_ASEPRITE_FREE(mem, ctx) MemFree(mem)

#include "cute_aseprite.h" // NOLINT

#ifdef __cplusplus
extern "C" {
#endif

Aseprite LoadAsepriteFromMemory(unsigned char* fileData, unsigned int size) {
    struct Aseprite aseprite;
    ase_t* ase = cute_aseprite_load_from_memory(fileData, (int)size, 0);
    if (ase == 0) {
        aseprite.ase = 0;
        return aseprite;
    }

    // Build the sprite's final image.
    Image image = GenImageColor(ase->w * ase->frame_count, ase->h, BLANK);

    // Load all frames.
    for (int i = 0; i < ase->frame_count; i++) {
        ase_frame_t* frame = ase->frames + i;
        Rectangle dest = {(float)(i * ase->w), 0, (float)ase->w, (float)ase->h};
        Rectangle src = {0, 0, (float)ase->w, (float)ase->h};
        Image frameImage = {
            .data = frame->pixels,
            .width = ase->w,
            .height = ase->h,
            .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8,
            .mipmaps = 1
        };
        ImageDraw(&image, frameImage, src, dest, WHITE);
    }

    // Apply the transparent pixel.
    int transparency  = ase->transparent_palette_entry_index;
    if (transparency >= 0 && transparency < ase->palette.entry_count) {
        ase_color_t transparentColor = ase->palette.entries[transparency].color;
        Color source = {
            .a = transparentColor.a,
            .r = transparentColor.r,
            .g = transparentColor.g,
            .b = transparentColor.b
        };
        ImageColorReplace(&image, source, BLANK);
    }

    // Create the Texture
    Texture2D texture = LoadTextureFromImage(image);

    // Now that the texture is loaded into the GPU, we can clear the image.
    UnloadImage(image);

    // Save the texture as the Aseprite context.
    ase->mem_ctx = MemAlloc(sizeof(Texture2D));
    Texture2D* texturePointer = ase->mem_ctx;
    texturePointer->format = texture.format;
    texturePointer->id = texture.id;
    texturePointer->mipmaps = texture.mipmaps;
    texturePointer->width = texture.width;
    texturePointer->height = texture.height;
    aseprite.ase = ase;
    return aseprite;
}

Aseprite LoadAseprite(const char* fileName) {
    unsigned int bytesRead;
    unsigned char* fileData = LoadFileData(fileName, &bytesRead);
    if (bytesRead == 0 || fileData == 0) {
        TraceLog(LOG_ERROR, "ASEPRITE: Failed to load aseprite file %s", fileName);
        struct Aseprite aseprite;
        aseprite.ase = 0;
        return aseprite;
    }

    Aseprite ase = LoadAsepriteFromMemory(fileData, bytesRead);
    UnloadFileData(fileData);
    return ase;
}

inline Texture GetAsepriteTexture(Aseprite aseprite) {
    Texture2D* texturePointer = (Texture2D*)aseprite.ase->mem_ctx;
    return *texturePointer;
}

void UnloadAseprite(Aseprite aseprite) {
    ase_t* ase = aseprite.ase;
    // Destroy the texture.
    if (ase->mem_ctx != 0) {
        // Unload the texture from the GPU.
        UnloadTexture(GetAsepriteTexture(aseprite));

        // Unload the texture data.
        MemFree(ase->mem_ctx);
    }

    // Destory the aseprite data.
    cute_aseprite_free(ase);
}

void DrawAseprite(Aseprite aseprite, int frame, int posX, int posY, Color tint) {
    Vector2 position = {(float)posX, (float)posY};
    DrawAsepriteV(aseprite, frame, position, tint);
}

void DrawAsepriteV(Aseprite aseprite, int frame, Vector2 position, Color tint) {
    ase_t* ase = aseprite.ase;
    if (ase == 0 || frame < 0 || frame >= ase->frame_count) {
        return;
    }

    Rectangle source = {(float)(frame * ase->w), 0, (float)ase->w, (float)ase->h};
    Texture2D texture = GetAsepriteTexture(aseprite);
    DrawTextureRec(texture, source, position, tint);
}

void DrawAsepriteEx(Aseprite aseprite, int frame, Vector2 position, float rotation, float scale, Color tint) {
    ase_t* ase = aseprite.ase;
    if (ase == 0 || frame < 0 || frame >= ase->frame_count) {
        return;
    }

    Rectangle source = {(float)(frame * ase->w), 0, (float)ase->w, (float)ase->h};
    Texture2D texture = GetAsepriteTexture(aseprite);
    Rectangle dest = {(float)position.x, (float)position.y, (float)(ase->w * scale), (float)(ase->h * scale)};
    Vector2 origin = {0, 0};
    DrawTexturePro(texture, source, dest, origin, rotation, tint);           // Draw a part of a texture defined by a rectangle with 'pro' parameters
}

void DrawAsepritePro(Aseprite aseprite, int frame, Rectangle dest, Vector2 origin, float rotation, Color tint) {
    ase_t* ase = aseprite.ase;
    if (ase == 0 || frame < 0 || frame >= ase->frame_count) {
        return;
    }

    Rectangle source = {(float)(frame * ase->w), 0, (float)ase->w, (float)ase->h};
    Texture2D texture = GetAsepriteTexture(aseprite);
    DrawTexturePro(texture, source, dest, origin, rotation, tint);
}

void TraceAseprite(Aseprite aseprite) {
    ase_t* ase = aseprite.ase;
    if (ase == 0) {
        TraceLog(LOG_INFO, "ASEPRITE: Empty file information");
        return;
    }

    TraceLog(LOG_INFO, "ASEPRITE: File information:");
    TraceLog(LOG_INFO, "    > Size:   %ix%i", ase->w, ase->h);
    TraceLog(LOG_INFO, "    > Frames: %i", ase->frame_count);
    TraceLog(LOG_INFO, "    > Slices: %i", ase->slice_count);
    TraceLog(LOG_INFO, "    > Colors: %i", ase->number_of_colors);
    TraceLog(LOG_INFO, "    > Mode:   %i", ase->mode);
    TraceLog(LOG_INFO, "    > Layers: %i", ase->layer_count);
    for (int i = 0; i < ase->layer_count; i++) {
        ase_layer_t* layer = ase->layers + i;
        TraceLog(LOG_INFO, "      - %s", layer->name);
    }

    TraceLog(LOG_INFO, "    > Tags:   %i", ase->tag_count);
    for (int i = 0; i < ase->tag_count; i++) {
        ase_tag_t* tag = ase->tags + i;
        TraceLog(LOG_INFO, "      - %s", tag->name);
    }
}

void UpdateAsepriteTag(AsepriteTag* tag) {
    if (tag == 0 || tag->tag == 0 || tag->aseprite.ase == 0) {
        TraceLog(LOG_ERROR, "ASEPRITE: Cannot update empty tag");
        return;
    }

    ase_t* ase = tag->aseprite.ase;
    ase_tag_t* aseTag = tag->tag;

    // Count down the timer and see if it's time to update the frame.
    tag->timer -= GetFrameTime() * tag->speed;
    if (tag->timer > 0) {
        return;
    }

    // Advance the frame and see if it's time to reset the position.
    tag->currentFrame += tag->direction;
    switch (aseTag->loop_animation_direction) {
        case ASE_ANIMATION_DIRECTION_BACKWORDS:
            if (tag->currentFrame < aseTag->from_frame) {
                tag->currentFrame = aseTag->to_frame;
            }
        break;
        case ASE_ANIMATION_DIRECTION_FORWARDS:
            if (tag->currentFrame > aseTag->to_frame) {
                tag->currentFrame = aseTag->from_frame;
            }
        break;
        case ASE_ANIMATION_DIRECTION_PINGPONG:
            if (tag->direction > 0) {
                if (tag->currentFrame > aseTag->to_frame) {
                    tag->direction = -1;
                    tag->currentFrame = aseTag->to_frame - 1;
                }
            }
            else {
                if (tag->currentFrame < aseTag->from_frame) {
                    tag->direction = 1;
                    tag->currentFrame = aseTag->from_frame + 1;
                }
            }
        break;
    }

    // Reset the timer.
    // TODO: Add the original tag->timer to make up the different in frame time?
    tag->timer = (float)(ase->frames[tag->currentFrame].duration_milliseconds) / 1000.0f/* + tag->timer; */;
}

void DrawAsepriteTag(AsepriteTag tag, int posX, int posY, Color tint) {
    DrawAseprite(tag.aseprite, tag.currentFrame, posX, posY, tint);
}

void DrawAsepriteTagV(AsepriteTag tag, Vector2 position, Color tint) {
    DrawAsepriteV(tag.aseprite, tag.currentFrame, position, tint);
}

void DrawAsepriteTagEx(AsepriteTag tag, Vector2 position, float rotation, float scale, Color tint) {
    DrawAsepriteEx(tag.aseprite, tag.currentFrame, position, rotation, scale, tint);
}

void DrawAsepriteTagPro(AsepriteTag tag, Rectangle dest, Vector2 origin, float rotation, Color tint) {
    DrawAsepritePro(tag.aseprite, tag.currentFrame, dest, origin, rotation, tint);
}

AsepriteTag LoadAsepriteTagFromId(Aseprite aseprite, int id) {
    struct AsepriteTag tag;
    tag.aseprite.ase = 0;
    tag.currentFrame = 0;
    tag.tag = 0;
    tag.timer = 0;
    tag.direction = 0;
    tag.speed = 1.0f;
    ase_t* ase = aseprite.ase;
    if (ase == 0) {
        TraceLog(LOG_ERROR, "ASEPRITE: Asprite not loaded when attempting to load tag #%i", id);
        return tag;
    }

    if (id < 0 || id >= ase->tag_count) {
        TraceLog(LOG_ERROR, "ASEPRITE: Tag index %i out of range for %i tags", id, ase->tag_count);
        return tag;
    }

    tag.aseprite.ase = aseprite.ase;
    tag.tag = &ase->tags[id];
    tag.currentFrame = tag.tag->from_frame;
    tag.direction = 1;
    if (tag.tag->loop_animation_direction == ASE_ANIMATION_DIRECTION_BACKWORDS) {
        tag.currentFrame = tag.tag->to_frame;
        tag.direction = -1;
    }
    tag.timer = (float)(ase->frames[tag.currentFrame].duration_milliseconds) / 1000.0f; // Timer in seconds.
    return tag;
}

AsepriteTag LoadAsepriteTag(Aseprite aseprite, const char* name) {
    struct AsepriteTag tag;
    tag.aseprite.ase = 0;
    tag.currentFrame = 0;
    tag.tag = 0;
    tag.timer = 0;
    tag.direction = 0;
    tag.speed = 1.0f;
    ase_t* ase = aseprite.ase;
    if (ase == 0) {
        TraceLog(LOG_ERROR, "ASEPRITE: Asprite not loaded when attempting to load tag '%s'", name);
        return tag;
    }

    // Loop through all tags to find the correct name.
    for (int i = 0; i < ase->tag_count; i++) {
        if (TextIsEqual(name, ase->tags[i].name)) {
            return LoadAsepriteTagFromId(aseprite, i);
        }
    }

    TraceLog(LOG_WARNING, "ASEPRITE: Could not find tag %s", name);
    return tag;
}

const char* GetAsepriteTagName(AsepriteTag tag) {
    if (tag.tag == 0) {
        TraceLog(LOG_WARNING, "ASEPRITE: Cannot get name of missing tag");
        return 0;
    }

    return tag.tag->name;
}

int GetAspriteTagCount(Aseprite aseprite) {
    if (aseprite.ase == 0) {
        TraceLog(LOG_WARNING, "ASEPRITE: Cannot get tag count when there is not loaded aseprite");
        return 0;
    }

    return aseprite.ase->tag_count;
}

#ifdef __cplusplus
}
#endif

#endif  // RAYLIB_ASEPRITE_IMPLEMENTATION_ONCE
#endif  // RAYLIB_ASEPRITE_IMPLEMENTATION
