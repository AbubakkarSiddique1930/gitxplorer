#include <GLFW/glfw3.h>
#include <ios>
#include <iostream>
#include <stdexcept>
#include <spdlog/spdlog.h>

#include <window.hpp>

int main(int argc, char const *argv[]) {
    std::ios_base::sync_with_stdio(false);
    spdlog::info("Hello World");

    Window mainWindow;

    try {
        InitGLFW();
        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
        mainWindow = Window(800, 600, "gitxplorer");
    } catch(const std::runtime_error& err) {
        spdlog::error(err.what());
        return -1;
    }

    while(mainWindow.ShouldNotClose()) {
        glfwPollEvents();
        if(glfwGetKey(mainWindow, GLFW_KEY_ESCAPE))
            break;
    }

    mainWindow.Terminate();
    TerminateGLFW();

    return 0;
}