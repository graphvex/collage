#ifndef COLLAGE_TEXT_H
#define COLLAGE_TEXT_H

// text/text.h — bake-on-demand SDF Font and SdfAtlas.

#include "graphvex.h"

;;CLASSNAME("Font")

typedef struct Font {
    const char *family;
    u32 atlasBindlessSlot;
    f32 bakePixelHeight;
    u64 _pad[2];
} Font;

_Static_assert(sizeof(Font) == 32, "Font obeys 32-byte floor");

#endif
