#ifndef COLLAGE_PRESENT_H
#define COLLAGE_PRESENT_H

// present/present.h — Presenter into the window's single seam canvas Swapchain.

#include "graphvex.h"

;;CLASSNAME("Presenter")

typedef struct Presenter {
    Swapchain swapchain;
} Presenter;

_Static_assert(sizeof(Presenter) == 32, "Presenter obeys 32-byte floor");

#endif
