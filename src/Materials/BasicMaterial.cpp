#include "Materials/BasicMaterial.hpp"
#include "Primitives/Primitives.hpp"
#include "Primitives/Texture.hpp"
#include <variant>

namespace TotoGL {

BasicMaterial::BasicMaterial(
    const ColorRGB &color, const std::shared_ptr<Texture> &texture)
    : _color(color), _texture(texture) {
    _shader->uniform("color") = _color;
    _shader->uniform("map") = _texture;
    _shader->uniform("has_texture") = false;
}
BasicMaterial::BasicMaterial(const ColorVariant &color) {
    if (std::holds_alternative<TexturePtr>(color)) {
        _texture = std::get<TexturePtr>(color);
    } else {
        _color = std::get<ColorRGB>(color);
    }
    _shader->uniform("color") = _color;
    _shader->uniform("map") = _texture;
    _shader->uniform("has_texture") = false;
}

void BasicMaterial::color(const ColorRGB &color) {
    _color = color;
    _shader->uniform("color") = _color;
}
void BasicMaterial::texture(const std::shared_ptr<Texture> &texture) {
    _texture = texture;
    _shader->uniform("has_texture") = (_texture != nullptr);
    _shader->uniform("map") = _texture;
}

} // namespace TotoGL