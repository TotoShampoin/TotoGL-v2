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
    PhongMaterial(
        const ColorVariant &diffuse = ColorRGB(0),
        const ColorVariant &specular = ColorRGB(0),
        const float &shininess = 4.f,
        const ColorVariant &emissive = ColorRGB(0),
        const float &emissive_strength = 0.);
    ~PhongMaterial() override = default;
    static std::shared_ptr<PhongMaterial> create(
        const ColorVariant &diffuse = ColorRGB(0),
        const ColorVariant &specular = ColorRGB(0),
        const float &shininess = 4.f,
        const ColorVariant &emissive = ColorRGB(0),
        const float &emissive_strength = 0.) {
        return std::make_shared<PhongMaterial>(
            diffuse,
            specular,
            shininess,
            emissive,
            emissive_strength);
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
    ColorVariant _emissive;
    ColorVariant _diffuse;
    ColorVariant _specular;
    float _shininess;
    float _emissive_strength;
};
using PhongMaterialPtr = std::shared_ptr<PhongMaterial>;

} // namespace TotoGL
