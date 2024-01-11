#pragma once

#include "Light.hpp"
#include <glm/geometric.hpp>

namespace TotoGL {

class DirectionalLight : public Light {
public:
    DirectionalLight() = default;
    ~DirectionalLight() override = default;
    static std::shared_ptr<DirectionalLight> create() {
        return std::make_shared<DirectionalLight>();
    }

    const Vector3 &direction() const { return _direction; }
    Vector3 &direction() { return _direction; }

    const Vector3 &worldDirection() const { return _world_direction; }

private:
    Vector3 _direction;
    Vector3 _world_direction;

    void updateMatrixWorld(const Matrix4 &parent) override {
        Light::updateMatrixWorld(parent);
        _world_direction = Vector4(glm::normalize(Vector3(matrixWorld() * Vector4(_direction, 1))), 1);
    }
};

} // namespace TotoGL
