// element/element.c — ElementNode eventBound and absoluteBound resolution.

#include "vex.h"
#include "element/element.h"

;;OVERVIEW
;;DEFINITION

ElementNode ElementNode_1(Rect rect) {
    ElementNode node = { 0 };
    node.property.rect = rect;
    return node;
}

;;GETTER
Property ElementNode_property(const ElementNode *self) {
    return self ? (*self).property : (Property){ 0 };
}

Rect ElementNode_eventBound(const ElementNode *self, Rect parentWorld) {
    if (!self) return Rect_0();
    Rect r = ElementNode_property(self).rect;
    return Rect_4(parentWorld.x + r.x, parentWorld.y + r.y, r.width, r.height);
}

Rect ElementNode_absoluteBound(const ElementNode *self, Rect parentWorld) {
    if (!self) return Rect_0();
    Rect ev = ElementNode_eventBound(self, parentWorld);
    Property prop = ElementNode_property(self);
    f32 halo = prop.shadowRadius + prop.blurRadius;
    return Rect_expand(ev, halo);
}
