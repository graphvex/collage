#ifndef COLLAGE_GROUP_H
#define COLLAGE_GROUP_H

// group/group.h — isolated composition Group at integer world origin.

#include "rect/rect.h"

;;CLASSNAME("Group")

typedef struct Group {
    RectI worldAllocation;
    f32 opacity;
    u32 _pad[7];
} Group;

_Static_assert(sizeof(Group) == 64, "Group obeys 32-byte multiple (64B)");

#endif
