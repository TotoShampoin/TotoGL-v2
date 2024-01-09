#pragma once
#include "Primitives/Object.hpp"

namespace TotoGL {

class Group : public Object {
public:
    ~Group() override = default;
    static std::shared_ptr<Group> create() { return std::make_shared<Group>(); }
private:
};

}


