#pragma once

#include <glm/common.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/quaternion.hpp>

#include "Primitives.hpp"

namespace TotoGL {

class Rotation {
public:
    virtual ~Rotation() = default;
    virtual void rotate(const Vector3&, const float&) = 0;
    void rotateX(const float& angle) { rotate(Vector3(1, 0, 0), angle); };
    void rotateY(const float& angle) { rotate(Vector3(0, 1, 0), angle); };
    void rotateZ(const float& angle) { rotate(Vector3(0, 0, 1), angle); };
    virtual Matrix4 matrix() const = 0;
};

class RotationMatrix : public Rotation {
public:
    RotationMatrix() = default;
    ~RotationMatrix() override = default;
    void rotate(const Vector3&, const float&) override;
    Matrix4 matrix() const override { return _matrix; };
    Matrix4& matrix() { return _matrix; };
private:
    glm::mat4 _matrix {1};
};

class Euler : public Rotation {
public:
    Euler() = default;
    ~Euler() override = default;
    void rotate(const Vector3&, const float&) override;
    Matrix4 matrix() const override;

    static Euler fromMatrix(const Matrix4&);

    const Vector3& asVector() const { return _angles; }
    const float& x() const { return _angles.x; }
    const float& y() const { return _angles.y; }
    const float& z() const { return _angles.z; }


    Vector3& asVector() {
        x(); y(); z();
        return _angles;
    }

    float& x() {
        _angles.x = glm::mod(_angles.x + PI, 2.f * PI) - PI;
        return _angles.x;
    }
    float& y() {
        _angles.y = glm::mod(_angles.y + PI, 2.f * PI) - PI;
        return _angles.y;
    }
    float& z() {
        _angles.z = glm::mod(_angles.z + PI, 2.f * PI) - PI;
        return _angles.z;
    }
private:
    glm::vec3 _angles {0};
};

class Quaternion : public Rotation {
public:
    Quaternion() = default;
    ~Quaternion() override = default;
    void rotate(const Vector3&, const float&) override;
    Matrix4 matrix() const override;

    const float& x() const { return _quaternion.x; }
    const float& y() const { return _quaternion.y; }
    const float& z() const { return _quaternion.z; }
    const float& w() const { return _quaternion.w; }

    float& x() { return _quaternion.x; }
    float& y() { return _quaternion.y; }
    float& z() { return _quaternion.z; }
    float& w() { return _quaternion.w; }
private:
    glm::quat _quaternion;
};

}
