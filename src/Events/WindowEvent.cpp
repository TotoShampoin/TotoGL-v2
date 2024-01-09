#include "Events/WindowEvent.hpp"
#include "Events/Event.hpp"
#include "Primitives/Primitives.hpp"
#include "Window.hpp"
#include <GLFW/glfw3.h>
#include <cmath>

namespace TotoGL {

void Window::_setupEvents() {
    _event_manager.touch<WindowCloseEvent>(EventName::WINDOW_CLOSE);
    _event_manager.touch<WindowMinimizeEvent>(EventName::WINDOW_MINIMIZE);
    _event_manager.touch<WindowMaximizeEvent>(EventName::WINDOW_MAXIMIZE);
    _event_manager.touch<WindowResizeEvent>(EventName::WINDOW_RESIZE);
    _event_manager.touch<MouseButtonEvent>(EventName::MOUSE_UP);
    _event_manager.touch<MouseButtonEvent>(EventName::MOUSE_DOWN);
    _event_manager.touch<MouseMoveEvent>(EventName::MOUSE_MOVE);
    _event_manager.touch<MouseScrollEvent>(EventName::MOUSE_SCROLL);
    _event_manager.touch<KeyboardEvent>(EventName::KEY_UP);
    _event_manager.touch<KeyboardEvent>(EventName::KEY_DOWN);

    glfwSetWindowUserPointer(_glfw_window.get(), this);
    glfwSetWindowCloseCallback(_glfw_window.get(), [](GLFWwindow *glwin) {
        auto &window = *static_cast<Window *>(glfwGetWindowUserPointer(glwin));
        window._event_manager.emit(
            EventName::WINDOW_CLOSE, WindowCloseEvent(EventName::WINDOW_CLOSE));
    });
    glfwSetWindowIconifyCallback(
        _glfw_window.get(), [](GLFWwindow *glwin, int minimized) {
            auto &window =
                *static_cast<Window *>(glfwGetWindowUserPointer(glwin));
            window._event_manager.emit(
                EventName::WINDOW_MINIMIZE,
                WindowMinimizeEvent(EventName::WINDOW_MINIMIZE, minimized));
        });
    glfwSetWindowMaximizeCallback(
        _glfw_window.get(), [](GLFWwindow *glwin, int maximized) {
            auto &window =
                *static_cast<Window *>(glfwGetWindowUserPointer(glwin));
            window._event_manager.emit(
                EventName::WINDOW_MAXIMIZE,
                WindowMaximizeEvent(EventName::WINDOW_MAXIMIZE, maximized));
        });
    glfwSetWindowSizeCallback(
        _glfw_window.get(), [](GLFWwindow *glwin, int width, int height) {
            auto &window =
                *static_cast<Window *>(glfwGetWindowUserPointer(glwin));
            window._width = width;
            window._height = height;
            window._event_manager.emit(
                EventName::WINDOW_RESIZE,
                WindowResizeEvent(
                    EventName::WINDOW_RESIZE, Vector2(width, height)));
        });
    glfwSetMouseButtonCallback(
        _glfw_window.get(),
        [](GLFWwindow *glwin, int button, int action, int mods) {
            auto &window =
                *static_cast<Window *>(glfwGetWindowUserPointer(glwin));
            EventName name = (action == GLFW_PRESS) ? EventName::MOUSE_DOWN
                                                    : EventName::MOUSE_UP;
            window._event_manager.emit(
                name, MouseButtonEvent(name, button, action, mods));
        });
    glfwSetCursorPosCallback(
        _glfw_window.get(), [](GLFWwindow *glwin, double x, double y) {
            auto &window =
                *static_cast<Window *>(glfwGetWindowUserPointer(glwin));
            auto last_pos = window._mouse_position;
            auto pos = Vector2(x, y);
            window._event_manager.emit(
                EventName::MOUSE_MOVE,
                MouseMoveEvent(
                    EventName::MOUSE_MOVE, pos,
                    std::isnan(last_pos.x) ? Vector2(0) : (pos - last_pos)));
        });
    glfwSetScrollCallback(
        _glfw_window.get(), [](GLFWwindow *glwin, double x, double y) {
            auto &window =
                *static_cast<Window *>(glfwGetWindowUserPointer(glwin));
            window._event_manager.emit(
                EventName::MOUSE_SCROLL,
                MouseScrollEvent(EventName::MOUSE_SCROLL, Vector2(x, y)));
        });
    glfwSetKeyCallback(
        _glfw_window.get(),
        [](GLFWwindow *glwin, int key, int scancode, int action, int mods) {
            auto &window =
                *static_cast<Window *>(glfwGetWindowUserPointer(glwin));
            EventName name = (action == GLFW_PRESS) ? EventName::KEY_DOWN
                                                    : EventName::KEY_UP;
            window._event_manager.emit(
                name, KeyboardEvent(name, key, scancode, action, mods));
        });
}

} // namespace TotoGL
