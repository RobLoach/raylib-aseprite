/**********************************************************************************************
*
*   raylib-aseprite - Aseprite sprite loader for raylib.
*
*   Copyright 2021 Rob Loach (@RobLoach)
*
*   DEPENDENCIES:
*       raylib 5.0+ https://www.raylib.com/
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
#include "cute_aseprite.h" // NOLINT

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Aseprite object containing a pointer to the ase_t* from cute_aseprite.h.
 *
 * @see LoadAseprite()
 * @see UnloadAseprite()
 */
typedef struct Aseprite {
    ase_t* ase;         // Pointer to the cute_aseprite data.
} Aseprite;

/**
 * Tag information from an Aseprite object.
 *
 * @see LoadAsepriteTag()
 * @see LoadAsepriteTagFromIndex()
 */
typedef struct AsepriteTag {
    char* name;         // The name of the tag.
    int currentFrame;   // The frame that the tag is currently on
    float timer;        // The countdown timer in seconds
    int direction;      // Whether we are moving forwards, or backwards through the frames
    float speed;        // The animation speed factor (1 is normal speed, 2 is double speed)
    Color color;        // The color provided for the tag
    bool loop;          // Whether to continue to play the animation when the animation finishes
    bool paused;        // Set to true to not progression of the animation
    Aseprite aseprite;  // The loaded Aseprite file
    ase_tag_t* tag;     // The active tag to act upon
} AsepriteTag;

/**
 * Slice data for the Aseprite.
 *
 * @see LoadAsepriteSlice()
 * @see https://www.aseprite.org/docs/slices/
 */
typedef struct AsepriteSlice {
    char* name;         // The name of the slice.
    Rectangle bounds;   // The rectangle outer bounds for the slice.
} AsepriteSlice;

// Aseprite functions
Aseprite LoadAseprite(const char* fileName);                        // Load an .aseprite file
Aseprite LoadAsepriteFromMemory(unsigned char* fileData, int size);  // Load an aseprite file from memory
bool IsAsepriteValid(Aseprite aseprite);                            // Check if the given Aseprite was loaded successfully
void UnloadAseprite(Aseprite aseprite);                             // Unloads the aseprite file
void TraceAseprite(Aseprite aseprite);                              // Display all information associated with the aseprite
Texture GetAsepriteTexture(Aseprite aseprite);                      // Retrieve the raylib texture associated with the aseprite
int GetAsepriteWidth(Aseprite aseprite);                            // Get the width of the sprite
int GetAsepriteHeight(Aseprite aseprite);                           // Get the height of the sprite
void DrawAseprite(Aseprite aseprite, int frame, int posX, int posY, Color tint);
void DrawAsepriteFlipped(Aseprite aseprite, int frame, int posX, int posY, bool horizontalFlip, bool verticalFlip, Color tint);
void DrawAsepriteV(Aseprite aseprite, int frame, Vector2 position, Color tint);
void DrawAsepriteVFlipped(Aseprite aseprite, int frame, Vector2 position, bool horizontalFlip, bool verticalFlip, Color tint);
void DrawAsepriteExFlipped(Aseprite aseprite, int frame, Vector2 position, float rotation, float scale, bool horizontalFlip, bool verticalFlip, Color tint);
void DrawAsepritePro(Aseprite aseprite, int frame, Rectangle dest, Vector2 origin, float rotation, Color tint);
void DrawAsepriteProFlipped(Aseprite aseprite, int frame, Rectangle dest, Vector2 origin, float rotation, bool horizontalFlip, bool verticalFlip, Color tint);

