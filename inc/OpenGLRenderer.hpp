#pragma once

#include <memory>
#include <vector>

#include "Cameras/Camera.hpp"
#include "Lights/Light.hpp"
#include "Mesh.hpp"
#include "Primitives/Object.hpp"
#include "Primitives/Primitives.hpp"
#include "Scene.hpp"
#include "Window.hpp"

namespace TotoGL {

class OpenGLRenderer {
public:
    OpenGLRenderer(
        const std::shared_ptr<Window> &window =
            Window::create(800, 600, "Default Window"));
    ~OpenGLRenderer();
    static std::shared_ptr<OpenGLRenderer> create(
        const std::shared_ptr<Window> &window =
            Window::create(800, 600, "Default Window")) {
        return std::make_shared<OpenGLRenderer>(window);
    }

    void render(
        const std::shared_ptr<Scene> &, const std::shared_ptr<Camera> &,
        const bool &affect_window = true) const;

    const std::shared_ptr<Window> &window() const { return _window; }

private:
    std::shared_ptr<Window> _window;

    void render_impl(
        const std::shared_ptr<Mesh> &, const std::shared_ptr<Camera> &,
        const std::vector<std::shared_ptr<Light>> &) const;

    std::vector<std::shared_ptr<Object>>
    getObjectsBuffer(const std::shared_ptr<Scene> &scene) const;
    void fillObjectsBuffer(
        const std::shared_ptr<Object> &, std::vector<std::shared_ptr<Object>> &,
        const Matrix4 & = Matrix4{ 1 }) const;

    void init();
};

} // namespace TotoGL
