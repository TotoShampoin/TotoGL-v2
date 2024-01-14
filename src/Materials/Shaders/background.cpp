#include "Renderers/GL3Renderer.hpp"

namespace TotoGL {

const char* background_vertex = R"glsl(
#version 330
layout (location = 0) in vec3 aPos;

uniform mat4 projection;
uniform mat4 view;

out vec3 VertPos;

void main() {
    gl_Position = vec4(aPos, 1.0); // DO NOT TOUCH, THIS IS A FULLSCREEN QUAD MESH
    VertPos = aPos;
}
)glsl";


const char* background_fragment = R"glsl(
#version 330
#define PI 3.1415926535

in vec3 VertPos;
out vec4 FragColor;

uniform mat4 projection;
uniform mat4 view;

uniform sampler2D background_texture;
uniform vec3 background_color;
uniform bool background_is_texture;

vec2 directionToUV(vec3 direction) {
    float u = 0.5 + atan(direction.z, direction.x) / (2.0 * PI);
    float v = 0.5 - asin(direction.y) / PI;
    return vec2(u, v);
}

void main() {
    if(background_is_texture) {
        vec4 clip_pos = vec4(VertPos, 1);
        vec4 eye_pos = inverse(projection) * clip_pos;
        eye_pos = vec4(eye_pos.xy, -1.0, 0.0);
        vec4 world_pos = inverse(view) * eye_pos;
        
        vec3 ray_direction = normalize(world_pos.xyz);
        vec2 uv = directionToUV(ray_direction);
        vec3 color = texture(background_texture, uv).rgb;
        FragColor = vec4(color, 1.0);
    } else {
        FragColor = vec4(background_color, 1.0);
    }
}
)glsl";

}
