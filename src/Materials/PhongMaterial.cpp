#include "Materials/PhongMaterial.hpp"
#include "Primitives/Primitives.hpp"
#include "Primitives/Texture.hpp"
#include <memory>
#include <variant>

namespace TotoGL {

PhongMaterial::PhongMaterial() {
    emissive(_emissive);
    diffuse(_diffuse);
    specular(_specular);
    shininess(_shininess);
}

void PhongMaterial::emissive(const ColorVariant &emissive) {
    _emissive = emissive;
    bool is_texture =
        std::holds_alternative<std::shared_ptr<Texture>>(emissive);
    _shader->uniform("emissive_is_texture") = is_texture;
    if (is_texture) {
        _shader->uniform("emissive_texture") =
            std::get<std::shared_ptr<Texture>>(emissive);
    } else {
        _shader->uniform("emissive_color") = std::get<ColorRGB>(emissive);
    }
}
void PhongMaterial::diffuse(const ColorVariant &diffuse) {
    _diffuse = diffuse;
    bool is_texture = std::holds_alternative<std::shared_ptr<Texture>>(diffuse);
    _shader->uniform("diffuse_is_texture") = is_texture;
    if (is_texture) {
        _shader->uniform("diffuse_texture") =
            std::get<std::shared_ptr<Texture>>(diffuse);
    } else {
        _shader->uniform("diffuse_color") = std::get<ColorRGB>(diffuse);
    }
}
void PhongMaterial::specular(const ColorVariant &specular) {
    _specular = specular;
    bool is_texture =
        std::holds_alternative<std::shared_ptr<Texture>>(specular);
    _shader->uniform("specular_is_texture") = is_texture;
    if (is_texture) {
        _shader->uniform("specular_texture") =
            std::get<std::shared_ptr<Texture>>(specular);
    } else {
        _shader->uniform("specular_color") = std::get<ColorRGB>(specular);
    }
}
void PhongMaterial::shininess(const float &shininess) {
    _shininess = shininess;
    _shader->uniform("shininess") = shininess;
}
void PhongMaterial::emissiveStrength(const float &emissive_strength) {
    _emissive_strength = emissive_strength;
    _shader->uniform("emissive_strength") = emissive_strength;
}

} // namespace TotoGL
