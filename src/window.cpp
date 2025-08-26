#include <stdexcept>
#include <GLFW/glfw3.h>

#include <window.hpp>

void InitGLFW() {
    if(!glfwInit())
        throw std::runtime_error("Failed to initialize GLFW");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    glfwWindowHint(GLFW_STENCIL_BITS, 0);
    glfwWindowHint(GLFW_DEPTH_BITS, 0);
}

void TerminateGLFW() {
    glfwTerminate();
}

Window::Window(int width, int height, const char* title)
: width(width), height(height) {
    if(!(window = glfwCreateWindow(width, height, title, NULL, NULL)))
    {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glfwSetWindowUserPointer(window, this);
}

void Window::Terminate() {
    glfwDestroyWindow(window);
}

void Window::DefaultResizeCB(GLFWwindow* window, int width, int height) {
    Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));

    win->width = width;
    win->height = height;
}
