#pragma once

#include <memory>
#include <type_traits>
#include <vector>

#include "Primitives/Primitives.hpp"
#include "Primitives/Rotation.hpp"

namespace TotoGL {

class Object {
public:
    Object() = default;
    virtual ~Object() = default;
    static std::shared_ptr<Object> create() {
        return std::make_shared<Object>();
    }

    void add(const std::shared_ptr<Object> &);
    void remove(const std::shared_ptr<Object> &);

    // template <typename ...Objects>
    // void add(const Objects&... objects) { (add(objects), ...); }
    // template <typename ...Objects>
    // void remove(const Objects&... objects) { (add(objects), ...); }

    bool contains(const std::shared_ptr<Object> &);
    void clear();

    template <
        typename SubObject,
        typename = std::enable_if_t<std::is_base_of<Object, SubObject>::value>>
    static std::vector<std::shared_ptr<SubObject>>
    filter(const std::vector<std::shared_ptr<Object>> &);

    void translate(const Vector3 &, const float &);
    void translateX(const float &);
    void translateY(const float &);
    void translateZ(const float &);

    void rotate(const Vector3 &, const float &);
    void rotateX(const float &);
    void rotateY(const float &);
    void rotateZ(const float &);

    void lookAt(const Vector3 &target, const Vector3 &up = { 0, 1, 0 });

    Matrix4 matrix() const;

    const std::vector<std::shared_ptr<Object>> &children() const {
        return _children;
    }

    template <
        typename SubObject,
        typename = std::enable_if_t<std::is_base_of<Object, SubObject>::value>>
    std::vector<std::shared_ptr<SubObject>> children() const;

    const Vector3 &position() const { return _position; }
    const Vector3 &scale() const { return _scale; }
    const Euler &rotation() const { return _rotation; }

    Vector3 &position() { return _position; }
    Vector3 &scale() { return _scale; }
    Euler &rotation() { return _rotation; }

protected:
    const Matrix4 &matrixWorld() const { return _matrix_world; }
    virtual void updateMatrixWorld(const Matrix4 &parent) {
        _matrix_world = matrix() * parent;
    }

private:
    Vector3 _position{ 0 };
    Vector3 _scale{ 1 };
    Euler _rotation;

    Matrix4 _matrix_world;

    std::vector<std::shared_ptr<Object>> _children;
    friend class OpenGLRenderer;
};

} // namespace TotoGL

#include "Object.tpp"
