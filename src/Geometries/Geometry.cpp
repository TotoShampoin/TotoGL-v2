#include "Primitives/Geometry.hpp"
#include "Primitives/Vertex.hpp"
#include <GL/glew.h>
#include <algorithm>
#include <numeric>
#include <optional>
#include <vector>

namespace TotoGL {

Geometry::Geometry() {
    allocate();
    update();
}

Geometry::Geometry(const std::vector<Vertex>& verts, const std::vector<Triangle>& tris, const std::vector<size_t>& mats)
    : _vertices(verts), _triangles(tris), _materials(mats)
{
    allocate();
    update();
}

Geometry::~Geometry() {
    glDeleteBuffers(1, &_ebo);
    glDeleteBuffers(1, &_vbo);
    glDeleteVertexArrays(1, &_vao);
}

void Geometry::allocate() {
    glGenVertexArrays(1, &_vao);
    glGenBuffers(1, &_vbo);
    glGenBuffers(1, &_ebo);

    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);

    glEnableVertexAttribArray(0); // position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(1); // normal
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Vertex::position)));
    glEnableVertexAttribArray(2); // uv
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Vertex::position) + sizeof(Vertex::normal)));
    glEnableVertexAttribArray(3); // color
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Vertex::position) + sizeof(Vertex::normal) + sizeof(Vertex::uv)));

    glBindVertexArray(0);
}

void Geometry::update() {
    sortTriangles();
    fillSubgeometries();
    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(Vertex), &_vertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _triangles.size() * sizeof(Triangle), &_triangles[0], GL_STATIC_DRAW);
    glBindVertexArray(0);
}

void Geometry::draw(const std::optional<size_t>& material_index) {
    if(!material_index.has_value()) {
        glBindVertexArray(_vao);
        glDrawElements(GL_TRIANGLES, _triangles.size() * 3, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        return;
    }
    size_t index = *material_index;
    if(index >= _subgeometries.size()) {
        index = 0;
    }
    glBindVertexArray(_vao);
    auto [start, count] = _subgeometries[index];
    glDrawElements(GL_TRIANGLES, count * 3, GL_UNSIGNED_INT, (void*)(start * sizeof(Triangle)));
    glBindVertexArray(0);
}

void Geometry::sortTriangles() {
    if(_materials.size() == 0) return;
    std::vector<size_t> indices(_triangles.size());
    std::iota(indices.begin(), indices.end(), 0);

    std::sort(indices.begin(), indices.end(),
        [this](size_t a, size_t b) {
            return _materials[a] < _materials[b];
        });
    _sorted_materials = _materials;
    std::sort(_sorted_materials.begin(), _sorted_materials.end(),
        [](size_t a, size_t b) {
            return a < b;
        });
    _sorted_triangles.clear();
    for (size_t i : indices) {
        _sorted_triangles.push_back(_triangles[i]);
    }
}
void Geometry::fillSubgeometries() {
    if(_sorted_materials.size() == 0) return;
    _subgeometries.clear();
    size_t current_material = _sorted_materials[0];
    size_t start = 0;
    for (size_t i = 1; i < _sorted_materials.size(); ++i) {
        if (_sorted_materials[i] != current_material) {
            _subgeometries.push_back({start, i - start});
            start = i;
            current_material = _sorted_materials[i];
        }
    }
    _subgeometries.push_back({start, _sorted_triangles.size() - start});
}

}
