#include "Materials/PhongMaterial.hpp"

namespace TotoGL {

const char *phong_vertex = R"glsl(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 Position;
out vec3 Normal;
out vec2 TexCoords;
out vec3 Color;
out vec3 ViewDirection;

void main()
{
    vec4 model_position = model * vec4(aPos, 1.0);

    Position = vec3(model_position);
    Normal = mat3(transpose(inverse(model))) * aNormal;
    TexCoords = aTexCoords;
    Color = aColor;
    ViewDirection = normalize(Position - vec3(view[3]));

    gl_Position = projection * view * model_position;
}
)glsl";


const char *phong_fragment = R"glsl(
#version 330 core
#define MAX_LIGHT 16

out vec4 FragColor;

in vec3 Position;
in vec3 Normal;
in vec2 TexCoords;
in vec3 Color;
in vec3 ViewDirection;

struct AmbientLight {
    vec3 color;
    float strength;
};
struct PointLight {
    vec3 position;
    vec3 color;
    float strength;
};
struct DirectionalLight {
    vec3 direction;
    vec3 color;
    float strength;
};

uniform vec3 emissive_color;
uniform sampler2D emissive_texture;
uniform bool emissive_is_texture;
uniform vec3 diffuse_color;
uniform sampler2D diffuse_texture;
uniform bool diffuse_is_texture;
uniform vec3 specular_color;
uniform sampler2D specular_texture;
uniform bool specular_is_texture;
uniform float shininess;
uniform float emissive_strength;

uniform AmbientLight ambient_light[MAX_LIGHT];
uniform PointLight point_light[MAX_LIGHT];
uniform DirectionalLight directional_light[MAX_LIGHT];

vec3 getColorOrTexture(vec2 uv, vec3 color, sampler2D image, bool is_texture) {
    return is_texture ? texture(image, uv).rgb : color;
}

vec3 getDirectionalLight(DirectionalLight light, vec3 diffuse, vec3 specular) {
    vec3 normal = normalize(Normal);
    vec3 light_dir = normalize(light.direction);
    // diffuse shading
    float diff = max(dot(normal, -light_dir), 0.0);
    // specular shading
    vec3 reflect_dir = reflect(light_dir, normal);
    float spec = pow(max(dot(ViewDirection, reflect_dir), 0.0), shininess);
    // combine results
    vec3 diffuse_color  = light.color * diff * diffuse;
    vec3 specular_color = light.color * spec * specular;
    
    return (diffuse_color + specular_color);
}

void main() {
    FragColor = vec4(0,0,0,1);
    vec3 emissive = getColorOrTexture(TexCoords, emissive_color, emissive_texture, emissive_is_texture);
    vec3 diffuse = getColorOrTexture(TexCoords, diffuse_color, diffuse_texture, diffuse_is_texture);
    vec3 specular = getColorOrTexture(TexCoords, specular_color, specular_texture, specular_is_texture);
    
    vec3 result = emissive * Color * emissive_strength;

    for(int i = 0; i < MAX_LIGHT; i++) {
        result += diffuse * ambient_light[i].color * ambient_light[i].strength;
        result += getDirectionalLight(directional_light[i], diffuse, specular);
    }

    FragColor = vec4(result, 1.0);
}
)glsl";

}
