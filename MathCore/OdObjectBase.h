#pragma once
#include <unordered_map>
#include <functional>
#include <memory>
#include <string>
#include "OdSmartPtr.h"

class OdObjectBase;
typedef OdSmartPtr<OdObjectBase> OdObjectBasePtr;

class OdObjectBase {
private:
    std::string m_objectId = "";
public:
    OdObjectBase() : m_objectId(GenerateShortId()) {}
    virtual ~OdObjectBase() {}

#pragma region Properties
    std::string GetObjectId() const;
#pragma endregion
    static std::string GenerateShortId();
    virtual OdObjectBasePtr Clone() const = 0;
};