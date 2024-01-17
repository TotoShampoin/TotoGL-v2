#include "Cameras/PerspectiveCamera.hpp"
#include <glm/ext/matrix_clip_space.hpp>

namespace TotoGL {

PerspectiveCamera::PerspectiveCamera(
    const float &fov, const float &aspect, const float &near, const float &far)
    : _fov(fov), _aspect(aspect), _near(near), _far(far),
      _projection_matrix(glm::perspective(fov, aspect, near, far)) {
}

void PerspectiveCamera::updateProjectionMatrix() {
    _projection_matrix = glm::perspective(_fov, _aspect, _near, _far);
}

} // namespace TotoGL
