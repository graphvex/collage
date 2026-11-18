#ifndef COLLAGE_PAINT_H
#define COLLAGE_PAINT_H

// paint/paint.h — Brush, Stroke, VectorBrush, RasterBrush and coverage Shape.
//
// Rect-First Law: shapes are evaluated as coverage inside a rect (analytic SDF
// or SDF atlas lookup), never tessellated into triangles.

#include "rect/rect.h"

;;CLASSNAME("Brush")

typedef struct Brush {
    u32 colorRGBA;
    f32 opacity;
    u32 _pad[6];
} Brush;

_Static_assert(sizeof(Brush) == 32, "Brush obeys 32-byte floor");

;;CLASSNAME("Stroke")

typedef struct Stroke {
    u32 colorRGBA;
    f32 width;
    u32 _pad[6];
} Stroke;

_Static_assert(sizeof(Stroke) == 32, "Stroke obeys 32-byte floor");

;;CLASSNAME("Shape")

typedef enum ShapeKind {
    SHAPE_RECT         = 0,
    SHAPE_ROUNDED_RECT = 1,
    SHAPE_CIRCLE       = 2,
    SHAPE_SDF_ATLAS    = 3
} ShapeKind;

typedef struct Shape {
    ShapeKind kind;
    u32 sdfAtlasSlot;
    Rect bounds;
    CornerRadius radius;
    u32 _pad[6];
} Shape;

_Static_assert(sizeof(Shape) == 96, "Shape obeys 32-byte multiple (96B)");

#endif
