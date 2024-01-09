#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

#include "Primitives/Uniform.hpp"
#include "Primitives/Texture.hpp"

namespace TotoGL {

void UniformVisitor::operator()(const int& value) {
    glUniform1i(id, value);
}

void UniformVisitor::operator()(const float& value) {
    glUniform1f(id, value);
}

void UniformVisitor::operator()(const bool& value) {
    glUniform1i(id, value);
}

void UniformVisitor::operator()(const std::vector<int>& value) {
    glUniform1iv(id, value.size(), value.data());
}

void UniformVisitor::operator()(const std::vector<float>& value) {
    glUniform1fv(id, value.size(), value.data());
}

void UniformVisitor::operator()(const std::vector<bool>& value) {
    std::vector<int> intVec(value.begin(), value.end());
    glUniform1iv(id, intVec.size(), intVec.data());
}

void UniformVisitor::operator()(const Vector2& value) {
    glUniform2fv(id, 1, glm::value_ptr(value));
}

void UniformVisitor::operator()(const Vector3& value) {
    glUniform3fv(id, 1, glm::value_ptr(value));
}

void UniformVisitor::operator()(const Vector4& value) {
    glUniform4fv(id, 1, glm::value_ptr(value));
}

void UniformVisitor::operator()(const Matrix2& value) {
    glUniformMatrix2fv(id, 1, GL_FALSE, glm::value_ptr(value));
}

void UniformVisitor::operator()(const Matrix3& value) {
    glUniformMatrix3fv(id, 1, GL_FALSE, glm::value_ptr(value));
}

void UniformVisitor::operator()(const Matrix4& value) {
    glUniformMatrix4fv(id, 1, GL_FALSE, glm::value_ptr(value));
}

void UniformVisitor::operator()(const std::shared_ptr<Texture>& texture) {
    glActiveTexture(GL_TEXTURE0 + index_of_texture);
    glBindTexture(GL_TEXTURE_2D, texture->textureId());
    glUniform1i(id, index_of_texture);
}

}
