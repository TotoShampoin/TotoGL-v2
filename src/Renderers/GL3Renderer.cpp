#include <GL/glew.h> // MUST BE FIRST

#include "Materials/BasicMaterial.hpp"
#include "Materials/MultiMaterial.hpp"
#include "Materials/ShaderMaterial.hpp"
#include "Mesh.hpp"
#include "Primitives/Geometry.hpp"
#include "Primitives/Primitives.hpp"
#include "Primitives/Texture.hpp"
#include "Renderers/GL3Renderer.hpp"
#include <GL/gl.h>
#include <sstream>
#include <variant>

namespace TotoGL {

void GL3Renderer::init() {
    static bool is_glew_init = false;
    if (is_glew_init)
        return;
    auto init = glewInit();
    if (init) {
        std::ostringstream oss;
        oss << "Couldn't initialize opengl renderer: "
            << glewGetErrorString(init);
        throw std::runtime_error(oss.str());
    }
}

GL3Renderer::GL3Renderer(const std::shared_ptr<Window> &window)
    : Renderer(window) {
    Renderer::window()->makeContextCurrent();
    init();
}

GL3Renderer::~GL3Renderer() {
}

void GL3Renderer::render(
    const std::shared_ptr<Scene> &scene,
    const std::shared_ptr<Camera> &camera) const {
    const auto &[width, height] = window()->size();
    glViewport(0, 0, width, height);
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    auto objects_buffer = getObjectsBuffer(scene);
    auto meshes = Object::filter<Mesh>(objects_buffer);
    auto lights = Object::filter<Light>(objects_buffer);

    render_background(camera);
    glClear(GL_DEPTH_BUFFER_BIT);
    for (const auto &mesh : meshes) {
        render_impl(mesh, camera, lights);
    }
}

void GL3Renderer::render_background(const std::shared_ptr<Camera> &camera) const {
    static auto quad = PlaneGeometry::create(2, 2);
    static auto bg = ShaderMaterial::create(background_vertex, background_fragment);
    bool is_texture = std::holds_alternative<TexturePtr>(_background);
    if(is_texture) {
        bg->uniform("background_texture") = std::get<TexturePtr>(_background);
    } else {
        bg->uniform("background_color") = std::get<ColorRGB>(_background);
    }
    bg->uniform("background_is_texture") = is_texture;
    bg->applyCamera(camera); // view and projection
    bg->activate();
    quad->draw();
    bg->deactivate();
}

void GL3Renderer::render_impl(
    const std::shared_ptr<Mesh> &mesh, const std::shared_ptr<Camera> &camera,
    const std::vector<std::shared_ptr<Light>> &lights) const {
    auto geometry = mesh->geometry();
    auto material = mesh->material();

    auto draw_mesh = [&](const std::shared_ptr<Material> &material,
                         const std::optional<size_t> &idx = std::nullopt) {
        material->applyModel(mesh->matrixWorld());
        material->applyCamera(camera);
        material->applyLights(lights);
        material->applyBackground(background());
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
GL3Renderer::getObjectsBuffer(const std::shared_ptr<Scene> &scene) const {
    std::vector<std::shared_ptr<Object>> objects_buffer;
    fillObjectsBuffer(scene, objects_buffer);
    return objects_buffer;
}

void GL3Renderer::fillObjectsBuffer(
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
