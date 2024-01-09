#pragma once
#include "EventManager.hpp"
#include <stdexcept>

namespace TotoGL {

template <typename EventName, typename Event>
EventManager<EventName, Event>::EventManager() {}

template <typename EventName, typename Event>
EventManager<EventName, Event>::~EventManager() {}

template <typename EventName, typename Event>
template <typename SpecificEvent>
void EventManager<EventName, Event>::touch(const EventName& name) {
    _events.emplace(name, EventInfo {
        .type = std::type_index(typeid(SpecificEvent))
    });
}

template <typename EventName, typename Event>
void EventManager<EventName, Event>::touch(const EventName& name) {
    _events.emplace(name, EventInfo {
        .type = std::type_index(typeid(Event))
    });
}

template <typename EventName, typename Event>
void EventManager<EventName, Event>::remove(const EventName& name) {
    _events.erase(name);
}

template <typename EventName, typename Event>
template <typename SpecificEvent>
void EventManager<EventName, Event>::_checkType(const EventName& name) {
    if(_events.find(name) == _events.end()) {
        throw std::runtime_error("Undefined event name");
    }
    if (_events.at(name).type != std::type_index(typeid(SpecificEvent))) {
        throw std::runtime_error("Wrong type of event: " + std::string(typeid(SpecificEvent).name()) + " (expected " + std::string(_events.at(name).type.name()) + ")");
    }
}

template <typename EventName, typename Event>
template <typename SpecificEvent, typename>
CallbackHandle EventManager<EventName, Event>::on(const EventName& name, const std::function<void(const SpecificEvent*)>& callback) {
    _checkType<SpecificEvent>(name);

    auto& event_callbacks = _events.at(name).callbacks;
    auto wrapper = [callback](const Event* event) {
        auto specific_event = dynamic_cast<const SpecificEvent*>(event);
        if (specific_event) {
            callback(specific_event);
        }
    };
    event_callbacks[_handle] = wrapper;
    return _handle++;
}

template <typename EventName, typename Event>
CallbackHandle EventManager<EventName, Event>::on(const EventName& name, const std::function<void(const Event*)>& callback) {
    _checkType<Event>(name);

    auto& event_callbacks = _events.at(name).callbacks;
    event_callbacks[_handle] = callback;
    return _handle++;
}

template <typename EventName, typename Event>
void EventManager<EventName, Event>::off(const EventName& name, const CallbackHandle& handle) {
    auto& event_callbacks = _events.at(name).callbacks;
    event_callbacks.erase(handle);
}

template <typename EventName, typename Event>
void EventManager<EventName, Event>::off(const EventName& name) {
    auto& event_callbacks = _events.at(name).callbacks;
    event_callbacks.clear();
}

template <typename EventName, typename Event>
template <typename SpecificEvent, typename>
void EventManager<EventName, Event>::emit(const EventName& name, const SpecificEvent& event) {
    _checkType<SpecificEvent>(name);

    auto& event_callbacks = _events.at(name).callbacks;
    for(const auto& [handle, callback] : event_callbacks) {
        callback(&event);
    }
}

template <typename EventName, typename Event>
void EventManager<EventName, Event>::emit(const EventName& name, const Event& event) {
    _checkType<Event>(name);

    auto& event_callbacks = _events.at(name).callbacks;
    for(const auto& [handle, callback] : event_callbacks) {
        callback(&event);
    }
}

}