// Aseprite Tag functions
AsepriteTag LoadAsepriteTag(Aseprite aseprite, const char* name);   // Load an Aseprite tag animation sequence
AsepriteTag LoadAsepriteTagFromIndex(Aseprite aseprite, int index); // Load an Aseprite tag animation sequence from its index
int GetAsepriteTagCount(Aseprite aseprite);                         // Get the total amount of available tags
bool IsAsepriteTagValid(AsepriteTag tag);                           // Check if the given Aseprite tag was loaded successfully
void UpdateAsepriteTag(AsepriteTag* tag);                           // Update the tag animation frame
AsepriteTag GenAsepriteTagDefault();                                // Generate an empty Tag with sane defaults
void DrawAsepriteTag(AsepriteTag tag, int posX, int posY, Color tint);
void DrawAsepriteTagFlipped(AsepriteTag tag, int posX, int posY, bool horizontalFlip, bool verticalFlip, Color tint);
void DrawAsepriteTagV(AsepriteTag tag, Vector2 position, Color tint);
void DrawAsepriteTagVFlipped(AsepriteTag tag, Vector2 position, bool horizontalFlip, bool verticalFlip, Color tint);
void DrawAsepriteTagEx(AsepriteTag tag, Vector2 position, float rotation, float scale, Color tint);
void DrawAsepriteTagExFlipped(AsepriteTag tag, Vector2 position, float rotation, float scale, bool horizontalFlip, bool verticalFlip, Color tint);
void DrawAsepriteTagPro(AsepriteTag tag, Rectangle dest, Vector2 origin, float rotation, Color tint);
void DrawAsepriteTagProFlipped(AsepriteTag tag, Rectangle dest, Vector2 origin, float rotation, bool horizontalFlip, bool verticalFlip, Color tint);
void SetAsepriteTagFrame(AsepriteTag* tag, int frameNumber);                           // Sets which frame the tag is currently displaying.
int GetAsepriteTagFrame(AsepriteTag tag);

// Aseprite Slice functions
AsepriteSlice LoadAsepriteSlice(Aseprite aseprite, const char* name);   // Load a slice from an Aseprite based on its name.
AsepriteSlice LoadAsperiteSliceFromIndex(Aseprite aseprite, int index); // Load a slice from an Aseprite based on its index.
int GetAsepriteSliceCount(Aseprite aseprite);                       // Get the amount of slices that are defined in the Aseprite.
bool IsAsepriteSliceValid(AsepriteSlice slice);                     // Return whether or not the given slice was found.
AsepriteSlice GenAsepriteSliceDefault();                            // Generate empty Aseprite slice data.

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

#ifdef __cplusplus
extern "C" {
#endif

// Have cute_aseprite report warnings through raylib.
#define CUTE_ASEPRITE_WARNING(msg) TraceLog(LOG_WARNING, "ASEPRITE: %s (cute_headers.h:%i)", msg, __LINE__)

#define CUTE_ASEPRITE_ASSERT(condition) do { if (!(condition)) { TraceLog(LOG_WARNING, "ASEPRITE: Failed assert \"%s\" in %s:%i", #condition, __FILE__, __LINE__); } } while(0)

#define CUTE_ASEPRITE_ALLOC(size, ctx) MemAlloc((unsigned int)(size))
#define CUTE_ASEPRITE_FREE(mem, ctx) MemFree((void*)(mem))

#define CUTE_ASEPRITE_SEEK_SET 0
#define CUTE_ASEPRITE_SEEK_END 0
#define CUTE_ASEPRITE_FILE void
#define CUTE_ASEPRITE_FOPEN(file, property) (CUTE_ASEPRITE_FILE*)file
#define CUTE_ASEPRITE_FSEEK(fp, sz, pos) TraceLog(LOG_ERROR, "ASEPRITE: fseek() was removed")
#define CUTE_ASEPRITE_FREAD(data, sz, num, fp) TraceLog(LOG_ERROR, "ASEPRITE: fread() was removed")
#define CUTE_ASEPRITE_FTELL(fp) (0)
#define CUTE_ASEPRITE_FCLOSE(fp) TraceLog(LOG_ERROR, "ASEPRITE: fclose() was removed")

#include "cute_aseprite.h" // NOLINT

/**
 * Load an .aseprite file through its memory data.
 *
 * @param fileData The loaded file data for the .aseprite file.
 * @param size The size of file in bytes.
 *
 * @see UnloadAseprite()
 * @see LoadAseprite()
 */
Aseprite LoadAsepriteFromMemory(unsigned char* fileData, int size) {
    struct Aseprite aseprite;
    aseprite.ase = 0;

    if (!IsWindowReady()) {
        TraceLog(LOG_ERROR, "ASEPRITE: Loading an Aseprite requires the Window to be running");
        return aseprite;
    }

    ase_t* ase = cute_aseprite_load_from_memory(fileData, (int)size, 0);
    if (ase == 0 || ase->frame_count == 0 || ase->w == 0 || ase->h == 0) {
        TraceLog(LOG_ERROR, "ASEPRITE: Failed to load Aseprite");
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
            .mipmaps = 1,
            .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8
        };
        ImageDraw(&image, frameImage, src, dest, WHITE);
    }

    // Apply the transparent pixel.
    int transparency  = ase->transparent_palette_entry_index;
    if (transparency >= 0 && transparency < ase->palette.entry_count) {
        ase_color_t transparentColor = ase->palette.entries[transparency].color;
        Color source = {
            .r = transparentColor.r,
            .g = transparentColor.g,
            .b = transparentColor.b,
            .a = transparentColor.a
        };
        ImageColorReplace(&image, source, BLANK);
    }

    // Create the Texture
    Texture2D texture = LoadTextureFromImage(image);

    // Now that the texture is loaded into the GPU, we can clear the image.
    UnloadImage(image);

    // Save the texture as the Aseprite context.
    ase->mem_ctx = MemAlloc(sizeof(Texture2D));
    Texture2D* texturePointer = (Texture2D*)ase->mem_ctx;
    texturePointer->format = texture.format;
    texturePointer->id = texture.id;
    texturePointer->mipmaps = texture.mipmaps;
    texturePointer->width = texture.width;
    texturePointer->height = texture.height;
    aseprite.ase = ase;
    TraceLog(LOG_INFO, "ASEPRITE: Loaded successfully (%ix%i - %i frames)", ase->w, ase->h, ase->frame_count);

    return aseprite;
}

