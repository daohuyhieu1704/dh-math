#pragma once
#include <atomic>
#include <cstddef>
#include <utility>
#include <type_traits>

template <class T>
class OdSmartPtr {
    T* ptr;
    std::atomic<unsigned>* ref_count;

    OdSmartPtr(T* p, std::atomic<unsigned>* rc) : ptr(p), ref_count(rc) {
        if (ref_count) {
            ++(*ref_count);
        }
    }

public:
    OdSmartPtr() : ptr(nullptr), ref_count(nullptr) {}

    OdSmartPtr(const OdSmartPtr& sp) : ptr(sp.ptr), ref_count(sp.ref_count) {
        if (ref_count) {
            ++(*ref_count);
        }
    }

    OdSmartPtr(OdSmartPtr&& sp) noexcept : ptr(sp.ptr), ref_count(sp.ref_count) {
        sp.ptr = nullptr;
        sp.ref_count = nullptr;
    }

    template <class U>
    OdSmartPtr(const OdSmartPtr<U>& sp,
        typename std::enable_if<std::is_convertible<U*, T*>::value>::type* = 0)
        : ptr(sp.ptr), ref_count(sp.ref_count)
    {
        if (ref_count) {
            ++(*ref_count);
        }
    }

    template <class U>
    OdSmartPtr(OdSmartPtr<U>&& sp,
        typename std::enable_if<std::is_convertible<U*, T*>::value>::type* = 0)
        : ptr(sp.ptr), ref_count(sp.ref_count)
    {
        sp.ptr = nullptr;
        sp.ref_count = nullptr;
    }

    OdSmartPtr& operator=(const OdSmartPtr& sp) {
        if (this != &sp) {
            if (ref_count && --(*ref_count) == 0) {
                delete ptr;
                delete ref_count;
            }
            ptr = sp.ptr;
            ref_count = sp.ref_count;
            if (ref_count) {
                ++(*ref_count);
            }
        }
        return *this;
    }

    OdSmartPtr& operator=(OdSmartPtr&& sp) noexcept {
        if (this != &sp) {
            if (ref_count && --(*ref_count) == 0) {
                delete ptr;
                delete ref_count;
            }
            ptr = sp.ptr;
            ref_count = sp.ref_count;
            sp.ptr = nullptr;
            sp.ref_count = nullptr;
        }
        return *this;
    }

    template <class U>
    OdSmartPtr& operator=(const OdSmartPtr<U>& sp) {
        static_assert(std::is_convertible<U*, T*>::value, "Incompatible pointer types.");
        if (ptr != sp.ptr) {
            if (ref_count && --(*ref_count) == 0) {
                delete ptr;
                delete ref_count;
            }
            ptr = sp.ptr;
            ref_count = sp.ref_count;
            if (ref_count) {
                ++(*ref_count);
            }
        }
        return *this;
    }

    template <class U>
    OdSmartPtr& operator=(OdSmartPtr<U>&& sp) {
        static_assert(std::is_convertible<U*, T*>::value, "Incompatible pointer types.");
        if (ptr != sp.ptr) {
            if (ref_count && --(*ref_count) == 0) {
                delete ptr;
                delete ref_count;
            }
            ptr = sp.ptr;
            ref_count = sp.ref_count;
            sp.ptr = nullptr;
            sp.ref_count = nullptr;
        }
        return *this;
    }

    ~OdSmartPtr() {
        if (ref_count && --(*ref_count) == 0) {
            delete ptr;
            delete ref_count;
        }
    }

    T& operator*() const { return *ptr; }
    T* operator->() const { return ptr; }
    operator bool() const { return ptr != nullptr; }

    bool isNull() const { return ptr == nullptr; }

    template <class U>
    friend class OdSmartPtr;

    template <class T1, class U1>
    friend OdSmartPtr<T1> static_pointer_cast(const OdSmartPtr<U1>& sp);

    template <class T1, class U1>
    friend OdSmartPtr<T1> dynamic_pointer_cast(const OdSmartPtr<U1>& sp);

    template <class T1, class U1>
    friend OdSmartPtr<T1> const_pointer_cast(const OdSmartPtr<U1>& sp);

    template <class U>
    friend class ObjectFactory;
};

template <class T, class U>
OdSmartPtr<T> static_pointer_cast(const OdSmartPtr<U>& sp)
{
    static_assert(std::is_convertible<T*, U*>::value || std::is_convertible<U*, T*>::value, "Incompatible pointer types.");
    T* casted_ptr = static_cast<T*>(sp.ptr);
    return OdSmartPtr<T>(casted_ptr, sp.ref_count);
}

template <class T, class U>
OdSmartPtr<T> dynamic_pointer_cast(const OdSmartPtr<U>& sp)
{
    T* casted_ptr = dynamic_cast<T*>(sp.ptr);
    if (casted_ptr) {
        return OdSmartPtr<T>(casted_ptr, sp.ref_count);
    }
    else {
        return OdSmartPtr<T>(nullptr, nullptr);
    }
}

template <class T, class U>
OdSmartPtr<T> const_pointer_cast(const OdSmartPtr<U>& sp)
{
    T* casted_ptr = const_cast<T*>(sp.ptr);
    return OdSmartPtr<T>(casted_ptr, sp.ref_count);
}

template <class T>
class ObjectFactory {
    ObjectFactory() = delete;
    ObjectFactory(const ObjectFactory&) = delete;
    ObjectFactory& operator=(const ObjectFactory&) = delete;

public:
    template <typename... Args>
    static OdSmartPtr<T> createObject(Args&&... args) {
        T* raw_ptr = new T(std::forward<Args>(args)...);
        unsigned* ref_count = new unsigned(1);
        return OdSmartPtr<T>(raw_ptr, ref_count);
    }
};