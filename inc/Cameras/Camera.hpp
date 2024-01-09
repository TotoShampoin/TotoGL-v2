#pragma once
#include "Primitives/Object.hpp"
#include "Primitives/Primitives.hpp"

namespace TotoGL {

class Camera : public Object {
public:
    ~Camera() override = default;
    Matrix4 matrixWorldInverse() const;
    virtual Matrix4 projectionMatrix() const = 0;
    Matrix4 projectionMatrixInverse() const;

private:
};

} // namespace TotoGL
