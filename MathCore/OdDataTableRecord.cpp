#include "pch.h"
#include "OdDataTableRecord.h"

std::vector<OdObjectBasePtr> OdDataTableRecord::GetObjects() const
{
    std::vector<OdObjectBasePtr> objects;
    for (const auto& pair : m_objects) {
        objects.push_back(OdObjectBasePtr(pair.second));
    }
    return objects;
}

void OdDataTableRecord::AddObject(OdObjectBasePtr obj)
{
    std::string id = obj->GetObjectId();
    m_objects[id] = obj;
}

bool OdDataTableRecord::GetObjectById(const std::string& id, OdObjectBasePtr obj) {
    auto it = m_objects.find(id);
    if (it != m_objects.end()) {
        obj = OdObjectBasePtr(it->second);
        return true;
    }
    return false;
}

nlohmann::json OdDataTableRecord::ToJson() const {
    nlohmann::json jsonArray = nlohmann::json::array();
    for (const auto& obj : m_objects) {
        OdDbObjectPtr dbObj = dynamic_pointer_cast<OdDbObject, OdObjectBase>(obj.second);
        if (dbObj) continue;
        jsonArray.push_back(dbObj->ToJson());
    }
    return jsonArray;
}

OdObjectBasePtr OdDataTableRecord::Clone() const
{
    return nullptr;
}
