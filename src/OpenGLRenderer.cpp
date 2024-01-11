#include <GL/glew.h>

#include <GL/gl.h>

#include "Lights/Light.hpp"
#include "Materials/Material.hpp"
#include "Materials/MultiMaterial.hpp"
#include "Primitives/Object.hpp"
#include "Primitives/Primitives.hpp"
#include "OpenGLRenderer.hpp"

#include <cstddef>
#include <memory>
#include <optional>
#include <sstream>

namespace TotoGL {

static bool is_glew_init = false;
void OpenGLRenderer::init() {
    if (is_glew_init)
        return;
    auto init = glewInit();
    if (init) {
        std::ostringstream oss;
        oss << "Couldn't initialize opengl renderer: " << glewGetErrorString(init);
        throw std::runtime_error(oss.str());
    }
}

OpenGLRenderer::OpenGLRenderer(const std::shared_ptr<Window> &window) : _window(window) {
    window->makeContextCurrent();
    init();
}

OpenGLRenderer::~OpenGLRenderer() {}

void OpenGLRenderer::render(
    const std::shared_ptr<Scene> &scene, const std::shared_ptr<Camera> &camera,
    const bool &affect_window) const {
    if (affect_window)
        _window->makeContextCurrent();
    const auto &[width, height] = _window->size();
    glViewport(0, 0, width, height);
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    auto objects_buffer = getObjectsBuffer(scene);
    auto meshes = Object::filter<Mesh>(objects_buffer);
    auto lights = Object::filter<Light>(objects_buffer);
    for (const auto &mesh : meshes) {
        render_impl(mesh, camera, lights);
    }
    if (affect_window)
        _window->swapBuffer();
}

void OpenGLRenderer::render_impl(
    const std::shared_ptr<Mesh> &mesh, const std::shared_ptr<Camera> &camera,
    const std::vector<std::shared_ptr<Light>> &lights) const {
    auto geometry = mesh->geometry();
    auto material = mesh->material();

    auto draw_mesh = [&](const std::shared_ptr<Material> &material,
                         const std::optional<size_t> &idx = std::nullopt) {
        material->applyModel(mesh->matrixWorld());
        material->applyCamera(camera);
        material->applyLights(lights);
        material->activate();
        geometry->draw(idx);
        material->deactivate();
    };

    if (auto multi_material =
            std::dynamic_pointer_cast<MultiMaterial>(material)) {
        auto materials = multi_material->materials();
        auto count = materials.size();
        for (const auto &material_idx : geometry->_sorted_materials) {
            auto &material = materials[material_idx < count ? material_idx : 0];
            draw_mesh(material, material_idx);
        }
    } else {
        draw_mesh(material);
    }
}

std::vector<std::shared_ptr<Object>>
OpenGLRenderer::getObjectsBuffer(const std::shared_ptr<Scene> &scene) const {
    std::vector<std::shared_ptr<Object>> objects_buffer;
    fillObjectsBuffer(scene, objects_buffer);
    return objects_buffer;
}

void OpenGLRenderer::fillObjectsBuffer(
    const std::shared_ptr<Object> &object,
    std::vector<std::shared_ptr<Object>> &objects_buffer,
    const Matrix4 &parent) const {
    object->updateMatrixWorld(parent);
    objects_buffer.push_back(object);
    for (const auto &child : object->children()) {
        fillObjectsBuffer(child, objects_buffer, object->matrixWorld());
    }
}

} // namespace TotoGL
