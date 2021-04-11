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
*   raylib-physfs is licensed under an unmodified zlib/libpng license, which is an OSI-certified,
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

ase_t* LoadAseprite(const char* fileName);
ase_t* LoadAsepriteFromMemory(unsigned char* fileData, unsigned int size);
Texture GetAsepriteTexture(ase_t* ase);
void UnloadAseprite(ase_t* ase);
void TraceAseprite(ase_t* ase);
Color GetColorFromAsepriteColor(ase_color_t color);
void DrawAseprite(ase_t* ase, int frame, int posX, int posY, Color tint);
void DrawAsepriteV(ase_t* ase, int frame, Vector2 position, Color tint);
void DrawAsepriteEx(ase_t* ase, int frame, Vector2 position, float rotation, float scale, Color tint);
void DrawAsepritePro(ase_t* ase, int frame, Rectangle dest, Vector2 origin, float rotation, Color tint);

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

#define CUTE_ASEPRITE_WARNING(msg) TraceLog(LOG_WARNING, msg, __LINE__)

#define CUTE_ASEPRITE_FILEIO
#define CUTE_ASEPRITE_SEEK_SET 0
#define CUTE_ASEPRITE_SEEK_END 0
#define CUTE_ASEPRITE_FILE void
CUTE_ASEPRITE_FILE* raylib_aseprite_fopen(const char* file, const char* property) {
    return 0;
}
void raylib_aseprite_fseek(CUTE_ASEPRITE_FILE* fp, int sz, int pos) {
    (void*)fp;
    (void)sz;
    (void)pos;
}
void raylib_aseprite_fread(char* data, int sz, int num, CUTE_ASEPRITE_FILE* fp) {
    (void*)fp;
}
int raylib_aseprite_ftell(CUTE_ASEPRITE_FILE* fp) {
    return 0;
}
void raylib_aseprite_fclose(CUTE_ASEPRITE_FILE* fp) {
    (void*)fp;
}
#define CUTE_ASEPRITE_FOPEN raylib_aseprite_fopen
#define CUTE_ASEPRITE_FSEEK raylib_aseprite_fseek
#define CUTE_ASEPRITE_FREAD raylib_aseprite_fread
#define CUTE_ASEPRITE_FTELL raylib_aseprite_ftell
#define CUTE_ASEPRITE_FCLOSE raylib_aseprite_fclose

#define CUTE_ASEPRITE_ALLOC(size, ctx) MemAlloc(size)
#define CUTE_ASEPRITE_FREE(mem, ctx) MemFree(mem)

#include "cute_aseprite.h" // NOLINT

#ifdef __cplusplus
extern "C" {
#endif

ase_t* LoadAsepriteFromMemory(unsigned char* fileData, unsigned int size) {
    ase_t* ase = cute_aseprite_load_from_memory(fileData, size, 0);
    if (ase == 0) {
        TraceLog(LOG_ERROR, "ASEPRITE: Error loading Aseprite");
        return 0;
    }

    // Build the sprite's final image.
    Image image = GenImageColor(ase->w * ase->frame_count, ase->h, BLANK);

    // Load all frames.
    for (int i = 0; i < ase->frame_count; i++) {
        ase_frame_t* frame = ase->frames + i;
        Rectangle dest = {i * ase->w, 0, ase->w, ase->h};
        Rectangle src = {0, 0, ase->w, ase->h};
        Image frameImage = {
            .data = frame->pixels,
            .width = ase->w,
            .height = ase->h,
            .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8,
            .mipmaps = 1
        };
        ImageDraw(&image, frameImage, src, dest, WHITE);
    }

    // Transparent Pixel
    int transparency  = ase->transparent_palette_entry_index;
    if (transparency >= 0 && transparency < ase->palette.entry_count) {
        Color source = GetColorFromAsepriteColor(ase->palette.entries[transparency].color);
        ImageColorReplace(&image, source, BLANK);
    }

    // Create the Texture.
    Texture2D texture = LoadTextureFromImage(image);
    UnloadImage(image);

    // Finalize the texture.
    GenTextureMipmaps(&texture);
    SetTextureFilter(texture, TEXTURE_FILTER_POINT);

    // Save the texture as the Aseprite context.
    ase->mem_ctx = MemAlloc(sizeof(Texture2D));
    Texture2D* texturePointer = ase->mem_ctx;
    texturePointer->format = texture.format;
    texturePointer->id = texture.id;
    texturePointer->mipmaps = texture.mipmaps;
    texturePointer->width = texture.width;
    texturePointer->height = texture.height;
    return ase;
}

ase_t* LoadAseprite(const char* fileName) {
    unsigned int bytesRead;
    unsigned char* fileData = LoadFileData(fileName, &bytesRead);
    if (bytesRead == 0 || fileData == 0) {
        TraceLog(LOG_ERROR, "ASEPRITE: Failed to load aseprite file.");
        return 0;
    }

    return LoadAsepriteFromMemory(fileData, bytesRead);
}

Texture GetAsepriteTexture(ase_t* ase) {
    Texture2D* texturePointer = (Texture2D*)ase->mem_ctx;
    return *texturePointer;
}

Color GetColorFromAsepriteColor(ase_color_t color) {
    Color output = {color.r, color.g, color.b, color.a};
    return output;
}

void UnloadAseprite(ase_t* ase) {
    // Destroy the texture.
    if (ase->mem_ctx != 0) {
        // Unload the texture from the GPU.
        UnloadTexture(GetAsepriteTexture(ase));

        // Unload the texture data.
        MemFree(ase->mem_ctx);
    }

    // Destory the aseprite data.
    cute_aseprite_free(ase);
}

void DrawAseprite(ase_t* ase, int frame, int posX, int posY, Color tint) {
    Vector2 position = {posX, posY};
    DrawAsepriteV(ase, frame, position, tint);
}

void DrawAsepriteV(ase_t* ase, int frame, Vector2 position, Color tint) {
    if (frame > ase->frame_count) {
        return;
    }
    Rectangle source = {frame * ase->w, 0, ase->w, ase->h};
    Texture2D texture = GetAsepriteTexture(ase);
    DrawTextureRec(texture, source, position, tint);
}

void DrawAsepriteEx(ase_t* ase, int frame, Vector2 position, float rotation, float scale, Color tint) {
    if (frame > ase->frame_count) {
        return;
    }
    Rectangle source = {frame * ase->w, 0, ase->w, ase->h};
    Texture2D texture = GetAsepriteTexture(ase);
    Rectangle dest = {position.x, position.y, ase->w * scale, ase->h * scale};
    Vector2 origin = {0, 0};
    DrawTexturePro(texture, source, dest, origin, rotation, tint);           // Draw a part of a texture defined by a rectangle with 'pro' parameters
}

void DrawAsepritePro(ase_t* ase, int frame, Rectangle dest, Vector2 origin, float rotation, Color tint) {
    if (frame > ase->frame_count) {
        return;
    }
    Rectangle source = {frame * ase->w, 0, ase->w, ase->h};
    Texture2D texture = GetAsepriteTexture(ase);
    DrawTexturePro(texture, source, dest, origin, rotation, tint);
}

void TraceAseprite(ase_t* ase) {
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

#ifdef __cplusplus
}
#endif

#endif  // RAYLIB_ASEPRITE_IMPLEMENTATION_ONCE
#endif  // RAYLIB_ASEPRITE_IMPLEMENTATION
