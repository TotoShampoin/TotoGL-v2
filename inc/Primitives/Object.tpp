#pragma once
#include "Object.hpp"
#include <memory>
#include <vector>

namespace TotoGL {

template <typename SubObject, typename>
std::vector<std::shared_ptr<SubObject>>
Object::filter(const std::vector<std::shared_ptr<Object>> &objects) {
    std::vector<std::shared_ptr<SubObject>> result;
    for (const auto &object : objects) {
        if (const auto &object_cast =
                std::dynamic_pointer_cast<SubObject>(object)) {
            result.push_back(object_cast);
        }
    }
    return result;
}

template <typename SubObject, typename>
std::vector<std::shared_ptr<SubObject>> Object::children() const {
    std::vector<std::shared_ptr<SubObject>> sub_children;
    for (const auto &child : _children) {
        const auto &child_cast = std::dynamic_pointer_cast<SubObject>(child);
        if (child_cast) {
            sub_children.push_back(child_cast);
        }
    }
    return sub_children;
}

} // namespace TotoGL
