#pragma once
#include "OdBaseObjectPtr.h"
#include "OdError_NotThatKindOfClass.h"

/// <summary>
/// This template class provides the typified implementation of smart pointers for instances of classes derived from the OdObjectBase class.
/// remarks
/// SmartPointers relieve the programmer of having to determine when objects are no longer needed, or having to delete them at that time.
/// Each object referenced by a SmartPointer maintains a reference count; i.e., how many SmartPointers are referencing it.
/// When the reference count reaches zero, the referenced object is deleted.
/// </summary>
/// <typeparam name="T"></typeparam>
template <class T> class OdSmartPtr : public OdBaseObjectPtr
{
protected:
    /// <summary>
    /// Increments the reference counter of the referenced object.
    /// </summary>
    void internalAddRef()
    {
        if (m_pObject)
            m_pObject->addRef();
    }

    /// <summary>
    /// Assigns the pointer of specified object to the smart pointer.  
    /// 
    /// The reference counter of the specified object is incremented.
    /// If this SmartPointer is currently referencing another object, that object 
    /// is released prior to the assignment.
    /// </summary>
    /// <param name="pObject">Pointer to the specified object to be assigned</param>
    void assign(const T* pObject)
    {
        if (m_pObject != pObject) // Prevent deleting object if nRefs=1
        {
            release();
            m_pObject = const_cast<T*>(pObject);
            internalAddRef();
        }
    }

    /// <summary>
    /// Assigns the pointer of specified object to the smart pointer.  
    /// The reference counter of the specified object is incremented.
    /// If this SmartPointer is currently referencing another object, that object is released prior to the assignment.
    /// </summary>
    /// <param name="pObject">Pointer to the specified object to be assigned</param>
    void internalQueryX(const OdObjectBase* pObject)
    {
        if (pObject)
        {
            OdObjectBase* pX = pObject->queryX(T::desc());
            if (pX)
                m_pObject = pX;
            else
                throw OdError_NotThatKindOfClass(pObject->isA(), T::desc());
        }
    }

    /// <summary>
    /// Assigns the pointer of specified object to the smart pointer.
    /// </summary>
    /// <param name="pObject">Pointer to the specified object to be assigned</param>
    void assign(const OdObjectBase* pObject)
    {
        release();
        internalQueryX(pObject);
    }
public:

    /// <summary>
    /// Constructors for the typified smart pointer.
    /// 
    /// If pObject is specified, the smart pointer is set to the address of the specified object. If pObject is not specified, the smart pointer is set to a NULL.
    /// If const OdBaseObjectPtr& are specified, the reference counter of the specified object is not incremented
    /// </summary>
    OdSmartPtr()
        : OdBaseObjectPtr()
    {
    }

    /// <summary>
    /// Constructors for the typified smart pointer.
    /// </summary>
    /// <param name="pObject">Pointer to the object to be assigned to the new SmartPointer object</param>
    /// <param name=""></param>
    OdSmartPtr(const T* pObject)
        : OdBaseObjectPtr(pObject)
    {
        internalAddRef();
    }

    OdSmartPtr(const OdObjectBase* pObject)
        : OdBaseObjectPtr()
    {
        internalQueryX(pObject);
    }

    OdSmartPtr(const OdSmartPtr& pObject)
        : OdBaseObjectPtr(pObject.get())
    {
        internalAddRef();
    }

    OdSmartPtr(const OdPrObjectPtr& pObject)
        : OdBaseObjectPtr()
    {
        internalQueryX(pObject.get());
    }

    OdSmartPtr(const OdBaseObjectPtr& pObject)
        : OdBaseObjectPtr()
    {
        internalQueryX(pObject.get());
    }

    OdSmartPtr(OdSmartPtr&& pObject) noexcept : OdBaseObjectPtr(std::move(pObject))
    {}

    /// <summary>
    /// Assigns the pointer of the specifed object to the smart pointer without incrementing its reference counter.  
    /// 
    /// The reference counter of the specified object is not incremented.
    /// If the smart pointer is currently referencing to another object, that object is released prior to the assignment.
    /// </summary>
    /// <param name="pObject">Pointer to the specifed object to be assigned.</param>
    void attach(const T* pObject)
    {
        release();
        m_pObject = const_cast<T*>(pObject);
    }

    /// <summary>
    /// Assigns the pointer of the specifed object to the smart pointer without incrementing its reference counter. 
    /// The reference counter of the specified object is not incremented.
    /// If the smart pointer is currently referencing to another object, that object is released prior to the assignment.
    /// </summary>
    /// <param name="pObject">Pointer to the specifed object to be assigned</param>
    void attach(OdObjectBase* pObject)
    {
        release();
        internalQueryX(pObject);
        if (pObject)
            pObject->release();
    }

    /// <summary>
    /// Destructor for the typified smart pointer.
    /// Decrements the reference counter of the referenced object. When the reference count reaches zero, the referenced object is deleted.
    /// </summary>
    ~OdSmartPtr()
    {
        release();
    }

    /// <summary>
    /// Releases the smart pointer reference to the referenced object. 
    /// 
    /// Decrements the reference counter of the referenced object. When the reference count reaches zero, the referenced object is deleted.Smart pointer is set to a NULL.
    /// </summary>
    void release()
    {
        if (m_pObject)
        {
            m_pObject->release();
            m_pObject = 0;
        }
    }

    /// <summary>
    /// Releases the smart pointer reference to the referenced object without decrementing of the reference counter. 
    /// </summary>
    /// <returns>
    /// Returns the raw pointer to the referenced object. The reference counter is not modified 
    /// for the referenced object.Smart pointer is set to a NULL.
    /// </returns>
    T* detach()
    {
        T* pRes = static_cast<T*>(m_pObject);
        m_pObject = 0;
        return pRes;
    }

    /// <summary>
    /// The assignment operator increments the reference counter of the referenced object and saves its address in the smart pointer.
    /// If the smart pointer is currently referencing to another object, that assignment operator releases the referenced object prior
    /// to the assignment.
    /// </summary>
    /// <param name="pObject"></param>
    /// <returns></returns>
    OdSmartPtr& operator = (const OdSmartPtr& pObject)
    {
        assign(pObject);
        return *this;
    }

    OdSmartPtr& operator = (OdSmartPtr&& pObject) noexcept
    {
        OdBaseObjectPtr::operator=(std::move(pObject));
        return *this;
    }

    OdSmartPtr& operator = (const OdBaseObjectPtr& pObject)
    {
        assign(pObject.get());
        return *this;
    }

    OdSmartPtr& operator = (const T* pObject)
    {
        assign(pObject);
        return *this;
    }

    /// <summary>
    /// Returns the raw pointer to the referenced object.
    /// 
    /// The smart pointer maintains its reference to the referenced object. 
    /// The reference counter of the referenced object is not changed.
    /// </summary>
    /// <returns></returns>
    const T* get() const
    {
        return static_cast<const T*>(m_pObject);
    }

    /// <summary>
    /// Returns the raw pointer to the referenced object.
    /// 
    /// The smart pointer maintains its reference to the referenced object. 
    /// The reference counter of the referenced object is not changed.
    /// </summary>
    /// <returns></returns>
    T* get()
    {
        return static_cast<T*>(m_pObject);
    }

    /// <summary>
    /// Returns the raw pointer to the referenced object.
    /// </summary>
    /// <returns></returns>
    T* operator ->()
    {
        return static_cast<T*>(m_pObject);
    }
    
    /// <summary>
    /// Returns the raw pointer to the referenced object.
    /// The reference counter of the referenced object is not changed.
    /// </summary>
    /// <returns></returns>
    const T* operator ->() const
    {
        return static_cast<const T*>(m_pObject);
    }

    /// <summary>
    /// Returns the raw pointer the  referenced object.
    /// This SmartPointer maintains its reference to the referenced object.
    /// The reference counter of the referenced object is not changed.
    /// </summary>
    operator T* ()
    {
        return static_cast<T*>(m_pObject);
    }

    operator const T* () const
    {
        return static_cast<const T*>(m_pObject);
    }

    bool operator==(const void* pObject) const
    {
        return (m_pObject == pObject);
    }

    bool operator==(const OdSmartPtr& pObject) const
    {
        return operator==((void*)pObject.get());
    }

    bool operator!=(const void* pObject) const
    {
        return (m_pObject != pObject);
    }

    bool operator!=(const OdSmartPtr& pObject) const
    {
        return operator!=((void*)pObject.get());
    }

    /// <summary>
    /// Returns true if and only if the smart pointer stores a NULL.
    /// </summary>
    /// <returns></returns>
    bool operator !() const { return m_pObject == nullptr; }

    /// <summary>
    /// Returns true if and only if the smart pointer stores a non-null pointer.
    /// </summary>
    explicit operator bool() const { return m_pObject != nullptr; }
};
