#include "Primitives/Object.hpp"
#include "Primitives/Rotation.hpp"
#include <algorithm>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/transform.hpp>

namespace TotoGL {

void Object::add(const std::shared_ptr<Object> &object) {
    _children.push_back(object);
}
void Object::remove(const std::shared_ptr<Object> &object) {
    _children.erase(std::remove(_children.begin(), _children.end(), object));
}
bool Object::contains(const std::shared_ptr<Object> &object) {
    return std::find(_children.begin(), _children.end(), object) !=
        _children.end();
}
void Object::clear() {
    _children.clear();
}

void Object::translate(const glm::vec3 &towards, const float &distance) {
    _position += glm::normalize(towards) * distance;
}
void Object::translateX(const float &distance) {
    _position.x += distance;
}
void Object::translateY(const float &distance) {
    _position.y += distance;
}
void Object::translateZ(const float &distance) {
    _position.z += distance;
}

void Object::rotate(const glm::vec3 &axis, const float &angle) {
    _rotation.rotate(axis, angle);
}
void Object::rotateX(const float &angle) {
    _rotation.rotateX(angle);
}
void Object::rotateY(const float &angle) {
    _rotation.rotateY(angle);
}
void Object::rotateZ(const float &angle) {
    _rotation.rotateZ(angle);
}

Matrix4 Object::matrix() const {
    return glm::translate(_position) * _rotation.matrix() * glm::scale(_scale);
}

void Object::lookAt(const Vector3 &target, const Vector3 &up) {
    _rotation =
        Euler::fromMatrix(glm::inverse(glm::lookAt(_position, target, up)));
}

} // namespace TotoGL
