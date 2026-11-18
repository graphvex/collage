#ifndef COLLAGE_COMPOSE_H
#define COLLAGE_COMPOSE_H

// compose/compose.h — CompositorImage and Compositor (public prefix Compositor*).
//
// Ordered Filter & Scatter Composition Law: linear-light premultiplied RGBA
// f32 accumulation; expanded filter allocations translate world origin and
// never stretch results back into event rectangles.

#include "rect/rect.h"
#include "filter/filter.h"

;;CLASSNAME("CompositorImage")

typedef struct CompositorImage {
    i32 originX;
    i32 originY;
    u32 width;
    u32 height;
    f32 *linearPremulRGBA;
    u64 _pad;
} CompositorImage;

_Static_assert(sizeof(CompositorImage) == 32, "CompositorImage obeys 32-byte floor");

;;CLASSNAME("Compositor")

typedef struct Compositor {
    u32 maxDrawRects;
    u32 currentDrawRects;
    PixelMapping pixelMapping;
    u64 _pad[3];
} Compositor;

_Static_assert(sizeof(Compositor) == 64, "Compositor obeys 32-byte multiple (64B)");

Compositor Compositor_0();
Compositor Compositor_1(f32 backingScaleFactor);
#define Compositor(...) CONSTRUCTOR_DISPATCH(Compositor, __VA_ARGS__)

// Computes expanded integer allocation support for a group after its FilterStack.
// Translates origin by -totalBlurRadius and expands width/height by 2*totalBlurRadius.
RectI Compositor_expandedSupport(RectI baseSupport, const FilterStack *stack);

#endif
