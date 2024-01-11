#pragma once

#include "Light.hpp"

namespace TotoGL {

class AmbientLight : public Light {
public:
    AmbientLight() = default;
    ~AmbientLight() override = default;
    static std::shared_ptr<AmbientLight> create() {
        return std::make_shared<AmbientLight>();
    }

private:
    void updateMatrixWorld(const Matrix4 &parent) override {
        Light::updateMatrixWorld(parent);
    }
};
using AmbientLightPtr = std::shared_ptr<AmbientLight>;

} // namespace TotoGL
