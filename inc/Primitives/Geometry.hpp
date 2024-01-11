#pragma once

#include "Primitives/Vertex.hpp"
#include <cstddef>
#include <memory>
#include <optional>
#include <vector>

namespace TotoGL {
struct Triangle {
    uint v1, v2, v3;
};

class Geometry {
public:
    Geometry();
    Geometry(
        const std::vector<Vertex> &verts, const std::vector<Triangle> &tris,
        const std::vector<size_t> &mats = {});
    ~Geometry();
    static std::shared_ptr<Geometry> create(
        const std::vector<Vertex> &verts, const std::vector<Triangle> &tris,
        const std::vector<size_t> &mats = {}) {
        return std::make_shared<Geometry>(verts, tris, mats);
    }

    const std::vector<Vertex> &vertices() const { return _vertices; }
    std::vector<Vertex> &vertices() { return _vertices; }
    const std::vector<Triangle> &triangles() const { return _triangles; }
    std::vector<Triangle> &triangles() { return _triangles; }
    const std::vector<size_t> &materials() const { return _materials; }
    std::vector<size_t> &materials() { return _materials; }

    void update();

private:
    struct SubGeometry {
        size_t start;
        size_t count;
    };
    std::vector<Vertex> _vertices;
    std::vector<Triangle> _triangles;
    std::vector<size_t> _materials;

    std::vector<Triangle> _sorted_triangles;
    std::vector<size_t> _sorted_materials;
    std::vector<SubGeometry> _subgeometries;

    uint _vbo, _vao, _ebo;

    // void draw();
    void allocate();
    void draw(const std::optional<size_t> & = std::nullopt);
    void sortTriangles();
    void fillSubgeometries();
    friend class OpenGLRenderer;
    friend class GL3Renderer;
};
using GeometryPtr = std::shared_ptr<Geometry>;

struct PlaneGeometry : Geometry {
    PlaneGeometry(const float &width = 1, const float &height = 1);
    static std::shared_ptr<PlaneGeometry>
    create(const float &width = 1, const float &height = 1) {
        return std::make_shared<PlaneGeometry>(width, height);
    }
};
struct BoxGeometry : Geometry {
    BoxGeometry(
        const float &width = 1, const float &height = 1,
        const float &depth = 1);
    static std::shared_ptr<BoxGeometry> create(
        const float &width = 1, const float &height = 1,
        const float &depth = 1) {
        return std::make_shared<BoxGeometry>(width, height, depth);
    }
};
struct SphereGeometry : Geometry {
    SphereGeometry(
        const float &radius = 1, const int &width_segments = 32,
        const int &height_segments = 16);
    static std::shared_ptr<SphereGeometry> create(
        const float &radius = 1, const int &width_segments = 32,
        const int &height_segments = 16) {
        return std::make_shared<SphereGeometry>(
            radius, width_segments, height_segments);
    }
};
struct CylinderGeometry : Geometry {
    CylinderGeometry(
        const float &radius_top = 1, const float &radius_bottom = 1,
        const float &height = 1, const int &radial_segments = 32,
        const int &height_segments = 1, const bool &open_ended = false);
    static std::shared_ptr<CylinderGeometry> create(
        const float &radius_top = 1, const float &radius_bottom = 1,
        const float &height = 1, const int &radial_segments = 32,
        const int &height_segments = 1, const bool &open_ended = false) {
        return std::make_shared<CylinderGeometry>(
            radius_top, radius_bottom, height, radial_segments, height_segments,
            open_ended);
    }
};

struct CapsuleGeometry : Geometry {
    CapsuleGeometry();
    static std::shared_ptr<CapsuleGeometry> create() {
        return std::make_shared<CapsuleGeometry>();
    }
};
struct ConeGeometry : Geometry {
    ConeGeometry();
    static std::shared_ptr<ConeGeometry> create() {
        return std::make_shared<ConeGeometry>();
    }
};
struct DodecahedronGeometry : Geometry {
    DodecahedronGeometry();
    static std::shared_ptr<DodecahedronGeometry> create() {
        return std::make_shared<DodecahedronGeometry>();
    }
};
struct IcosahedronGeometry : Geometry {
    IcosahedronGeometry();
    static std::shared_ptr<IcosahedronGeometry> create() {
        return std::make_shared<IcosahedronGeometry>();
    }
};
struct TorusGeometry : Geometry {
    TorusGeometry();
    static std::shared_ptr<TorusGeometry> create() {
        return std::make_shared<TorusGeometry>();
    }
};

// std::shared_ptr<Geometry> PlaneGeometry(const float& width = 1, const float&
// height = 1); std::shared_ptr<Geometry> BoxGeometry(const float& width = 1,
// const float& height = 1, const float& depth = 1); std::shared_ptr<Geometry>
// SphereGeometry(const float& radius = 1, const int& width_segments = 32, const
// int& height_segments = 16); std::shared_ptr<Geometry> CylinderGeometry(
//     const float& radius_top = 1, const float& radius_bottom = 1, const float&
//     height = 1, const int& radial_segments = 32, const int& height_segments =
//     1, const bool& open_ended = false);
// std::shared_ptr<Geometry> CapsuleGeometry();
// std::shared_ptr<Geometry> ConeGeometry();
// std::shared_ptr<Geometry> DodecahedronGeometry();
// std::shared_ptr<Geometry> IcosahedronGeometry();
// std::shared_ptr<Geometry> TorusGeometry();

} // namespace TotoGL
