// collage_core_test.c — tests for collage (graphvex/compositor):
// - Rect & native Retina PixelMapping (Seam Canvas Pixel Mapping Law)
// - ElementNode eventBound vs absoluteBound (Absolute Rendering & Event Bound Law)
// - FilterToken ID16|payload48 & expanded allocation origin translation
// - Independent Scene Cadence Law (CompositeScheduler + SceneSource)

#include "collage.h"

static i32 failures;

static fn check(i32 ok, const char *what) {
    if (ok) return;
    fprintf(stderr, "collage_core_test: FAIL %s\n", what);
    failures++;
}

i32 main() {
    // 1. Seam Canvas Pixel Mapping Law (2.0 Retina scale maps 1:1 native pixels)
    Compositor comp = Compositor(2.0f);
    Rect logical = Rect(10.0f, 20.0f, 100.0f, 50.0f);
    RectI native = PixelMapping_toNativeRectI(&comp.pixelMapping, logical);
    check(native.x == 20 && native.y == 40 && native.width == 200 && native.height == 100,
          "Retina 2.0 PixelMapping maps logical (10,20,100,50) to native (20,40,200,100)");

    // 2. Absolute Rendering & Event Bound Law
    Rect parentWorld = Rect(50.0f, 50.0f, 500.0f, 500.0f);
    ElementNode node = ElementNode_1(Rect(50.0f, 50.0f, 200.0f, 80.0f));
    node.property.shadowRadius = 12.0f;
    node.property.blurRadius = 8.0f;

    Rect ev = ElementNode_eventBound(&node, parentWorld);
    Rect ab = ElementNode_absoluteBound(&node, parentWorld);
    check(ev.x == 100.0f && ev.y == 100.0f && ev.width == 200.0f && ev.height == 80.0f,
          "eventBound is (100,100,200,80) and is unaltered by filters/shadows");
    check(ab.x == 80.0f && ab.y == 80.0f && ab.width == 240.0f && ab.height == 120.0f,
          "absoluteBound expands by shadow+blur (20px) on all sides to (80,80,240,120)");

    // 3. Ordered Filter & Scatter Composition Law: expanded allocation translates origin
    FilterStack stack = { 0 };
    FilterStack_push(&stack, FilterToken_blurBox(12u));
    FilterStack_push(&stack, FilterToken_blurBox(8u));
    RectI baseI = RectI(100, 100, 200, 80);
    RectI expI  = Compositor_expandedSupport(baseI, &stack);
    check(expI.x == 80 && expI.y == 80 && expI.width == 240 && expI.height == 120,
          "Chained box blurs (12+8=20) translate allocation origin to (80,80) and extent to 240x120");

    // 4. Independent Scene Cadence Law: widget and scene versions invalidate independently
    CompositeScheduler sched = CompositeScheduler_0();
    check(CompositeScheduler_needsComposite(&sched), "Initial widget tree needs composite");
    CompositeScheduler_markComposed(&sched);
    check(!CompositeScheduler_needsComposite(&sched), "Clean after markComposed");

    // Scene finishes a new frame version while widgets are idle
    Image sceneImg = Image_3(800u, 600u, PIXEL_FORMAT_RGBA16_FLOAT);
    SceneSource src = SceneSource_3(&sceneImg, 1u, ev);
    CompositeScheduler_observeSceneVersion(&sched, src.sceneVersion);
    check(CompositeScheduler_needsComposite(&sched), "Completed scene version invalidates composite independently");
    CompositeScheduler_markComposed(&sched);
    check(!CompositeScheduler_needsComposite(&sched), "Clean after composing new scene version");

    return failures ? 1 : 0;
}
