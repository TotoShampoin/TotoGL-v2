#include <GL/glew.h>

#include "Materials/ShaderMaterial.hpp"
#include "Lights/AmbientLight.hpp"
#include "Lights/DirectionalLight.hpp"
#include "Lights/PointLight.hpp"
#include "Primitives/Texture.hpp"
#include <memory>
#include <format>
#include <sstream>
#include <stdexcept>
#include <variant>

namespace TotoGL {

void checkShader(GLuint shader) {
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::ostringstream oss;
        oss << "Shader compilation error:\n" << infoLog;
        throw std::runtime_error(oss.str());
    }
}

ShaderMaterial::ShaderMaterial(const std::string& vertex_source, const std::string& fragment_source) {
    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    const char* vertexShaderSource = vertex_source.c_str();
    glShaderSource(vertex_shader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertex_shader);
    checkShader(vertex_shader);

    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragmentShaderSource = fragment_source.c_str();
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
    for(const auto& [id, value] : _uniforms) {
        auto visitor = UniformVisitor {_program_id, id, index_of_texture};
        std::visit(visitor, value);
        index_of_texture += std::holds_alternative<std::shared_ptr<Texture>>(value);
    }
}

void ShaderMaterial::deactivate() {
    glUseProgram(GL_NONE);
}

int ShaderMaterial::uniformId(const std::string& name) const {
    return glGetUniformLocation(_program_id, name.c_str());
}

void ShaderMaterial::applyModel(const Matrix4& model) {
    uniform("model") = model;
}

void ShaderMaterial::applyCamera(const std::shared_ptr<Camera>& camera) {
    uniform("view") = camera->matrixWorldInverse();
    uniform("projection") = camera->projectionMatrix();
}

void ShaderMaterial::applyLight(const std::shared_ptr<Light>& light, const size_t& idx) {
    auto light_idx = std::format("_light[{}].", idx);
    if (auto ambient_light = std::dynamic_pointer_cast<AmbientLight>(light)) {
        uniform("ambient"+light_idx+"color") = ambient_light->color();
        uniform("ambient"+light_idx+"strength") = ambient_light->strength();
    } else if (auto pointLight = std::dynamic_pointer_cast<PointLight>(light)) {
        uniform("point"+light_idx+"position") = pointLight->position();
        uniform("point"+light_idx+"color") = pointLight->color();
        uniform("point"+light_idx+"strength") = pointLight->strength();
    } else if (auto directionalLight = std::dynamic_pointer_cast<DirectionalLight>(light)) {
        uniform("directional"+light_idx+"direction") = directionalLight->direction();
        uniform("directional"+light_idx+"color") = directionalLight->color();
        uniform("directional"+light_idx+"strength") = directionalLight->strength();
    }
}

void ShaderMaterial::applyLights(const std::vector<std::shared_ptr<Light>>& lights) {
    size_t i = 0;
    for(const auto& light : lights) {
        applyLight(light, i++);
    }
}

const char* simple_vertex = R"glsl(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 Normal;
out vec2 TexCoords;
out vec3 Color;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    Normal = mat3(transpose(inverse(model))) * aNormal;
    TexCoords = aTexCoords;
    Color = aColor;
}
)glsl";

}
