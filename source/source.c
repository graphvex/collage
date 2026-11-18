// source/source.c — SceneSource construction and rect fit.

#include "vex.h"
#include "source/source.h"

;;OVERVIEW
;;DEFINITION

SceneSource SceneSource_3(const Image *sceneImage, u64 sceneVersion, Rect eventRect) {
    return (SceneSource){
        .sceneImage = sceneImage,
        .sceneVersion = sceneVersion,
        .eventRect = eventRect,
        ._pad = { 0u, 0u }
    };
}
