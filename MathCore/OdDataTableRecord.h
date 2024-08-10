#pragma once
#include "pch.h"
#include "OdDbObject.h"
#include <vector>

class OdDataTableRecord : public OdObjectBase {
private:
    std::map<std::string, std::shared_ptr<OdObjectBase>> m_objects;
public:
#pragma region Properties
    std::vector<std::shared_ptr<OdObjectBase>> GetObjects() const;
#pragma endregion

    void AddObject(std::shared_ptr<OdObjectBase> obj);

    bool GetObjectById(const std::string& id, std::shared_ptr<OdObjectBase>& obj);

    nlohmann::json ToJson() const;
    OdObjectBase* Clone() const override;
};

typedef std::shared_ptr<OdDataTableRecord> OdDataTableRecordPtr;