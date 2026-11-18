#ifndef COLLAGE_H
#define COLLAGE_H

// collage.h — the one include door of the collage rect-first forward compositor.
//
// Checked out at `graphvex/compositor/`; public class prefix stays `Compositor*`.
// Tier: core. Owns rect-first forward composition, graphics language vocabulary,
// paint/shape coverage, SDF text, elements, sources (including SceneSource),
// isolated groups, ordered filter stacks, damage, independent scheduling, and
// presentation. Never includes meld, darling, hotcwap or driver headers.

#include "vex.h"
#include "graphvex.h"

// One Type Registry Law: collage owns 0x0140 - 0x017F.
#define ID_COLLAGE_RECT               0x0140u
#define ID_COLLAGE_PROPERTY           0x0141u
#define ID_COLLAGE_GRAPHICS_COMPONENT 0x0142u
#define ID_COLLAGE_ELEMENT_NODE       0x0143u
#define ID_COLLAGE_BRUSH              0x0144u
#define ID_COLLAGE_STROKE             0x0145u
#define ID_COLLAGE_VECTOR_BRUSH       0x0146u
#define ID_COLLAGE_RASTER_BRUSH       0x0147u
#define ID_COLLAGE_SHAPE              0x0148u
#define ID_COLLAGE_FONT               0x0149u
#define ID_COLLAGE_SOURCE             0x014Au
#define ID_COLLAGE_SCENE_SOURCE       0x014Bu
#define ID_COLLAGE_GROUP              0x014Cu
#define ID_COLLAGE_FILTER_STACK       0x014Du
#define ID_COLLAGE_FILTER_POOL        0x014Eu
#define ID_COLLAGE_COMPOSITOR         0x014Fu
#define ID_COLLAGE_COMPOSITOR_IMAGE   0x0150u
#define ID_COLLAGE_DAMAGE_REGION      0x0151u
#define ID_COLLAGE_SCHEDULER          0x0152u
#define ID_COLLAGE_PRESENTER          0x0153u

#include "rect/rect.h"
#include "lang/lang.h"
#include "paint/paint.h"
#include "text/text.h"
#include "element/element.h"
#include "source/source.h"
#include "group/group.h"
#include "filter/filter.h"
#include "compose/compose.h"
#include "damage/damage.h"
#include "schedule/schedule.h"
#include "present/present.h"

#endif
