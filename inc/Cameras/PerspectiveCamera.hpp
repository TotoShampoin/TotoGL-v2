#pragma once
#include "Camera.hpp"
#include "Primitives/Primitives.hpp"

namespace TotoGL {

class PerspectiveCamera : public Camera {
public:
    PerspectiveCamera(
        const float &fov, const float &aspect, const float &near,
        const float &far);
    ~PerspectiveCamera() override = default;
    static std::shared_ptr<PerspectiveCamera> create(
        const float &fov, const float &aspect, const float &near,
        const float &far) {
        return std::make_shared<PerspectiveCamera>(fov, aspect, near, far);
    }

    Matrix4 projectionMatrix() const override { return _projection_matrix; }
    void updateProjectionMatrix();

    float &fov() { return _fov; }
    float &aspect() { return _aspect; }
    float &near() { return _near; }
    float &far() { return _far; }

    const float &fov() const { return _fov; }
    const float &aspect() const { return _aspect; }
    const float &near() const { return _near; }
    const float &far() const { return _far; }

private:
    float _fov, _aspect, _near, _far;
    Matrix4 _projection_matrix;
};

} // namespace TotoGL
