#include "Primitives/Texture.hpp"
#include <GL/gl.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <stdexcept>
#include <vector>

namespace TotoGL {

Texture::~Texture() {
    glDeleteTextures(1, &_texture_id);
}

void Texture::load(std::basic_ifstream<char>& file) {
    file.seekg(0, std::ios::end);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);
    if(size < 0) {
        throw std::runtime_error("Invalid file");
    }

    std::vector<char> buffer(size);
    if (!file.read(buffer.data(), size)) {
        throw std::runtime_error("Couldn't read file");
    }

    unsigned char* data = stbi_load_from_memory(
        reinterpret_cast<unsigned char*>(buffer.data()),
        size, &_width, &_height, &_color_depth, 0);
    if (!data) {
        throw std::runtime_error("Couldn't load image from file");
    }

    int gl_depth;
    switch (_color_depth) {
        case 1: gl_depth = GL_R; break;
        case 2: gl_depth = GL_RG; break;
        case 3: gl_depth = GL_RGB; break;
        case 4: gl_depth = GL_RGBA; break;
    }

    glGenTextures(1, &_texture_id);
    glBindTexture(GL_TEXTURE_2D, _texture_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, gl_depth, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<GLenum>(_filter_min));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<GLenum>(_filter_mag));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, static_cast<GLenum>(_wrapping_horizontal));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, static_cast<GLenum>(_wrapping_vertical));
    glBindTexture(GL_TEXTURE_2D, GL_NONE);

    stbi_image_free(data);
}

}
