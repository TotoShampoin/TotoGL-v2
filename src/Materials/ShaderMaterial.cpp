#include <GL/glew.h>

#include "Lights/AmbientLight.hpp"
#include "Lights/DirectionalLight.hpp"
#include "Lights/PointLight.hpp"
#include "Materials/ShaderMaterial.hpp"
#include "Primitives/Primitives.hpp"
#include "Primitives/Texture.hpp"
#include <format>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <variant>

namespace TotoGL {

void checkShader(GLuint shader) {
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::ostringstream oss;
        oss << "Shader compilation error:\n" << infoLog;
        throw std::runtime_error(oss.str());
    }
}

ShaderMaterial::ShaderMaterial(
    const std::string &vertex_source, const std::string &fragment_source) {
    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    const char *vertexShaderSource = vertex_source.c_str();
    glShaderSource(vertex_shader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertex_shader);
    checkShader(vertex_shader);

    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    const char *fragmentShaderSource = fragment_source.c_str();
    glShaderSource(fragment_shader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragment_shader);
    checkShader(fragment_shader);

    _program_id = glCreateProgram();
    glAttachShader(_program_id, vertex_shader);
    glAttachShader(_program_id, fragment_shader);
    glLinkProgram(_program_id);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

ShaderMaterial::~ShaderMaterial() {
    glDeleteProgram(_program_id);
}

void ShaderMaterial::activate() {
    glUseProgram(_program_id);
    int index_of_texture = 0;
    for (const auto &[id, value] : _uniforms) {
        auto visitor = UniformVisitor{ _program_id, id, index_of_texture };
        std::visit(visitor, value);
        index_of_texture +=
            std::holds_alternative<std::shared_ptr<Texture>>(value);
    }
}

void ShaderMaterial::deactivate() {
    glUseProgram(GL_NONE);
}

int ShaderMaterial::uniformId(const std::string &name) const {
    return glGetUniformLocation(_program_id, name.c_str());
}

void ShaderMaterial::applyModel(const Matrix4 &model) {
    uniform("model") = model;
}

void ShaderMaterial::applyCamera(const std::shared_ptr<Camera> &camera) {
    uniform("view") = camera->matrixWorldInverse();
    uniform("projection") = camera->projectionMatrix();
}

void ShaderMaterial::applyLight(
    const std::shared_ptr<Light> &light, const size_t &idx) {
    auto light_idx = std::format("_light[{}].", idx);
    if (auto ambient_light = std::dynamic_pointer_cast<AmbientLight>(light)) {
        uniform("ambient" + light_idx + "color") = ambient_light->color();
        uniform("ambient" + light_idx + "strength") = ambient_light->strength();
    } else if (auto pointLight = std::dynamic_pointer_cast<PointLight>(light)) {
        uniform("point" + light_idx + "position") = pointLight->worldPosition();
        uniform("point" + light_idx + "color") = pointLight->color();
        uniform("point" + light_idx + "strength") = pointLight->strength();
    } else if (
        auto directionalLight =
            std::dynamic_pointer_cast<DirectionalLight>(light)) {
        uniform("directional" + light_idx + "direction") =
            directionalLight->worldDirection();
        uniform("directional" + light_idx + "color") =
            directionalLight->color();
        uniform("directional" + light_idx + "strength") =
            directionalLight->strength();
    }
}

void ShaderMaterial::applyLights(
    const std::vector<std::shared_ptr<Light>> &lights) {
    size_t i = 0;
    for (const auto &light : lights) {
        applyLight(light, i++);
    }
}

void ShaderMaterial::applyBackground(const ColorVariant &background) {
    bool is_texture = std::holds_alternative<TexturePtr>(background);
    if(is_texture) {
        uniform("environment_texture") = std::get<TexturePtr>(background);
    } else {
        uniform("environment_color") = std::get<ColorRGB>(background);
    }
    uniform("environment_is_texture") = is_texture;
}

} // namespace TotoGL
