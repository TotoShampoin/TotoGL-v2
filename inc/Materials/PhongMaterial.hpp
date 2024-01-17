#pragma once

#include "Materials/Material.hpp"
#include "Materials/ShaderMaterial.hpp"
#include "Primitives/Primitives.hpp"
#include "Primitives/Texture.hpp"
#include <memory>

namespace TotoGL {

extern const char *phong_vertex;
extern const char *phong_fragment;

class PhongMaterial : public Material {
public:
    PhongMaterial();
    ~PhongMaterial() override = default;
    static std::shared_ptr<PhongMaterial> create() {
        return std::make_shared<PhongMaterial>();
    }

    void emissive(const ColorVariant &);
    void diffuse(const ColorVariant &);
    void specular(const ColorVariant &);
    void shininess(const float &);
    void emissiveStrength(const float &);

    const ColorVariant &emissive() const { return _emissive; }
    const ColorVariant &diffuse() const { return _diffuse; }
    const ColorVariant &specular() const { return _specular; }
    const float &shininess() const { return _shininess; }
    const float &emissiveStrength() const { return _emissive_strength; }

    void applyModel(const Matrix4 &model) override {
        _shader->applyModel(model);
    }
    void applyCamera(const std::shared_ptr<Camera> &camera) override {
        _shader->applyCamera(camera);
    }
    void applyLight(
        const std::shared_ptr<Light> &light, const size_t &idx = 0) override {
        _shader->applyLight(light, idx);
    }
    void
    applyLights(const std::vector<std::shared_ptr<Light>> &lights) override {
        _shader->applyLights(lights);
    }
    void applyBackground(const ColorVariant &background) override {
        _shader->applyBackground(background);
    }
    void activate() override { _shader->activate(); }
    void deactivate() override { _shader->deactivate(); }

private:
    std::shared_ptr<ShaderMaterial> _shader =
        ShaderMaterial::create(phong_vertex, phong_fragment);
    ColorVariant _emissive{ ColorRGB{ 0 } };
    ColorVariant _diffuse{ ColorRGB{ 0 } };
    ColorVariant _specular{ ColorRGB{ 0 } };
    float _shininess{ 4. };
    float _emissive_strength{ 1. };
};
using PhongMaterialPtr = std::shared_ptr<PhongMaterial>;

} // namespace TotoGL
