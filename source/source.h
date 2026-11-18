#ifndef COLLAGE_SOURCE_H
#define COLLAGE_SOURCE_H

// source/source.h — rect sources (Solid, Image, Glyph, Vector, SceneSource).
//
// SceneSource consumes the newest completed scene Image (e.g. from meld) as an
// ordinary rect at the panel's eventBound without collage including meld.

#include "rect/rect.h"
#include "graphvex.h"

;;CLASSNAME("SourceKind")

typedef enum SourceKind {
    SOURCE_SOLID  = 0,
    SOURCE_IMAGE  = 1,
    SOURCE_GLYPH  = 2,
    SOURCE_VECTOR = 3,
    SOURCE_SCENE  = 4
} SourceKind;

;;CLASSNAME("SceneSource")

typedef struct SceneSource {
    const Image *sceneImage;
    u64 sceneVersion;
    Rect eventRect;
    u64 _pad[2];
} SceneSource;

_Static_assert(sizeof(SceneSource) == 64, "SceneSource obeys 32-byte multiple (64B)");

SceneSource SceneSource_3(const Image *sceneImage, u64 sceneVersion, Rect eventRect);

#endif
