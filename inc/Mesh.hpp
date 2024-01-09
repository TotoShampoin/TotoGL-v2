#pragma once

#include <memory>
#include <vector>
#include "Primitives/Object.hpp"
#include "Primitives/Geometry.hpp"
#include "Materials/Material.hpp"
#include "Primitives/Vertex.hpp"

namespace TotoGL {

class Mesh : public Object {
public:
    Mesh(const std::shared_ptr<Geometry>& geo, const std::shared_ptr<Material>& mat);
    ~Mesh() override = default;
    static std::shared_ptr<Mesh> create(const std::shared_ptr<Geometry>& geo, const std::shared_ptr<Material>& mat) {
        return std::make_shared<Mesh>(geo, mat);
    }

    std::vector<Vertex> vertices() { return _geometry->vertices(); }
    const std::shared_ptr<Material>& material() const { return _material; }
    std::shared_ptr<Geometry>& geometry() { return _geometry; }
private:
    std::shared_ptr<Geometry> _geometry;
    std::shared_ptr<Material> _material;
};

}


