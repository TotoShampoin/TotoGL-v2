#include "Primitives/Rotation.hpp"
#include "Primitives/Primitives.hpp"
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/transform.hpp>

namespace TotoGL {

void RotationMatrix::rotate(const Vector3 &axis, const float &angle) {
    _matrix = glm::rotate(angle, axis) * _matrix;
}

void Euler::rotate(const Vector3 &axis, const float &angle) {
    auto M = matrix();
    M = glm::rotate(angle, axis) * M;
    glm::extractEulerAngleXYZ(M, _angles.x, _angles.y, _angles.z);
}

Euler Euler::fromMatrix(const Matrix4 &matrix) {
    Euler euler;
    glm::extractEulerAngleXYZ(matrix, euler.x(), euler.y(), euler.z());
    return euler;
}

Matrix4 Euler::matrix() const {
    return glm::eulerAngleXYZ(_angles.x, _angles.y, _angles.z);
}

void Quaternion::rotate(const Vector3 &axis, const float &angle) {
    _quaternion = glm::rotate(_quaternion, angle, axis);
}

Matrix4 Quaternion::matrix() const {
    return glm::mat4_cast(_quaternion);
}

} // namespace TotoGL
