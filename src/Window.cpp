#include "Window.hpp"
#include <GLFW/glfw3.h>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>

namespace TotoGL {

static bool is_init = false;

GLFWwindow* initAndCreateWindow(int width, int height, const char * title, GLFWmonitor * monitor, GLFWwindow * share) {
    Window::init();
    return glfwCreateWindow(width, height, title, monitor, share);
}
void Window::init() {
    if(is_init) return;
    if(!glfwInit()) {
        std::ostringstream oss;
        const char* err;
        glfwGetError(&err);
        oss << "Couldn't initialize window engine (glfw): " << err;
        throw std::runtime_error(oss.str());
    }
    glfwSetErrorCallback([](int code, const char* error) {
        std::cerr << "Error(" << code << "): " << error << "\n";
    });
    is_init = true;
}
void Window::terminate() {
    glfwTerminate();
}

Window::Window(const int& width, const int& height, const std::string& title):
    _width(width),
    _height(height),
    _title(title),
    _glfw_window(initAndCreateWindow(_width, _height, _title.c_str(), NULL, NULL))
{
    if(_glfw_window.get() == NULL) {
        throw std::runtime_error("Couldn't create window");
    }
    glfwMakeContextCurrent(_glfw_window.get());
    _setupEvents();
}

void Window::pollEvents() {
    makeContextCurrent();
    glfwPollEvents();
}
void Window::swapBuffer() {
    glfwSwapBuffers(_glfw_window.get());
}
void Window::makeContextCurrent() {
    glfwMakeContextCurrent(_glfw_window.get());
}
void Window::size(const int& width, const int& height) {
    _width = width;
    _height = height;
    glfwSetWindowSize(_glfw_window.get(), _width, _height);
}
void Window::title(const std::string& new_title) {
    _title = new_title;
    glfwSetWindowTitle(_glfw_window.get(), _title.c_str());
}

}
