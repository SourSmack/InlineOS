#pragma once
#include "EventQueue.hpp"

template <class T>
EventQueue<T>::EventQueue(T handle) {
    if (handle) {
        queueHandle = handle;
    }
}

template <class T>
T EventQueue<T>::operator*() {
    return queueHandle;
}

template <class T>
bool EventQueue<T>::receive(void* event, uint32_t ticksToWait) {
    return xQueueReceive(queueHandle, event, ticksToWait) == pdPASS;
}
