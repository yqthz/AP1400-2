#ifndef SHARED_PTR
#define SHARED_PTR
template<typename T>
class SharedPtr {
public:
    SharedPtr(T* n);
    SharedPtr();
    ~SharedPtr();
    SharedPtr(SharedPtr& p);
    SharedPtr<T>& operator=(SharedPtr& p);
    size_t use_count() const;
    T* get() const;
    T& operator*() const;
    T* operator->() const;
    void reset();
    void reset(T* n);
    operator bool() const;
private:
    T* _p;
    size_t* count;
};

template<typename T>
T* make_shared(const T& n) {
    T* t = new T(n);
    return t;
}

#include"shared_ptr.hpp"

#endif //SHARED_PTR