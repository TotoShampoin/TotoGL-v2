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

void PhongMaterial::emissive(const ColorVariant& emissive) {
    _emissive = emissive;
    bool is_texture = std::holds_alternative<std::shared_ptr<Texture>>(emissive);
    _shader->uniform("emissive_is_texture") = is_texture;
    if(is_texture) {
        _shader->uniform("emissive_color") = std::get<std::shared_ptr<Texture>>(emissive);
    } else {
        _shader->uniform("emissive_texture") = std::get<ColorRGB>(emissive);
    }
}
void PhongMaterial::diffuse(const ColorVariant& diffuse) {
    _diffuse = diffuse;
    bool is_texture = std::holds_alternative<std::shared_ptr<Texture>>(diffuse);
    _shader->uniform("diffuse_is_texture") = is_texture;
    if(is_texture) {
        _shader->uniform("diffuse_color") = std::get<std::shared_ptr<Texture>>(diffuse);
    } else {
        _shader->uniform("diffuse_texture") = std::get<ColorRGB>(diffuse);
    }
}
void PhongMaterial::specular(const ColorVariant& specular) {
    _specular = specular;
    bool is_texture = std::holds_alternative<std::shared_ptr<Texture>>(specular);
    _shader->uniform("specular_is_texture") = is_texture;
    if(is_texture) {
        _shader->uniform("specular_color") = std::get<std::shared_ptr<Texture>>(specular);
    } else {
        _shader->uniform("specular_texture") = std::get<ColorRGB>(specular);
    }
}
void PhongMaterial::shininess(const float& shininess) {
    _shininess = shininess;
    _shader->uniform("shininess") = shininess;
}

const char* phong_vertex = R"glsl(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 Normal;
out vec2 TexCoords;
out vec3 Color;
out vec3 ViewDir;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    Normal = mat3(transpose(inverse(model))) * aNormal;
    TexCoords = aTexCoords;
    Color = aColor;

    vec3 viewPos = vec3(-transpose(mat3(view)) * view[3].xyz);
    vec4 worldPos = model * vec4(aPos, 1.0);
    ViewDir = normalize(viewPos - vec3(worldPos));
}
)glsl";

const char* phong_fragment = R"glsl(
#version 330 core
#define MAX_LIGHT 16

out vec4 FragColor;

in vec3 Normal;
in vec2 TexCoords;
in vec3 Color;
out vec3 ViewDir;

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
uniform sampler2D normal_map;
uniform bool has_normal_map;

uniform AmbientLight emissive_light[MAX_LIGHT];
uniform PointLight point_light[MAX_LIGHT];
uniform DirectionalLight directional_light[MAX_LIGHT];

vec3 getColorOrTexture(vec2 uv, vec3 color, sampler2D image, bool is_texture) {
    return is_texture ? color : texture(image, uv).rgb;
}

void main() {
    vec3 norm = normalize(Normal);

    FragColor = vec4(0,0,0,1);
    vec3 emissive = getColorOrTexture(TexCoords, emissive_color, emissive_texture, emissive_is_texture);
    vec3 diffuse = getColorOrTexture(TexCoords, diffuse_color, diffuse_texture, diffuse_is_texture);
    vec3 specular = getColorOrTexture(TexCoords, specular_color, specular_texture, specular_is_texture);
    
    vec3 result = emissive * Color;

    for(int i = 0; i < MAX_LIGHT; i++) {
        vec3 light_dir = normalize(point_light[i].position - gl_FragCoord.xyz);
        float diff = max(dot(norm, light_dir), 0.0);
        result += diff * diffuse * point_light[i].color * point_light[i].strength;

        vec3 halfway_dir = normalize(light_dir + ViewDir);
        float spec = pow(max(dot(norm, halfway_dir), 0.0), shininess);
        result += spec * specular * point_light[i].color * point_light[i].strength;
    }

    FragColor = vec4(result, 1.0);
}
)glsl";

}
