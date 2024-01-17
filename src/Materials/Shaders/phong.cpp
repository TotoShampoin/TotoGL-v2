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
    ViewDirection = mat3(inverse(view)) * normalize(Position - vec3(view[3]));

    gl_Position = projection * view * model_position;
}
)glsl";

const char *phong_fragment = R"glsl(
#version 330 core

#define PI 3.1415927535
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

uniform sampler2D environment_texture;
uniform vec3 environment_color;
uniform bool environment_is_texture;

uniform AmbientLight ambient_light[MAX_LIGHT];
uniform PointLight point_light[MAX_LIGHT];
uniform DirectionalLight directional_light[MAX_LIGHT];

vec2 directionToUV(vec3 direction) {
    float u = 0.5 + atan(direction.z, direction.x) / (2.0 * PI);
    float v = 0.5 - asin(direction.y) / PI;
    return vec2(u, v);
}

vec3 getColorOrTexture(vec2 uv, vec3 color, sampler2D image, bool is_texture) {
    return is_texture ? texture(image, uv).rgb : color;
}

vec3 getDirectionalLight(DirectionalLight light, float distance, vec3 diffuse, vec3 specular) {
    vec3 normal = normalize(Normal);
    vec3 light_dir = normalize(-light.direction);
    float strength = 1 / (distance * distance);
    // diffuse shading
    float diff = max(dot(normal, light_dir), 0.0);
    // specular shading
    vec3 reflect_dir = reflect(-light_dir, normal);
    float spec = pow(max(dot(ViewDirection, reflect_dir), 0.0), shininess);
    // combine results
    vec3 diffuse_color  = light.color * light.strength * diff * diffuse * strength;
    vec3 specular_color = light.color * light.strength * spec * specular * strength;
    
    return (diffuse_color + specular_color);
}

// very naive approach, also very wrong
vec3 environmentLight(vec3 diffuse, vec3 specular) {
    DirectionalLight environment_light;
    environment_light.direction = -Normal;
    environment_light.color = getColorOrTexture(directionToUV(-environment_light.direction), environment_color, environment_texture, environment_is_texture).rgb;
    environment_light.strength = 1.0;
    return getDirectionalLight(environment_light, 1, diffuse, specular);
}

void main() {
    FragColor = vec4(0,0,0,1);
    vec3 emissive = getColorOrTexture(TexCoords, emissive_color, emissive_texture, emissive_is_texture);
    vec3 diffuse = getColorOrTexture(TexCoords, diffuse_color, diffuse_texture, diffuse_is_texture);
    vec3 specular = getColorOrTexture(TexCoords, specular_color, specular_texture, specular_is_texture);
    
    vec3 result = emissive * Color * emissive_strength;

    // result += environmentLight(diffuse, specular);

    for(int i = 0; i < MAX_LIGHT; i++) {
        result += diffuse * ambient_light[i].color * ambient_light[i].strength;
        result += getDirectionalLight(directional_light[i], 1, diffuse, specular);

        DirectionalLight point_dirlight;
        point_dirlight.direction = Position - point_light[i].position;
        point_dirlight.color = point_light[i].color;
        point_dirlight.strength = point_light[i].strength;
        result += getDirectionalLight(point_dirlight, length(point_dirlight.direction), diffuse, specular);
    }

    FragColor = vec4(result, 1.0);
}
)glsl";

} // namespace TotoGL
