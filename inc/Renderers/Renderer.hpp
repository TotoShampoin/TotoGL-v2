#pragma once

#include <memory>

#include "Window.hpp"

namespace TotoGL {

class Renderer {
public:
    Renderer() = delete;
    virtual ~Renderer() = default;

    virtual void render() const = 0;

    const std::shared_ptr<Window> &window() const { return _window; }

protected:
    Renderer(
        const std::shared_ptr<Window> &window =
            Window::create(800, 600, "Default Window"))
        : _window(window) {}

private:
    std::shared_ptr<Window> _window;
};

} // namespace TotoGL
