#pragma once
#include "OdDrawable.h"
#include "json.hpp"

class OdDbObject : public OdDrawable {
public:
    OdDbObject() : OdDrawable() {}
    virtual ~OdDbObject() = default;
    virtual nlohmann::json ToJson() const;
};


