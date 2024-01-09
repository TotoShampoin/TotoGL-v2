#include "Materials/BasicMaterial.hpp"

namespace TotoGL {

BasicMaterial::BasicMaterial(const ColorRGB& color, const std::shared_ptr<Texture>& texture)
    : _color(color), _texture(texture) {
        _shader->uniform("color") = _color;
        _shader->uniform("map") = _texture;
        _shader->uniform("has_texture") = false;
    }

void BasicMaterial::color(const ColorRGB& color) {
    _color = color;
    _shader->uniform("color") = _color;
}
void BasicMaterial::texture(const std::shared_ptr<Texture>& texture) {
    _texture = texture;
    _shader->uniform("has_texture") = (_texture != nullptr);
    _shader->uniform("map") = _texture;
}

const char* basic_fragment = R"glsl(
#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec2 TexCoords;
in vec3 Color;

uniform vec3 color;
uniform sampler2D map;
uniform bool has_texture;

void main() {
    FragColor = vec4(0,0,0,1);
    FragColor.rgb = Color * color;
    if(has_texture) {
        FragColor.rgb *= texture(map, TexCoords).rgb;
    }
}

)glsl";

}