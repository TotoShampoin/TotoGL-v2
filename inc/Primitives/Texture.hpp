#pragma once

#include "Primitives/Primitives.hpp"
#include <GL/gl.h>
#include <GL/glext.h>
#include <fstream>
#include <memory>
#include <tuple>
#include <variant>

namespace TotoGL {

class Texture {
public:
    enum class Wrapping {
        REPEAT = GL_REPEAT,
        MIRRORED_REPEAT = GL_MIRRORED_REPEAT,
        CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
        CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER
    };
    enum class Filtering { NEAREST = GL_NEAREST, LINEAR = GL_LINEAR };

    Texture(std::basic_ifstream<char> &&file) { load(file); }
    Texture(std::basic_ifstream<char> &file) { load(file); }
    ~Texture();
    static std::shared_ptr<Texture> create(std::basic_ifstream<char> &&file) {
        return std::make_shared<Texture>(file);
    }
    static std::shared_ptr<Texture> create(std::basic_ifstream<char> &file) {
        return std::make_shared<Texture>(file);
    }

    void update() const;

    const uint &textureId() const { return _texture_id; }
    const std::tuple<const int &, const int &> size() const {
        return { _width, _height };
    }
    const int &colorDepth() const { return _color_depth; }

    Filtering &minFilter() { return _filter_min; }
    Filtering &magFilter() { return _filter_mag; }
    Wrapping &xWrapping() { return _wrapping_horizontal; }
    Wrapping &yWrapping() { return _wrapping_vertical; }

    const Filtering &minFilter() const { return _filter_min; }
    const Filtering &magFilter() const { return _filter_mag; }
    const Wrapping &xWrapping() const { return _wrapping_horizontal; }
    const Wrapping &yWrapping() const { return _wrapping_vertical; }

private:
    uint _texture_id;
    int _width, _height, _color_depth;
    Filtering _filter_min{ Texture::Filtering::LINEAR };
    Filtering _filter_mag{ Texture::Filtering::LINEAR };
    Wrapping _wrapping_horizontal{ Texture::Wrapping::CLAMP_TO_EDGE };
    Wrapping _wrapping_vertical{ Texture::Wrapping::CLAMP_TO_EDGE };
    void load(std::basic_ifstream<char> &);
};
using TexturePtr = std::shared_ptr<Texture>;
using ColorVariant = std::variant<ColorRGB, TexturePtr>;

} // namespace TotoGL
