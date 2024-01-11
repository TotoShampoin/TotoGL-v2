#pragma once

#include "Material.hpp"
#include <initializer_list>
#include <memory>
#include <vector>

namespace TotoGL {

class MultiMaterial : public Material {
public:
    MultiMaterial(const std::initializer_list<std::shared_ptr<Material>> &mats)
        : _materials(mats) {}
    ~MultiMaterial() override = default;
    static std::shared_ptr<MultiMaterial>
    create(const std::initializer_list<std::shared_ptr<Material>> &mats) {
        return std::make_shared<MultiMaterial>(mats);
    }

    const std::vector<std::shared_ptr<Material>> &materials() const {
        return _materials;
    }

    // I don't actually need those, because
    // I'll access each mat individually
    void applyModel(const Matrix4 &) override {}
    void applyCamera(const std::shared_ptr<Camera> &) override {}
    void applyLight(const std::shared_ptr<Light> &, const size_t &) override {}
    void applyLights(const std::vector<std::shared_ptr<Light>> &) override {}
    void activate() override {}
    void deactivate() override {}

private:
    std::vector<std::shared_ptr<Material>> _materials;
};
using MultiMaterialPtr = std::shared_ptr<MultiMaterial>;

} // namespace TotoGL
