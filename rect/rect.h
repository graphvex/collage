#ifndef COLLAGE_RECT_H
#define COLLAGE_RECT_H

// rect/rect.h — Rect, RectI, CornerRadius and PixelMapping (Rect-First Law).

#include "vex.h"

;;CLASSNAME("Rect")

typedef struct Rect {
    f32 x;
    f32 y;
    f32 width;
    f32 height;
    u32 _pad[4];
} Rect;

_Static_assert(sizeof(Rect) == 32, "Rect obeys 32-byte floor");

Rect Rect_0();
Rect Rect_4(f32 x, f32 y, f32 width, f32 height);
#define Rect(...) CONSTRUCTOR_DISPATCH(Rect, __VA_ARGS__)

bool Rect_contains(Rect self, f32 px, f32 py);
Rect Rect_union(Rect a, Rect b);
Rect Rect_intersect(Rect a, Rect b);
Rect Rect_expand(Rect self, f32 halo);

;;CLASSNAME("RectI")

typedef struct RectI {
    i32 x;
    i32 y;
    i32 width;
    i32 height;
    u32 _pad[4];
} RectI;

_Static_assert(sizeof(RectI) == 32, "RectI obeys 32-byte floor");

RectI RectI_0();
RectI RectI_4(i32 x, i32 y, i32 width, i32 height);
#define RectI(...) CONSTRUCTOR_DISPATCH(RectI, __VA_ARGS__)

RectI RectI_expand(RectI self, i32 radius);
RectI RectI_union(RectI a, RectI b);

;;CLASSNAME("CornerRadius")

typedef struct CornerRadius {
    f32 topLeft;
    f32 topRight;
    f32 bottomRight;
    f32 bottomLeft;
    u32 _pad[4];
} CornerRadius;

_Static_assert(sizeof(CornerRadius) == 32, "CornerRadius obeys 32-byte floor");

;;CLASSNAME("PixelMapping")

typedef struct PixelMapping {
    f32 backingScaleFactor;
    u32 _pad[7];
} PixelMapping;

_Static_assert(sizeof(PixelMapping) == 32, "PixelMapping obeys 32-byte floor");

PixelMapping PixelMapping_1(f32 backingScaleFactor);
RectI PixelMapping_toNativeRectI(const PixelMapping *self, Rect logicalRect);

#endif