/**
 * Load an .aseprite file.
 *
 * @param fileName The path to the file to load.
 *
 * @return The loaded Aseprite object, or an empty one on failure.
 *
 * @see UnloadAseprite()
 * @see IsAsepriteValid()
 */
Aseprite LoadAseprite(const char* fileName) {
    int bytesRead;
    unsigned char* fileData = LoadFileData(fileName, &bytesRead);
    if (bytesRead == 0 || fileData == 0) {
        TraceLog(LOG_ERROR, "ASEPRITE: Failed to load aseprite file \"%s\"", fileName);
        struct Aseprite aseprite;
        aseprite.ase = 0;
        return aseprite;
    }

    Aseprite ase = LoadAsepriteFromMemory(fileData, bytesRead);
    UnloadFileData(fileData);
    return ase;
}

/**
 * Determine whether or not the given Aseprite object was loaded successfully.
 *
 * @param aseprite The loaded Aseprite object.
 *
 * @return True if the Aseprite was loaded successfully, false otherwise.
 */
bool IsAsepriteValid(Aseprite aseprite) {
    return aseprite.ase != 0;
}

/**
 * Get the loaded raylib texture for the Aseprite.
 *
 * @param aseprite The loaded Aseprite object to retrieve the texture for.
 *
 * @return The internal texture associated with the Aseprite, or an empty Texture on failure.
 */
inline Texture GetAsepriteTexture(Aseprite aseprite) {
    if (aseprite.ase == 0) {
        struct Texture texture;
        TraceLog(LOG_WARNING, "ASEPRITE: Cannot get Texture from non-existant aseprite");
        texture.id = 0;
        texture.width = 0;
        texture.height = 0;
        texture.mipmaps = 0;
        texture.format = 0;
        return texture;
    }

    Texture2D* texturePointer = (Texture2D*)aseprite.ase->mem_ctx;
    return *texturePointer;
}

/**
 * Get the width of the aseprite sprite.
 *
 * @param aseprite The loaded Aseprite object to retrieve the width for.
 *
 * @return The width of the sprite, or 0 on failure.
 */
int GetAsepriteWidth(Aseprite aseprite) {
    if (aseprite.ase == 0) {
        TraceLog(LOG_WARNING, "ASEPRITE: Cannot get width from non-existant aseprite");
        return 0;
    }

    return aseprite.ase->w;
}

/**
 * Get the height of the aseprite sprite.
 *
 * @param aseprite The loaded Aseprite object to retrieve the height for.
 *
 * @return The height of the sprite, or 0 on failure.
 */
int GetAsepriteHeight(Aseprite aseprite) {
    if (aseprite.ase == 0) {
        TraceLog(LOG_WARNING, "ASEPRITE: Cannot get width from non-existant aseprite");
        return 0;
    }

    return aseprite.ase->h;
}

/**
 * Get the amount of tags defined in the aseprite sprite.
 *
 * @param aseprite The loaded Aseprite object to retrieve the amount of tags for.
 *
 * @return The number of tags that are defined within the aseprite, or 0 on failure.
 */
