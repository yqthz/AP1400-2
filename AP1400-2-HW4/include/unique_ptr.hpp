template<typename T>
UniquePtr<T>::UniquePtr(T* n) : _p(n) { }


template<typename T>
UniquePtr<T>::UniquePtr() : _p(nullptr) { }

template<typename T>
UniquePtr<T>::~UniquePtr() {
    delete _p;
    _p = nullptr;
}

template<typename T>
T* UniquePtr<T>::get() const {
    return _p;
}

template<typename T>
T& UniquePtr<T>::operator*() const {
    return *_p;
}

template<typename T>
T* UniquePtr<T>::operator->() const {
    return _p;
}

template<typename T>
void UniquePtr<T>::reset() {
    delete _p;
    _p = nullptr;
}

template<typename T>
void UniquePtr<T>::reset(T* n) {
    if (n != _p) {
        delete _p;
        _p = n;
    }
}

template<typename T>
T* UniquePtr<T>::release() {
    T* t = _p;
    _p = nullptr;
    return t;
}

template<typename T>
UniquePtr<T>::operator bool() const {
    return _p != nullptr;
}