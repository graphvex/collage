// compose/compose.c — Compositor construction and expanded filter support.

#include "vex.h"
#include "compose/compose.h"

;;OVERVIEW
;;DEFINITION

Compositor Compositor_1(f32 backingScaleFactor) {
    Compositor comp = { 0 };
    comp.maxDrawRects = 4096u;
    comp.currentDrawRects = 0u;
    comp.pixelMapping = PixelMapping_1(backingScaleFactor);
    return comp;
}

Compositor Compositor_0() {
    return Compositor_1(2.0f);
}

RectI Compositor_expandedSupport(RectI baseSupport, const FilterStack *stack) {
    i32 radius = FilterStack_totalBlurRadius(stack);
    return RectI_expand(baseSupport, radius);
}
