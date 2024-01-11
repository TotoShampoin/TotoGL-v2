#pragma once

#include "Materials/Material.hpp"
#include "Materials/ShaderMaterial.hpp"
#include "Primitives/Primitives.hpp"
#include "Primitives/Texture.hpp"
#include <memory>

namespace TotoGL {

extern const char *basic_fragment;

class BasicMaterial : public Material {
public:
    BasicMaterial(
        const ColorRGB &color = ColorRGB(1.),
        const std::shared_ptr<Texture> &texture = nullptr);
    ~BasicMaterial() override = default;
    static std::shared_ptr<BasicMaterial> create(const ColorRGB &color) {
        return std::make_shared<BasicMaterial>(color);
    }

    void color(const ColorRGB &color);
    void texture(const std::shared_ptr<Texture> &texture);

    const ColorRGB &color() const { return _color; }
    const std::shared_ptr<Texture> &texture() const { return _texture; }

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
    void activate() override { _shader->activate(); }
    void deactivate() override { _shader->deactivate(); }

private:
    std::shared_ptr<ShaderMaterial> _shader =
        ShaderMaterial::create(simple_vertex, basic_fragment);
    ColorRGB _color;
    std::shared_ptr<Texture> _texture;
};
using BasicMaterialPtr = std::shared_ptr<BasicMaterial>;

} // namespace TotoGL