int GetAsepriteTagCount(Aseprite aseprite) {
    if (aseprite.ase == 0) {
        TraceLog(LOG_WARNING, "ASEPRITE: Cannot get tag count non-existant aseprite");
        return 0;
    }

    return aseprite.ase->tag_count;
}

/**
 * Unloads the given Aseprite. This will also unload the internal Texture.
 *
 * @param aseprite The loaded Aseprite object of which to unload.
 *
 * @see LoadAseprite()
 */
void UnloadAseprite(Aseprite aseprite) {
    ase_t* ase = aseprite.ase;
    if (ase == 0) {
        return;
    }

    // Destroy the texture.
    if (ase->mem_ctx != 0) {
        // Unload the texture from the GPU.
        UnloadTexture(GetAsepriteTexture(aseprite));

        // Unload the texture object.
        MemFree(ase->mem_ctx);
    }

    // Destory the aseprite data.
    cute_aseprite_free(ase);

    TraceLog(LOG_INFO, "ASEPRITE: Unloaded Aseprite data successfully");
}

void DrawAseprite(Aseprite aseprite, int frame, int posX, int posY, Color tint) {
    DrawAsepriteFlipped(aseprite, frame, posX, posY, false, false, tint);
}

void DrawAsepriteFlipped(Aseprite aseprite, int frame, int posX, int posY, bool horizontalFlip, bool verticalFlip, Color tint) {
    Vector2 position = {(float)posX, (float)posY};
    DrawAsepriteVFlipped(aseprite, frame, position, horizontalFlip, verticalFlip, tint);
}

void DrawAsepriteV(Aseprite aseprite, int frame, Vector2 position, Color tint) {
    DrawAsepriteVFlipped(aseprite, frame, position, false, false, tint);
}

void DrawAsepriteVFlipped(Aseprite aseprite, int frame, Vector2 position, bool horizontalFlip, bool verticalFlip, Color tint) {
    ase_t* ase = aseprite.ase;
    if (ase == 0 || frame < 0 || frame >= ase->frame_count) {
        return;
    }

    Rectangle source = {(float)(frame * ase->w), 0,
        horizontalFlip ? (float)-ase->w : (float)ase->w,
        verticalFlip ? (float)-ase->h : (float)ase->h
    };
    Texture2D texture = GetAsepriteTexture(aseprite);
    DrawTextureRec(texture, source, position, tint);
}

void DrawAsepriteEx(Aseprite aseprite, int frame, Vector2 position, float rotation, float scale, Color tint) {
    DrawAsepriteExFlipped(aseprite, frame, position, rotation, scale, false, false, tint);
}

void DrawAsepriteExFlipped(Aseprite aseprite, int frame, Vector2 position, float rotation, float scale, bool horizontalFlip, bool verticalFlip, Color tint) {
    ase_t* ase = aseprite.ase;
    if (ase == 0 || frame < 0 || frame >= ase->frame_count) {
        return;
    }

    Rectangle source = {(float)(frame * ase->w), 0,
        horizontalFlip ? (float)-ase->w : (float)ase->w,
        verticalFlip ? (float)-ase->h : (float)ase->h
    };
    Texture2D texture = GetAsepriteTexture(aseprite);
    Rectangle dest = {(float)position.x, (float)position.y, (float)ase->w * scale, (float)ase->h * scale};
    Vector2 origin = {0, 0};
    DrawTexturePro(texture, source, dest, origin, rotation, tint);           // Draw a part of a texture defined by a rectangle with 'pro' parameters
}

void DrawAsepritePro(Aseprite aseprite, int frame, Rectangle dest, Vector2 origin, float rotation, Color tint) {
    DrawAsepriteProFlipped(aseprite, frame, dest, origin, rotation, false, false, tint);
}

void DrawAsepriteProFlipped(Aseprite aseprite, int frame, Rectangle dest, Vector2 origin, float rotation, bool horizontalFlip, bool verticalFlip, Color tint) {
    ase_t* ase = aseprite.ase;
    if (ase == 0 || frame < 0 || frame >= ase->frame_count) {
        return;
    }

    Rectangle source = {
        (float)(frame * ase->w), 0,
        horizontalFlip ? (float)-ase->w : (float)ase->w,
        verticalFlip ? (float)-ase->h : (float)ase->h
    };
    Texture2D texture = GetAsepriteTexture(aseprite);
    DrawTexturePro(texture, source, dest, origin, rotation, tint);
}

