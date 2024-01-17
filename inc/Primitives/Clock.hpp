#pragma once

#include <chrono>
#include <memory>

namespace TotoGL {

using Seconds = std::chrono::duration<float>;

class Clock {
public:
    Clock();
    ~Clock() = default;
    static std::shared_ptr<Clock> create() {
        return std::make_shared<Clock>();
    }

    Seconds time();
    Seconds delta_time();

private:
    decltype(std::chrono::system_clock::now()) _start;
    decltype(std::chrono::system_clock::now()) _last_time;
};

} // namespace TotoGL
