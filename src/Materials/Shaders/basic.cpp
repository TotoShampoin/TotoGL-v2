#include "Materials/BasicMaterial.hpp"

namespace TotoGL {

const char *basic_fragment = R"glsl(
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
