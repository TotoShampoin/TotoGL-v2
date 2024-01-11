#pragma once

#include <GLFW/glfw3.h>
#include <functional>
#include <memory>

#include "Events/Event.hpp"
#include "Events/EventManager.hpp"
#include "Primitives/Primitives.hpp"
// #include "Renderer.hpp"

namespace TotoGL {

class Window {
private:
    struct GLFWwindowDeleter {
        void operator()(GLFWwindow *ptr) { glfwDestroyWindow(ptr); }
    };

public:
    Window(const int &width, const int &height, const std::string &title);
    ~Window() = default;
    static std::shared_ptr<Window>
    create(const int &width, const int &height, const std::string &title) {
        return std::make_shared<Window>(width, height, title);
    }

    static void init();
    static void terminate();

    void pollEvents();
    void swapBuffer();
    void makeContextCurrent();
    bool shouldClose();

    void callBeforeSwap(const std::function<void()>&);

    void size(const int &, const int &);
    void title(const std::string &);

    const std::string &title() const { return _title; }
    const std::tuple<const int &, const int &> size() const {
        return { _width, _height };
    }
    const std::unique_ptr<GLFWwindow, GLFWwindowDeleter> &glfwWindow() const {
        return _glfw_window;
    };

    template <
        typename SpecificEvent,
        typename =
            std::enable_if_t<std::is_base_of<Event, SpecificEvent>::value>>
    CallbackHandle
    on(const EventName &name,
       const std::function<void(const SpecificEvent *)> &callback) {
        return _event_manager.on<SpecificEvent>(name, callback);
    }
    CallbackHandle
    on(const EventName &name,
       const std::function<void(const Event *)> &callback) {
        return _event_manager.on(name, callback);
    }
    void off(const EventName &name, const CallbackHandle &handle) {
        return _event_manager.off(name, handle);
    }
    void off(const EventName &name) { return _event_manager.off(name); }

private:
    int _width, _height;
    std::string _title;
    EventManager<EventName, Event> _event_manager;

    Vector2 _mouse_position{ NAN };

    std::unique_ptr<GLFWwindow, GLFWwindowDeleter> _glfw_window;

    void _setupEvents();
};

} // namespace TotoGL
