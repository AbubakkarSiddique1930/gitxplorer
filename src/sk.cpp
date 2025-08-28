#include <sk.hpp>

#include <GLFW/glfw3.h>
#include <include/gpu/ganesh/GrBackendSurface.h>
#include <include/gpu/ganesh/SkSurfaceGanesh.h>
#include <include/gpu/ganesh/gl/GrGLAssembleInterface.h>
#include <include/gpu/ganesh/gl/GrGLBackendSurface.h>
#include <include/gpu/ganesh/gl/GrGLDirectContext.h>
#include <include/gpu/ganesh/gl/GrGLInterface.h>
#include <include/core/SkColorSpace.h>

GrDirectContext* SK::context = nullptr;
SkSurface* SK::surface = nullptr;
SkCanvas* SK::canvas = nullptr;

static void* GetGLProc(void*, const char* p) {
    return (void*)glfwGetProcAddress(p);
}

void SK::Init(int w, int h) {
    auto interface = GrGLMakeNativeInterface();
    if(!interface)
        interface = GrGLMakeAssembledInterface(
            nullptr, (GrGLGetProc)* GetGLProc
        );

    context = GrDirectContexts::MakeGL(interface).release();

    GrGLFramebufferInfo fbInfo;
    fbInfo.fFBOID = 0;
    fbInfo.fFormat= GL_RGBA8;

    SkColorType colType = kRGBA_8888_SkColorType;
    GrBackendRenderTarget rndrTrgt = GrBackendRenderTargets::MakeGL(
        w, h, 
        0,
        0,
        fbInfo
    );

    surface = SkSurfaces::WrapBackendRenderTarget(
        context,
        rndrTrgt,
        kBottomLeft_GrSurfaceOrigin,
        colType,
        nullptr, nullptr
    ).release();
    if(!surface)
        throw std::runtime_error("Failed to create Skia surface");

    canvas = surface->getCanvas();
}

void SK::Terminate()
{
    delete surface;
    delete context;
}