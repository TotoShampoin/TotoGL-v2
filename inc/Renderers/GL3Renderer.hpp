#pragma once

#include "Cameras/Camera.hpp"
#include "Lights/Light.hpp"
#include "Mesh.hpp"
#include "Renderer.hpp"
#include "Scene.hpp"
#include <memory>
#include <vector>

namespace TotoGL {

class GL3Renderer : public Renderer {
public:
    GL3Renderer(
        const std::shared_ptr<Window> &window =
            Window::create(800, 600, "Default Window"));
    ~GL3Renderer() override;
    static std::shared_ptr<GL3Renderer> create(
        const std::shared_ptr<Window> &window =
            Window::create(800, 600, "Default Window")) {
        return std::make_shared<GL3Renderer>(window);
    }

    // Will do nothing, use render(scene, camera)
    void render() const override {}

    void render(
        const std::shared_ptr<Scene> &, const std::shared_ptr<Camera> &) const;

private:
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
using GL3RendererPtr = std::shared_ptr<GL3Renderer>;

} // namespace TotoGL
