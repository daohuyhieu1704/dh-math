#pragma once
#include "OdDrawable.h"
#include "nlohmann/json.hpp"

enum Visibility
{
    kInvisible = 1,
    kVisible = 0
};

class OdDbObject : public OdDrawable {
public:
    OdDbObject() : OdDrawable() {}
    virtual ~OdDbObject() = default;
    virtual nlohmann::json ToJson() const;
};

typedef OdSmartPtr<OdDbObject> OdDbObjectPtr;