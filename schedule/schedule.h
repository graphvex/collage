#ifndef COLLAGE_SCHEDULE_H
#define COLLAGE_SCHEDULE_H

// schedule/schedule.h — CompositeScheduler (Independent Scene Cadence Law).
//
// Widget changes and completed scene versions invalidate composition
// independently; scene work never monopolizes widget scheduling.

#include "vex.h"

;;CLASSNAME("CompositeScheduler")

typedef struct CompositeScheduler {
    u64 widgetVersion;
    u64 composedWidgetVersion;
    u64 sceneVersion;
    u64 composedSceneVersion;
} CompositeScheduler;

_Static_assert(sizeof(CompositeScheduler) == 32, "CompositeScheduler obeys 32-byte floor");

CompositeScheduler CompositeScheduler_0();
fn   CompositeScheduler_markWidgetDirty(CompositeScheduler *self);
fn   CompositeScheduler_observeSceneVersion(CompositeScheduler *self, u64 completedSceneVersion);
bool CompositeScheduler_needsComposite(const CompositeScheduler *self);
fn   CompositeScheduler_markComposed(CompositeScheduler *self);

#endif
