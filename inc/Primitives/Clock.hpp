#pragma once

#include <chrono>
#include <memory>

namespace TotoGL {

class Clock {
public:
    Clock();
    ~Clock() = default;
    static std::shared_ptr<Clock> create() {
        return std::make_shared<Clock>();
    }

    decltype(std::chrono::milliseconds()) time();
    decltype(std::chrono::milliseconds()) delta_time();

private:
    decltype(std::chrono::system_clock::now()) _start;
    decltype(std::chrono::system_clock::now()) _last_time;
};

} // namespace TotoGL
