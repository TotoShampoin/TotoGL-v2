#pragma once
#include "Primitives/Object.hpp"
#include "Primitives/Primitives.hpp"
#include <memory>

namespace TotoGL {

class Camera : public Object {
public:
    ~Camera() override = default;
    Matrix4 matrixWorldInverse() const;
    virtual Matrix4 projectionMatrix() const = 0;
    Matrix4 projectionMatrixInverse() const;

private:
};
using CameraPtr = std::shared_ptr<Camera>;

} // namespace TotoGL
