#ifndef COLLAGE_FILTER_H
#define COLLAGE_FILTER_H

// filter/filter.h — FilterToken (ID16 | payload48) and ordered FilterStack.
//
// Ordered Filter & Scatter Composition Law: filter tokens pack a 16-bit ID in
// bits 63..48 and a 48-bit payload in bits 47..0; stacks execute left-to-right.

#include "vex.h"

#define FILTER_STACK_MAX_OPS 8u

;;CLASSNAME("FilterId")

typedef enum FilterId {
    FILTER_IDENTITY_ID   = 0x0000u,
    FILTER_GAIN_ID       = 0x0001u,
    FILTER_BLUR_BOX_ID   = 0x0002u,
    FILTER_BRIGHTNESS_ID = 0x0003u,
    FILTER_CONTRAST_ID   = 0x0004u,
    FILTER_GRAYSCALE_ID  = 0x0005u,
    FILTER_INVERT_ID     = 0x0006u,
    FILTER_POOLED_ID     = 0x8000u
} FilterId;

;;CLASSNAME("FilterToken")

typedef u64 FilterToken;

static inline FilterToken FilterToken_encode(u16 id, u64 payload48) {
    return ((u64) id << 48) | (payload48 & 0x0000FFFFFFFFFFFFULL);
}

static inline u16 FilterToken_id(FilterToken token) {
    return (u16) (token >> 48);
}

static inline u64 FilterToken_payload(FilterToken token) {
    return token & 0x0000FFFFFFFFFFFFULL;
}

FilterToken FilterToken_blurBox(u32 radiusPixels);
FilterToken FilterToken_gain(f32 factor);

;;CLASSNAME("FilterStack")

typedef struct FilterStack {
    FilterToken ops[FILTER_STACK_MAX_OPS];
    u32 count;
    u32 _pad[7];
} FilterStack;

_Static_assert(sizeof(FilterStack) == 96, "FilterStack obeys 32-byte multiple (96B)");

bool FilterStack_push(FilterStack *self, FilterToken token);
i32  FilterStack_totalBlurRadius(const FilterStack *self);

#endif
