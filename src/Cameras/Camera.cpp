#include "Cameras/Camera.hpp"
#include <glm/matrix.hpp>

namespace TotoGL {

Matrix4 Camera::matrixWorldInverse() const {
    return glm::inverse(matrix());
}
Matrix4 Camera::projectionMatrixInverse() const {
    return glm::inverse(projectionMatrix());
}

}
