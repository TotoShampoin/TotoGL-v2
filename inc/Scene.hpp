#pragma once
#include "Primitives/Object.hpp"

namespace TotoGL {

class Scene : public Object {
public:
    ~Scene() override = default;
    static std::shared_ptr<Scene> create() { return std::make_shared<Scene>(); }

private:
};
using ScenePtr = std::shared_ptr<Scene>;

} // namespace TotoGL
