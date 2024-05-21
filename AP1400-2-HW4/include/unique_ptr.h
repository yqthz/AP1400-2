#ifndef UNIQUE_PTR
#define UNIQUE_PTR
template<typename T>
class UniquePtr {
public:
    UniquePtr(T* n);
    UniquePtr();
    ~UniquePtr();
    UniquePtr(const UniquePtr& p) = delete;
    UniquePtr operator=(const UniquePtr& p) = delete;
    T* get() const;
    T& operator*() const;
    T* operator->() const;
    void reset();
    void reset(T* n);
    T* release();
    operator bool() const;
private:
    T* _p;
};

template<typename T>
T* make_unique(const T& n) {
    T* t = new T(n);
    return t;
}
#include"unique_ptr.hpp"


#endif //UNIQUE_PTR