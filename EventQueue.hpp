#pragma once

template <class T>
class EventQueue {
private:
    T queueHandle{nullptr}; 

public:
    explicit EventQueue(T handle);
    T operator*();
    bool receive(void* event, uint32_t ticksToWait);
};


#include "EventQueue.cpp"
