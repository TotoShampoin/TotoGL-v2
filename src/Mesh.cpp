#include "Mesh.hpp"
#include "Materials/Material.hpp"
#include <memory>

namespace TotoGL {

Mesh::Mesh(
    const std::shared_ptr<Geometry> &geo, const std::shared_ptr<Material> &mat)
    : _geometry(geo), _material(mat) {
}

} // namespace TotoGL
