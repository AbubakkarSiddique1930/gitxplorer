#include <include/core/SkColor.h>
#include <include/core/SkFont.h>
#include <include/core/SkFontTypes.h>
#include <include/core/SkPaint.h>
#include <include/ports/SkFontMgr_fontconfig.h>
#include <GLFW/glfw3.h>
#include <ios>
#include <iostream>
#include <stdexcept>
#include <spdlog/spdlog.h>

#include <window.hpp>
#include <sk.hpp>
#include <font.hpp>

int main(int argc, char const *argv[]) {
    std::ios_base::sync_with_stdio(false);
    spdlog::info("Hello World");

    Window mainWindow;

    try {
        InitGLFW();
        mainWindow = Window(800, 600, "gitxplorer");
        SK::Init(800, 600);
    } catch(const std::runtime_error& err) {
        spdlog::error(err.what());
        return -1;
    }

    SkPaint bgPaint, fgPaint;
    bgPaint.setColor(SkColors::kCyan);
    fgPaint.setColor(SkColors::kBlack);

    SkFont fontMononoki = Font::LoadFontFromFile(
        "resources/fonts/mononoki/mononoki-Regular.ttf", 32
    );
    SkFont fontComfortaa = Font::LoadFontFromFile(
        "resources/fonts/Comfortaa/Comfortaa-Medium.ttf", 32
    );

    while(mainWindow.ShouldNotClose()) {
        glfwPollEvents();
        if(glfwGetKey(mainWindow, GLFW_KEY_ESCAPE))
            break;

        SK::canvas->drawPaint(bgPaint);
        SK::canvas->drawSimpleText(
            "Hello", 5, SkTextEncoding::kUTF8,
            50, 50, fontMononoki, fgPaint
        );
        SK::canvas->drawSimpleText(
            "World", 5, SkTextEncoding::kUTF8,
            50, 90, fontComfortaa, fgPaint
        );


        SK::context->flush();

        glfwSwapBuffers(mainWindow);
    }

    SK::Terminate();
    mainWindow.Terminate();
    TerminateGLFW();

    return 0;
}