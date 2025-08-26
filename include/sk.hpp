#pragma once

#include <include/core/SkCanvas.h>
#include <include/gpu/ganesh/GrDirectContext.h>

namespace SK {
    extern GrDirectContext* context;
    extern SkSurface* surface;
    extern SkCanvas* canvas;

    void Init(int width, int height);
    void Terminate();
}