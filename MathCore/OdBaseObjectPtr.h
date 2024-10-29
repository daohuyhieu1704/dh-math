#pragma once
#include "pch.h"
#include <utility>

class OdObjectBase;

/// <summary>
/// **Smart Pointer Base Class**
/// Simplifies memory management by automatically tracking and releasing referenced objects.
/// Key Features:
/// * **Reference Counting:** Maintains a count of active references.
/// * **Automatic Memory Management:** Releases objects when no longer needed.
/// </summary>
class OdBaseObjectPtr
{
protected:
    OdObjectBase* m_pObject = nullptr;

    OdBaseObjectPtr() : m_pObject(0) {}
    explicit OdBaseObjectPtr(const OdObjectBase* pSource) : m_pObject(const_cast<OdObjectBase*>(pSource)) {}

    OdBaseObjectPtr(OdBaseObjectPtr&& pObject) noexcept : m_pObject(pObject.m_pObject)
    {
        pObject.m_pObject = nullptr;
    }

    OdBaseObjectPtr& operator = (OdBaseObjectPtr&& pObject) noexcept
    {
        std::swap(m_pObject, pObject.m_pObject);
        return *this;
    }
public:
    /** \details
      Returns the raw pointer to the referenced object.
      \remarks
      This class maintains the reference to the referenced object.
      The reference counter of the referenced object is not changed.
    */
    OdObjectBase* get() const { return m_pObject; }
    bool isNull() const { return m_pObject == 0; }
};