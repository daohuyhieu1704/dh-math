#pragma once
#include "pch.h"
#include "OdDbObject.h"
#include <vector>

class OdDataTableRecord : public OdObjectBase {
private:
    std::map<OdDbObjectId, OdDrawablePtr> m_objects;
public:
	ODBASE_DECLARE_MEMBERS(OdDataTableRecord);
	virtual ~OdDataTableRecord() = default;
#pragma region Properties
    std::vector<OdDrawablePtr> GetObjects() const;
#pragma endregion
    void AddObject(OdDrawablePtr obj);
    bool GetObjectById(const OdDbObjectId& id, OdDrawablePtr obj);
    nlohmann::json ToJson() const;

    // Inherited via OdObjectBase
    void addRef() override;
    void release() override;
};

typedef OdSmartPtr<OdDataTableRecord> OdDataTableRecordPtr;