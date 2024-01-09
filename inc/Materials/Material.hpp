#pragma once

#include "Cameras/Camera.hpp"
#include "Lights/Light.hpp"
#include "Primitives/Primitives.hpp"
#include <memory>
#include <vector>

namespace TotoGL {

class Material {
public:
    virtual ~Material() = default;
    virtual void applyModel(const Matrix4 &) = 0;
    virtual void applyCamera(const std::shared_ptr<Camera> &) = 0;
    virtual void
    applyLight(const std::shared_ptr<Light> &, const size_t & = 0) = 0;
    virtual void applyLights(const std::vector<std::shared_ptr<Light>> &) = 0;
    virtual void activate() = 0;
    virtual void deactivate() = 0;
};

} // namespace TotoGL
