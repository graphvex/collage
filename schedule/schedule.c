// schedule/schedule.c — independent widget and scene invalidation tracking.

#include "vex.h"
#include "schedule/schedule.h"

;;OVERVIEW
;;DEFINITION

CompositeScheduler CompositeScheduler_0() {
    return (CompositeScheduler){
        .widgetVersion = 1u,
        .composedWidgetVersion = 0u,
        .sceneVersion = 0u,
        .composedSceneVersion = 0u
    };
}

;;GETTER
static u64 CompositeScheduler_widgetVersion(const CompositeScheduler *self) {
    return self ? (*self).widgetVersion : 0u;
}
;;SETTER
static fn CompositeScheduler_setWidgetVersion(CompositeScheduler *self, u64 v) {
    if (self) (*self).widgetVersion = v;
}
;;GETTER
static u64 CompositeScheduler_composedWidgetVersion(const CompositeScheduler *self) {
    return self ? (*self).composedWidgetVersion : 0u;
}
;;SETTER
static fn CompositeScheduler_setComposedWidgetVersion(CompositeScheduler *self, u64 v) {
    if (self) (*self).composedWidgetVersion = v;
}
;;GETTER
static u64 CompositeScheduler_sceneVersion(const CompositeScheduler *self) {
    return self ? (*self).sceneVersion : 0u;
}
;;SETTER
static fn CompositeScheduler_setSceneVersion(CompositeScheduler *self, u64 v) {
    if (self) (*self).sceneVersion = v;
}
;;GETTER
static u64 CompositeScheduler_composedSceneVersion(const CompositeScheduler *self) {
    return self ? (*self).composedSceneVersion : 0u;
}
;;SETTER
static fn CompositeScheduler_setComposedSceneVersion(CompositeScheduler *self, u64 v) {
    if (self) (*self).composedSceneVersion = v;
}

fn CompositeScheduler_markWidgetDirty(CompositeScheduler *self) {
    if (self) CompositeScheduler_setWidgetVersion(self, CompositeScheduler_widgetVersion(self) + 1u);
}

fn CompositeScheduler_observeSceneVersion(CompositeScheduler *self, u64 completedSceneVersion) {
    if (self && completedSceneVersion > CompositeScheduler_sceneVersion(self)) {
        CompositeScheduler_setSceneVersion(self, completedSceneVersion);
    }
}

bool CompositeScheduler_needsComposite(const CompositeScheduler *self) {
    if (!self) return false;
    return (CompositeScheduler_widgetVersion(self) != CompositeScheduler_composedWidgetVersion(self)) ||
           (CompositeScheduler_sceneVersion(self)  != CompositeScheduler_composedSceneVersion(self));
}

fn CompositeScheduler_markComposed(CompositeScheduler *self) {
    if (!self) return;
    CompositeScheduler_setComposedWidgetVersion(self, CompositeScheduler_widgetVersion(self));
    CompositeScheduler_setComposedSceneVersion(self, CompositeScheduler_sceneVersion(self));
}
