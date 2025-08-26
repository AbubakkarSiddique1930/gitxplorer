#include <GLFW/glfw3.h>
#include <include/core/SkColor.h>
#include <include/core/SkPaint.h>
#include <ios>
#include <iostream>
#include <stdexcept>
#include <spdlog/spdlog.h>

#include <window.hpp>
#include <sk.hpp>

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

    SkPaint bgPaint;
    bgPaint.setColor(SkColors::kCyan);

    while(mainWindow.ShouldNotClose()) {
        glfwPollEvents();
        if(glfwGetKey(mainWindow, GLFW_KEY_ESCAPE))
            break;

        SK::canvas->drawPaint(bgPaint);

        SK::context->flush();

        glfwSwapBuffers(mainWindow);
    }

    SK::Terminate();
    mainWindow.Terminate();
    TerminateGLFW();

    return 0;
}