/**
 * Display information about the loaded asprite.
 */
void TraceAseprite(Aseprite aseprite) {
    ase_t* ase = aseprite.ase;
    if (ase == 0) {
        TraceLog(LOG_INFO, "ASEPRITE: Empty Aseprite information");
        return;
    }

    TraceLog(LOG_INFO, "ASEPRITE: Aseprite information: (%ix%i - %i frames)", ase->w, ase->h, ase->frame_count);
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

    TraceLog(LOG_INFO, "    > Slices: %i", ase->slice_count);
    for (int i = 0; i < ase->slice_count; i++) {
        ase_slice_t* slice = ase->slices + i;
        TraceLog(LOG_INFO, "      - %s", slice->name);
    }
}

/**
 * Updates a tag to progress through its animation frame.
 *
 * @param tag The AsepriteTag passed in by reference (&tag).
 */
void UpdateAsepriteTag(AsepriteTag* tag) {
    if (tag == 0 || tag->tag == 0 || tag->aseprite.ase == 0) {
        TraceLog(LOG_WARNING, "ASEPRITE: Cannot update empty tag");
        return;
    }

    // Don't progress if the tag is paused.
    if (tag->paused) {
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
        case ASE_ANIMATION_DIRECTION_FORWARDS:
            if (tag->currentFrame > aseTag->to_frame) {
                if (tag->loop) {
                    tag->currentFrame = aseTag->from_frame;
                } else {
                    tag->currentFrame = aseTag->to_frame;
                    tag->paused = true;
                }
            }
        break;
        case ASE_ANIMATION_DIRECTION_BACKWORDS:
            if (tag->currentFrame < aseTag->from_frame) {
                if (tag->loop) {
                    tag->currentFrame = aseTag->to_frame;
                } else {
                    tag->currentFrame = aseTag->from_frame;
                    tag->paused = true;
                }
            }
        break;
        case ASE_ANIMATION_DIRECTION_PINGPONG:
            if (tag->direction > 0) {
                if (tag->currentFrame > aseTag->to_frame) {
                    tag->direction = -1;
                    if (tag->loop) {
                        tag->currentFrame = aseTag->to_frame - 1;
                    } else {
                        tag->currentFrame = aseTag->to_frame;
                        tag->paused = true;
                    }
                }
            } else {
                if (tag->currentFrame < aseTag->from_frame) {
                    tag->direction = 1;
                    if (tag->loop) {
                        tag->currentFrame = aseTag->from_frame + 1;
                    } else {
                        tag->currentFrame = aseTag->from_frame;
                        tag->paused = true;
                    }
                }
            }
        break;
    }

    // Reset the timer.
    // TODO(RobLoach): Add the original tag->timer to make up the different in frame time?
    tag->timer = (float)(ase->frames[tag->currentFrame].duration_milliseconds) / 1000.0f /* + tag->timer; */;
}

/**
 * Set which frame the Aseprite tag is on.
 *
 * @param tag The Aseprite tag to modify.
 * @param frameNumber Which frame to set the active tag to. If negative, will start from the end.
 */
void SetAsepriteTagFrame(AsepriteTag* tag, int frameNumber) {
    // TODO: Need to attribute frame number for ASE_ANIMATION_DIRECTION_BACKWORDS?
    if (frameNumber >= 0) {
        tag->currentFrame = tag->tag->from_frame + frameNumber;
    }
    else {
        tag->currentFrame = tag->tag->to_frame + frameNumber;
    }

    // Bounds
    if (tag->currentFrame < tag->tag->from_frame) {
        tag->currentFrame = tag->tag->from_frame;
    }
    else if (tag->currentFrame > tag->tag->to_frame) {
        tag->currentFrame = tag->tag->to_frame;
    }
}

int GetAsepriteTagFrame(AsepriteTag tag) {
    // TODO: Need to attribute frame number for ASE_ANIMATION_DIRECTION_BACKWORDS?
    return tag.currentFrame - tag.tag->from_frame;
}

void DrawAsepriteTag(AsepriteTag tag, int posX, int posY, Color tint) {
    DrawAseprite(tag.aseprite, tag.currentFrame, posX, posY, tint);
}

