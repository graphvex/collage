// rect/rect.c — Rect, RectI and native pixel mapping.

#include "vex.h"
#include "rect/rect.h"

;;OVERVIEW
;;DEFINITION

Rect Rect_4(f32 x, f32 y, f32 width, f32 height) {
    if (width < 0.0f) width = 0.0f;
    if (height < 0.0f) height = 0.0f;
    return (Rect){ .x = x, .y = y, .width = width, .height = height, ._pad = { 0 } };
}

Rect Rect_0() {
    return Rect_4(0.0f, 0.0f, 0.0f, 0.0f);
}

bool Rect_contains(Rect self, f32 px, f32 py) {
    return px >= self.x && px < (self.x + self.width) &&
           py >= self.y && py < (self.y + self.height);
}

Rect Rect_union(Rect a, Rect b) {
    if (a.width <= 0.0f || a.height <= 0.0f) return b;
    if (b.width <= 0.0f || b.height <= 0.0f) return a;
    f32 x0 = (a.x < b.x) ? a.x : b.x;
    f32 y0 = (a.y < b.y) ? a.y : b.y;
    f32 ax1 = a.x + a.width,  bx1 = b.x + b.width;
    f32 ay1 = a.y + a.height, by1 = b.y + b.height;
    f32 x1 = (ax1 > bx1) ? ax1 : bx1;
    f32 y1 = (ay1 > by1) ? ay1 : by1;
    return Rect_4(x0, y0, x1 - x0, y1 - y0);
}

Rect Rect_intersect(Rect a, Rect b) {
    f32 x0 = (a.x > b.x) ? a.x : b.x;
    f32 y0 = (a.y > b.y) ? a.y : b.y;
    f32 ax1 = a.x + a.width,  bx1 = b.x + b.width;
    f32 ay1 = a.y + a.height, by1 = b.y + b.height;
    f32 x1 = (ax1 < bx1) ? ax1 : bx1;
    f32 y1 = (ay1 < by1) ? ay1 : by1;
    if (x1 <= x0 || y1 <= y0) return Rect_0();
    return Rect_4(x0, y0, x1 - x0, y1 - y0);
}

Rect Rect_expand(Rect self, f32 halo) {
    if (halo < 0.0f) halo = 0.0f;
    return Rect_4(self.x - halo, self.y - halo,
                  self.width + 2.0f * halo, self.height + 2.0f * halo);
}

RectI RectI_4(i32 x, i32 y, i32 width, i32 height) {
    if (width < 0) width = 0;
    if (height < 0) height = 0;
    return (RectI){ .x = x, .y = y, .width = width, .height = height, ._pad = { 0 } };
}

RectI RectI_0() {
    return RectI_4(0, 0, 0, 0);
}

RectI RectI_expand(RectI self, i32 radius) {
    if (radius < 0) radius = 0;
    return RectI_4(self.x - radius, self.y - radius,
                   self.width + 2 * radius, self.height + 2 * radius);
}

RectI RectI_union(RectI a, RectI b) {
    if (a.width <= 0 || a.height <= 0) return b;
    if (b.width <= 0 || b.height <= 0) return a;
    i32 x0 = (a.x < b.x) ? a.x : b.x;
    i32 y0 = (a.y < b.y) ? a.y : b.y;
    i32 ax1 = a.x + a.width,  bx1 = b.x + b.width;
    i32 ay1 = a.y + a.height, by1 = b.y + b.height;
    i32 x1 = (ax1 > bx1) ? ax1 : bx1;
    i32 y1 = (ay1 > by1) ? ay1 : by1;
    return RectI_4(x0, y0, x1 - x0, y1 - y0);
}

PixelMapping PixelMapping_1(f32 backingScaleFactor) {
    if (backingScaleFactor <= 0.0f) backingScaleFactor = 1.0f;
    return (PixelMapping){ .backingScaleFactor = backingScaleFactor, ._pad = { 0 } };
}

;;GETTER
f32 PixelMapping_backingScaleFactor(const PixelMapping *self) {
    return self ? (*self).backingScaleFactor : 1.0f;
}

RectI PixelMapping_toNativeRectI(const PixelMapping *self, Rect logicalRect) {
    f32 scale = PixelMapping_backingScaleFactor(self);
    i32 x0 = (i32) floorf(logicalRect.x * scale);
    i32 y0 = (i32) floorf(logicalRect.y * scale);
    i32 x1 = (i32) ceilf((logicalRect.x + logicalRect.width) * scale);
    i32 y1 = (i32) ceilf((logicalRect.y + logicalRect.height) * scale);
    return RectI_4(x0, y0, x1 - x0, y1 - y0);
}
