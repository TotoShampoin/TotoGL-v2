#pragma once

#include "Primitives/Object.hpp"
#include "Primitives/Primitives.hpp"
#include <memory>

namespace TotoGL {

class Light : public Object {
public:
    virtual ~Light() = default;
    ColorRGB &color() { return _color; }
    float &strength() { return _strength; }
    const ColorRGB &color() const { return _color; }
    const float &strength() const { return _strength; }

protected:
    virtual void updateMatrixWorld(const Matrix4 &parent) override {
        Object::updateMatrixWorld(parent);
    }

private:
    ColorRGB _color{ 1, 1, 1 };
    float _strength{ 1 };
};
using LightPtr = std::shared_ptr<Light>;

} // namespace TotoGL
