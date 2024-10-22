#pragma once
#include "pch.h"
#include "OdDbObject.h"
#include <vector>

class OdDataTableRecord : public OdObjectBase {
private:
    std::map<std::string, OdObjectBasePtr> m_objects;
public:
#pragma region Properties
    std::vector<OdObjectBasePtr> GetObjects() const;
#pragma endregion

    void AddObject(OdObjectBasePtr obj);

    bool GetObjectById(const std::string& id, OdObjectBasePtr obj);

    nlohmann::json ToJson() const;
    OdObjectBasePtr Clone() const override;
};

typedef std::shared_ptr<OdDataTableRecord> OdDataTableRecordPtr;