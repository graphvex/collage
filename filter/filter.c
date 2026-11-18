// filter/filter.c — FilterToken helpers and FilterStack accumulation.

#include "vex.h"
#include "filter/filter.h"

;;OVERVIEW
;;DEFINITION

FilterToken FilterToken_blurBox(u32 radiusPixels) {
    return FilterToken_encode(FILTER_BLUR_BOX_ID, (u64) radiusPixels);
}

FilterToken FilterToken_gain(f32 factor) {
    u32 bits = 0u;
    memcpy(&bits, &factor, sizeof bits);
    return FilterToken_encode(FILTER_GAIN_ID, (u64) bits);
}

;;GETTER
static u32 FilterStack_count(const FilterStack *self) {
    return self ? (*self).count : 0u;
}
;;SETTER
static fn FilterStack_setCount(FilterStack *self, u32 count) {
    if (self) (*self).count = count;
}
;;GETTER
static FilterToken FilterStack_ops(const FilterStack *self, u32 idx) {
    return (self && idx < (*self).count) ? (*self).ops[idx] : 0u;
}
;;SETTER
static fn FilterStack_setOps(FilterStack *self, u32 idx, FilterToken token) {
    if (self && idx < FILTER_STACK_MAX_OPS) (*self).ops[idx] = token;
}

bool FilterStack_push(FilterStack *self, FilterToken token) {
    if (!self) return false;
    u32 count = FilterStack_count(self);
    if (count >= FILTER_STACK_MAX_OPS) {
        THROW("FilterStack: exceeded FILTER_STACK_MAX_OPS (%u)", FILTER_STACK_MAX_OPS);
        return false;
    }
    FilterStack_setOps(self, count, token);
    FilterStack_setCount(self, count + 1u);
    return true;
}

i32 FilterStack_totalBlurRadius(const FilterStack *self) {
    if (!self) return 0;
    i32 total = 0;
    u32 count = FilterStack_count(self);
    for (u32 i = 0u; i < count; i++) {
        FilterToken tok = FilterStack_ops(self, i);
        if (FilterToken_id(tok) == FILTER_BLUR_BOX_ID) {
            total += (i32) (FilterToken_payload(tok) & 0xFFFFu);
        }
    }
    return total;
}
