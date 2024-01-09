#pragma once

#include <functional>
#include <map>
#include <typeindex>

namespace TotoGL {

using CallbackHandle = std::size_t;

template <typename EventName, typename Event>
class EventManager {
    static_assert(!std::is_arithmetic<Event>::value, "Event cannot be a primitive type");
    using EventCallback = std::function<void(const Event*)>;
public:
    template <typename SpecificEvent>
    void touch(const EventName& name);
    void touch(const EventName& name);
    
    void remove(const EventName& name);

    template <typename SpecificEvent, typename = std::enable_if_t<std::is_base_of<Event, SpecificEvent>::value>>
    CallbackHandle on(const EventName&, const std::function<void(const SpecificEvent*)>&);
    CallbackHandle on(const EventName&, const std::function<void(const Event*)>&);
    
    void off(const EventName&, const CallbackHandle&);
    void off(const EventName&);
    
    template <typename SpecificEvent, typename = std::enable_if_t<std::is_base_of<Event, SpecificEvent>::value>>
    void emit(const EventName&, const SpecificEvent&);
    void emit(const EventName&, const Event&);

    EventManager();
    ~EventManager();
private:
    struct EventInfo {
        std::type_index type;
        std::map<CallbackHandle, EventCallback> callbacks {};
    };
    std::map<EventName, EventInfo> _events;
    CallbackHandle _handle {0};

    template <typename SpecificEvent>
    void _checkType(const EventName& name);
};

}

#include "EventManager.tpp"
