#ifndef COLLAGE_DAMAGE_H
#define COLLAGE_DAMAGE_H

// damage/damage.h — DamageRegion (union of old and new absolute bounds).

#include "rect/rect.h"

;;CLASSNAME("DamageRegion")

typedef struct DamageRegion {
    RectI bounds;
    bool dirty;
    u8 _pad[31];
} DamageRegion;

_Static_assert(sizeof(DamageRegion) == 64, "DamageRegion obeys 32-byte multiple (64B)");

#endif
