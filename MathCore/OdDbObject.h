#pragma once
#include "OdDrawable.h"
#include "nlohmann/json.hpp"
#include "OdDbObjectId.h"

class OdDbObject : public OdDrawable {
public:
    ODBASE_DECLARE_MEMBERS(OdDbObject);
public:
    OdDbObject();
	~OdDbObject() = default;

    /// <summary>
	/// Returns the database data of this object.
    /// </summary>
    /// <returns></returns>
    virtual nlohmann::json ToJson() const;
};

typedef OdSmartPtr<OdDbObject> OdDbObjectPtr;

