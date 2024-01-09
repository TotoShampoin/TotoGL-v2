#pragma once

#include <glm/glm.hpp>
#include <glm/ext/scalar_constants.hpp>

namespace TotoGL {

constexpr static auto PI = glm::pi<float>();

// alias for glm vector
using Vector2 = glm::vec2;
using Vector3 = glm::vec3;
using Vector4 = glm::vec4;
// alias for glm matrix
using Matrix2 = glm::mat2;
using Matrix3 = glm::mat3;
using Matrix4 = glm::mat4;

using ColorRGB = glm::vec3;
using ColorRGBA = glm::vec4;

}