void DrawAsepriteTagFlipped(AsepriteTag tag, int posX, int posY, bool horizontalFlip, bool verticalFlip, Color tint) {
    DrawAsepriteFlipped(tag.aseprite, tag.currentFrame, posX, posY, horizontalFlip, verticalFlip, tint);
}

void DrawAsepriteTagV(AsepriteTag tag, Vector2 position, Color tint) {
    DrawAsepriteV(tag.aseprite, tag.currentFrame, position, tint);
}

void DrawAsepriteTagVFlipped(AsepriteTag tag, Vector2 position, bool horizontalFlip, bool verticalFlip, Color tint) {
    DrawAsepriteVFlipped(tag.aseprite, tag.currentFrame, position, horizontalFlip, verticalFlip, tint);
}

void DrawAsepriteTagEx(AsepriteTag tag, Vector2 position, float rotation, float scale, Color tint) {
    DrawAsepriteEx(tag.aseprite, tag.currentFrame, position, rotation, scale, tint);
}

void DrawAsepriteTagExFlipped(AsepriteTag tag, Vector2 position, float rotation, float scale, bool horizontalFlip, bool verticalFlip, Color tint) {
    DrawAsepriteExFlipped(tag.aseprite, tag.currentFrame, position, rotation, scale, horizontalFlip, verticalFlip, tint);
}

void DrawAsepriteTagPro(AsepriteTag tag, Rectangle dest, Vector2 origin, float rotation, Color tint) {
    DrawAsepritePro(tag.aseprite, tag.currentFrame, dest, origin, rotation, tint);
}

void DrawAsepriteTagProFlipped(AsepriteTag tag, Rectangle dest, Vector2 origin, float rotation, bool horizontalFlip, bool verticalFlip, Color tint) {
    DrawAsepriteProFlipped(tag.aseprite, tag.currentFrame, dest, origin, rotation, horizontalFlip, verticalFlip, tint);
}

/**
 * Generate an aseprite tag with sane defaults.
 *
 * @return An AsepriteTag with sane defaults.
 */
AsepriteTag GenAsepriteTagDefault() {
    struct AsepriteTag tag;
    tag.aseprite.ase = 0;
    tag.currentFrame = 0;
    tag.tag = 0;
    tag.timer = 0;
    tag.direction = 0;
    tag.speed = 1.0f;
    tag.color = BLACK;
    tag.loop = true;
    tag.paused = false;
    tag.name = 0;
    return tag;
}

/**
 * Load an Aseprite tag from the given index.
 *
 * @param aseprite The loaded Aseprite object from which to load the tag.
 * @param index The tag index within the Aseprite object.
 *
 * @return The Aseprite tag information, or an empty tag on failure.
 *
 * @see LoadAsepriteTag()
 * @see IsAsepriteTagValid()
 */
AsepriteTag LoadAsepriteTagFromIndex(Aseprite aseprite, int index) {
    AsepriteTag tag = GenAsepriteTagDefault();

    // Ensure the Aseprite exists.
    ase_t* ase = aseprite.ase;
    if (ase == 0) {
        TraceLog(LOG_ERROR, "ASEPRITE: Asprite not loaded when attempting to load tag #%i", index);
        return tag;
    }

    // Ensure the tag exists
    if (index < 0 || index >= ase->tag_count) {
        TraceLog(LOG_ERROR, "ASEPRITE: Tag index %i out of range for %i tags", index, ase->tag_count);
        return tag;
    }

    // Base tag information
    tag.aseprite.ase = aseprite.ase;
    tag.tag = &ase->tags[index];

    // Set up the frame range
    tag.direction = 1;
    tag.currentFrame = tag.tag->from_frame;
    if (tag.tag->loop_animation_direction == ASE_ANIMATION_DIRECTION_BACKWORDS) {
        tag.currentFrame = tag.tag->to_frame;
        tag.direction = -1;
    }

    // Pause the animation if it's a one-frame tag
    if (tag.tag->from_frame == tag.tag->to_frame) {
        tag.paused = true;
    }

    // Timer in seconds
    tag.timer = (float)(ase->frames[tag.currentFrame].duration_milliseconds) / 1000.0f;

    // Color
    tag.color.r = (unsigned char)tag.tag->r;
    tag.color.g = (unsigned char)tag.tag->g;
    tag.color.b = (unsigned char)tag.tag->b;

    // Name
    tag.name = (char*)tag.tag->name;

    // Display a trace log about the aseprite tag
    TraceLog(LOG_TRACE, "ASEPRITE: [ID %i] Asprite tag loaded successfully (%s)", index, tag.name);

    return tag;
}

