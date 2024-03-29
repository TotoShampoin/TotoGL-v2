#include "Primitives/Clock.hpp"

#include <chrono>

namespace TotoGL {

Clock::Clock()
    : _start(std::chrono::system_clock::now()),
      _last_time(std::chrono::system_clock::now()) {
}

Seconds Clock::time() {
    _last_time = std::chrono::system_clock::now();
    auto difference = (_last_time - _start);
    return std::chrono::duration_cast<std::chrono::milliseconds>(difference);
}
Seconds Clock::delta_time() {
    auto time = std::chrono::system_clock::now();
    auto difference = time - _last_time;
    _last_time = time;
    return std::chrono::duration_cast<std::chrono::milliseconds>(difference);
}

} // namespace TotoGL
