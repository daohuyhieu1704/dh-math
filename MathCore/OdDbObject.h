#pragma once
#include "OdDrawable.h"
#include "nlohmann/json.hpp"
#include "OdDbObjectId.h"

class OdDbObject : public OdDrawable {
public:
    ODBASE_DECLARE_MEMBERS(OdDbObject);
protected:
    OdDbObject() : OdDrawable() {}
public:
	~OdDbObject() = default;

    /// <summary>
    /// Increments the reference count of this object.
    /// </summary>
    void addRef();

    /// <summary>
    /// Decrements the reference count of this object.
    /// This object is deleted when the reference count reaches zero.
    /// </summary>
    void release();

    /// <summary>
    /// Returns the reference count of this object.
    /// </summary>
    /// <returns></returns>
    long numRefs() const;

    /// <summary>
	/// Returns the database data of this object.
    /// </summary>
    /// <returns></returns>
    virtual nlohmann::json ToJson() const;
};

typedef OdSmartPtr<OdDbObject> OdDbObjectPtr;

