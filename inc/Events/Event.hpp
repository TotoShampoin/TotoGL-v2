#pragma once

namespace TotoGL {

enum class EventName {
    WINDOW_RESIZE,
    WINDOW_CLOSE,
    WINDOW_MINIMIZE,
    WINDOW_MAXIMIZE,
    MOUSE_UP,
    MOUSE_DOWN,
    MOUSE_MOVE,
    MOUSE_SCROLL,
    KEY_UP,
    KEY_DOWN
};
struct Event {
    EventName type;
    Event(EventName t) : type(t) {}
    virtual ~Event() = default;
};

} // namespace TotoGL
