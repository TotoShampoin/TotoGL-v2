#pragma once

#include "Primitives/Primitives.hpp"
#include "Events/Event.hpp"

namespace TotoGL {

struct WindowCloseEvent : Event {
    WindowCloseEvent(EventName t)
        : Event(t) {}
};

struct WindowMinimizeEvent : Event {
    bool minimized;
    WindowMinimizeEvent(EventName t, int m)
        : Event(t), minimized(m) {}
};

struct WindowMaximizeEvent : Event {
    bool maximized;
    WindowMaximizeEvent(EventName t, int m)
        : Event(t), maximized(m) {}
};

struct WindowResizeEvent : Event {
    Vector2 size;
    WindowResizeEvent(EventName t, Vector2 s)
        : Event(t), size(std::move(s)) {}
};

struct MouseButtonEvent : Event {
    int button;
    bool action;
    int mod;

    MouseButtonEvent(EventName t, int b, int a, int m)
        : Event(t), button(b), action(a), mod(m) {}
};

struct MouseMoveEvent : Event {
    Vector2 position;
    Vector2 delta_position;

    MouseMoveEvent(EventName t, Vector2 p, Vector2 d)
        : Event(t), position(std::move(p)), delta_position(std::move(d)) {}
};

struct MouseScrollEvent : Event {
    Vector2 delta_scroll;

    MouseScrollEvent(EventName t, Vector2 d)
        : Event(t), delta_scroll(std::move(d)) {}
};

struct KeyboardEvent : Event {
    int key;
    int scancode;
    bool action;
    int mod;

    KeyboardEvent(EventName t, int k, int s, int a, int m)
        : Event(t), key(k), scancode(s), action(a), mod(m) {}
};

}
