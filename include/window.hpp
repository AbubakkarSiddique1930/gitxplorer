#pragma once

#include <GLFW/glfw3.h>

void InitGLFW();
void TerminateGLFW();

class Window {
    public:
        Window() : window(nullptr), width(0), height(0) {}
        Window(int width, int height, const char* title);
        void Terminate();

        void SetVSync(bool b) {
            glfwSwapInterval(b);
        }

        inline bool ShouldClose() {
            return glfwWindowShouldClose(window);
        }

        inline bool ShouldNotClose() {
            return !glfwWindowShouldClose(window);
        }

        inline operator GLFWwindow*() const {
            return window;
        }

        inline int GetWidth() {
            return width;
        }
        inline int GetHeight() {
            return height;
        }

    private:
        void static DefaultResizeCB(GLFWwindow*, int width, int height);
        int width, height;
        GLFWwindow* window;
};
