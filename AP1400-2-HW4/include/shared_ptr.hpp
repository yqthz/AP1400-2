template<typename T>
SharedPtr<T>::SharedPtr(T* n) : _p(n), count(new size_t(1)) { }

template<typename T>
SharedPtr<T>::SharedPtr() : _p(nullptr), count(new size_t(0)) { }

template<typename T>
SharedPtr<T>::~SharedPtr() {
    if (_p != nullptr && count != nullptr && *count == 1) {
        delete _p;
        delete count;
        _p = nullptr;
        count = nullptr;
    }
    else if (count != nullptr){
        *count -= 1;
    }

}

template<typename T>
SharedPtr<T>::SharedPtr(SharedPtr& p) : _p(p.get()) { 
    (*p.count) += 1;
    this->count = p.count;
}


template<typename T>
SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr& p) {
    if (this == &p) {
        return *this;
    }
    *(this->count) -= 1;
    if (*(this->count) == 0) {
        delete this->_p;
        delete this->count;
        this->_p = nullptr;
        this->count = nullptr;
    }
    _p = p._p;
    *(p.count) += 1;
    count = p.count;
    return *this;
}

template<typename T>
size_t SharedPtr<T>::use_count() const {
    if (count == nullptr) {
        return 0;
    }
    return *count;
}

template<typename T>
T* SharedPtr<T>::get() const {
    return _p;
}

template<typename T>
T& SharedPtr<T>::operator*() const {
    return *_p;
}

template<typename T>
T* SharedPtr<T>::operator->() const {
    return _p;
}

template<typename T>
void SharedPtr<T>::reset() {
    delete _p;
    delete count;
    _p = nullptr;
    count = nullptr;
}

template<typename T>
void SharedPtr<T>::reset(T* n) {
    delete _p;
    _p = n;
    *count = 1;
}

template<typename T>
SharedPtr<T>::operator bool() const {
    return _p != nullptr;
}