template<
    class T ,
    class Self,
    bool (*TransportData)(Self&),
    bool (*DestinationAvailable)(Self&),
    bool (*SourceAvailable)(Self&)
>
Courier<T, Self, TransportData, DestinationAvailable, SourceAvailable>::Courier(Mission<T> &p_task)
    : task(p_task) 
    { }

template<
    class T ,
    class Self,
    bool (*TransportData)(Self&),
    bool (*DestinationAvailable)(Self&),
    bool (*SourceAvailable)(Self&)
>
void Courier<T, Self, TransportData, DestinationAvailable, SourceAvailable>::transfer(void * context) {
    auto& self = *static_cast<Self*>(context);

    while (!Mission<T>::waitForNotify(Mission<T>::event.stop, 0)) {
        if (Mission<T>::waitForNotify(Mission<T>::event.pause, 0)) {
            while (!Mission<T>::waitForNotify(Mission<T>::event.resume, Mission<T>::MAX_DELAY)) {}
        }

        if constexpr (SourceAvailable != nullptr) {
            while (!SourceAvailable(self)) {
                Mission<T>::notify(sourceExhaustion);
                while (!Mission<T>::waitForNotify(Mission<T>::event.resume, Mission<T>::MAX_DELAY)) {}
            }
        }

        if constexpr (DestinationAvailable != nullptr) {
            while (!DestinationAvailable(self)) {
                Mission<T>::notify(destinationExhaustion);
                while (!Mission<T>::waitForNotify(Mission<T>::event.resume, Mission<T>::MAX_DELAY)) {}
            }
        }

        if constexpr (TransportData != nullptr) {
            if (!TransportData(self)) {
                Mission<T>::notify(transferExhaustion);
                while (!Mission<T>::waitForNotify(Mission<T>::event.resume, Mission<T>::MAX_DELAY)) {}
            }
        }
    }
}

template<
    class T ,
    class Self,
    bool (*TransportData)(Self&),
    bool (*DestinationAvailable)(Self&),
    bool (*SourceAvailable)(Self&)
>
bool Courier<T, Self, TransportData, DestinationAvailable, SourceAvailable>::pauseTransfer() {
    return false;
}

template<
    class T ,
    class Self,
    bool (*TransportData)(Self&),
    bool (*DestinationAvailable)(Self&),
    bool (*SourceAvailable)(Self&)
>
bool Courier<T, Self, TransportData, DestinationAvailable, SourceAvailable>::stopTransfer() {
    return false;
}

template<
    class T ,
    class Self,
    bool (*TransportData)(Self&),
    bool (*DestinationAvailable)(Self&),
    bool (*SourceAvailable)(Self&)
>
bool Courier<T, Self, TransportData, DestinationAvailable, SourceAvailable>::startTransfer() {
    return false;
}

template<
    class T ,
    class Self,
    bool (*TransportData)(Self&),
    bool (*DestinationAvailable)(Self&),
    bool (*SourceAvailable)(Self&)
>
uint32_t Courier<T, Self, TransportData, DestinationAvailable, SourceAvailable>::verifyStatus(uint32_t status) {
    if (status) {
        return Mission<T>::waitForNotify(status, 0);
    }
    return Mission<T>::checkOnFlags();
}
