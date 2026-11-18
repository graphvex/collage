#ifndef COLLAGE_ELEMENT_H
#define COLLAGE_ELEMENT_H

// element/element.h — Property, GraphicsComponent and ElementNode.
//
// Absolute Rendering & Event Bound Law: every element has two geometric bounds:
// eventBound (resolved layout/hit rectangle; filters never alter it) and
// absoluteBound (conservative world-space AABB enclosing own and descendant
// paint after shadow/blur/filter expansion).

#include "rect/rect.h"

;;CLASSNAME("Property")

typedef struct Property {
    Rect rect;
    CornerRadius radius;
    u32 backgroundRGBA;
    u32 borderRGBA;
    f32 borderWidth;
    f32 shadowRadius;
    f32 blurRadius;
    u32 _pad[3];
} Property;

_Static_assert(sizeof(Property) == 96, "Property obeys 32-byte multiple (96B)");

;;CLASSNAME("GraphicsComponent")

typedef struct GraphicsComponent {
    Property property;
} GraphicsComponent;

_Static_assert(sizeof(GraphicsComponent) == 96, "GraphicsComponent obeys 32-byte multiple (96B)");

;;CLASSNAME("ElementNode")

typedef struct ElementNode {
    Property property;
    bool clipsChildren;
    u8 _pad[31];
} ElementNode;

_Static_assert(sizeof(ElementNode) == 128, "ElementNode obeys 32-byte multiple (128B)");

ElementNode ElementNode_1(Rect rect);
Rect ElementNode_eventBound(const ElementNode *self, Rect parentWorld);
Rect ElementNode_absoluteBound(const ElementNode *self, Rect parentWorld);

#endif
