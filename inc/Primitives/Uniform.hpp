#pragma once

#include "Primitives/Primitives.hpp"
#include "Primitives/Texture.hpp"
#include <memory>
#include <variant>
#include <vector>

namespace TotoGL {

using Uniform = std::variant<
    int, float, bool, std::vector<int>, std::vector<float>, std::vector<bool>,
    Vector2, Vector3, Vector4, Matrix2, Matrix3, Matrix4,
    TexturePtr>;

struct UniformVisitor {
    uint program_id;
    int id;
    int index_of_texture = 0;
    void operator()(const int &value);
    void operator()(const float &value);
    void operator()(const bool &value);
    void operator()(const std::vector<int> &value);
    void operator()(const std::vector<float> &value);
    void operator()(const std::vector<bool> &value);
    void operator()(const Vector2 &value);
    void operator()(const Vector3 &value);
    void operator()(const Vector4 &value);
    void operator()(const Matrix2 &value);
    void operator()(const Matrix3 &value);
    void operator()(const Matrix4 &value);
    void operator()(const TexturePtr &value);
};

} // namespace TotoGL