/**
 * Load an Aseprite tag from the given name.
 *
 * @param aseprite The Aseprite object to load the tag from.
 * @param name The name of the tag to be loaded.
 *
 * @return The loaded Aseprite tag, or an empty tag on failure.
 *
 * @see IsAsepriteTagValid()
 * @see UpdateAsepriteTag()
 */
AsepriteTag LoadAsepriteTag(Aseprite aseprite, const char* name) {
    AsepriteTag tag = GenAsepriteTagDefault();
    ase_t* ase = aseprite.ase;
    if (ase == 0) {
        TraceLog(LOG_ERROR, "ASEPRITE: Cannot load tag \"%s\" from an Aseprite that's not loaded", name);
        return tag;
    }

    // Loop through all tags to find the correct name.
    for (int i = 0; i < ase->tag_count; i++) {
        if (TextIsEqual(name, ase->tags[i].name)) {
            return LoadAsepriteTagFromIndex(aseprite, i);
        }
    }

    // Display a warning about the missing aseprite
    TraceLog(LOG_WARNING, "ASEPRITE: Could not find tag \"%s\"", name);

    return tag;
}

/**
 * Determine whether or not the Aseprite tag was loaded successfully.
 *
 * @param tag The tag of which to check if it was loaded.
 *
 * @return True if the tag was loaded, false otherwise.
 */
bool IsAsepriteTagValid(AsepriteTag tag) {
    return tag.tag != 0;
}

/**
 * Load a slice from an Aseprite based on its name.
 *
 * @param name The name of the slice to find.
 *
 * @return The loaded slice, or an empty one if not found.
 */
AsepriteSlice LoadAsepriteSlice(Aseprite aseprite, const char* name) {
    if (aseprite.ase == NULL) {
        TraceLog(LOG_WARNING, "ASEPRITE: Cannot load slice on empty aseprite");
        return GenAsepriteSliceDefault();
    }
    for (int i = 0; i < aseprite.ase->slice_count; i++) {
        ase_slice_t* slice = &aseprite.ase->slices[i];
        if (TextIsEqual(name, slice->name)) {
            return LoadAsperiteSliceFromIndex(aseprite, i);
        }
    }

    return GenAsepriteSliceDefault();
}

/**
 * Load a slice from an Aseprite based on its index.
 *
 * @param index The index of the slice to load.
 *
 * @return The loaded slice, or an empty one if not found.
 */
AsepriteSlice LoadAsperiteSliceFromIndex(Aseprite aseprite, int index) {
    if (aseprite.ase == NULL) {
        TraceLog(LOG_WARNING, "ASEPRITE: Cannot load slice index from empty aseprite");
        return GenAsepriteSliceDefault();
    }
    if (index < aseprite.ase->slice_count) {
        AsepriteSlice output;
        ase_slice_t* slice = &aseprite.ase->slices[index];
        output.bounds.x = (float)slice->origin_x;
        output.bounds.y = (float)slice->origin_y;
        output.bounds.width = (float)slice->w;
        output.bounds.height = (float)slice->h;
        output.name = (char*)slice->name;
        return output;
    }

    return GenAsepriteSliceDefault();
}

/**
 * Generate empty Aseprite slice data.
 */
AsepriteSlice GenAsepriteSliceDefault() {
    AsepriteSlice slice;
    slice.name = "";
    slice.bounds = (Rectangle){0, 0, 0, 0};
    return slice;
}

/**
 * Get the amount of slices that are defined in the Aseprite.
 *
 * @return The amount of slices.
 */
int GetAsepriteSliceCount(Aseprite aseprite) {
    return aseprite.ase->slice_count;
}

/**
 * Return whether or not the given slice was found.
 */
bool IsAsepriteSliceValid(AsepriteSlice slice) {
    return TextLength(slice.name) != 0;
}

#ifdef __cplusplus
}
#endif

#endif  // RAYLIB_ASEPRITE_IMPLEMENTATION_ONCE
#endif  // RAYLIB_ASEPRITE_IMPLEMENTATION
