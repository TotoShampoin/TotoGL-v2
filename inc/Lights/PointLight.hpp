#pragma once

#include "Light.hpp"
#include "Primitives/Primitives.hpp"

namespace TotoGL {

class PointLight : public Light {
public:
    PointLight() = default;
    ~PointLight() override = default;
    static std::shared_ptr<PointLight> create() {
        return std::make_shared<PointLight>();
    }

    const Vector3 &position() const { return _position; }
    Vector3 &position() { return _position; }

    const Vector3 &worldPosition() const { return _world_position; }

private:
    Vector3 _position;
    Vector3 _world_position;

    void updateMatrixWorld(const Matrix4 &parent) override {
        Light::updateMatrixWorld(parent);
        _world_position = matrixWorld() * Vector4(_position, 1);
    }
};

} // namespace TotoGL
