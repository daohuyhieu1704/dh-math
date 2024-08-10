#include "pch.h"
#include "OdDataTableRecord.h"

std::vector<std::shared_ptr<OdObjectBase>> OdDataTableRecord::GetObjects() const
{
    std::vector<std::shared_ptr<OdObjectBase>> objects;
    for (const auto& pair : m_objects) {
        objects.push_back(std::shared_ptr<OdObjectBase>(pair.second.get()));
    }
    return objects;
}

void OdDataTableRecord::AddObject(std::shared_ptr<OdObjectBase> obj)
{
    std::string id = obj->GetObjectId();
    m_objects[id] = obj;
}

bool OdDataTableRecord::GetObjectById(const std::string& id, std::shared_ptr<OdObjectBase>& obj) {
    auto it = m_objects.find(id);
    if (it != m_objects.end()) {
        obj = std::shared_ptr<OdObjectBase>(it->second.get(), [](OdObjectBase*) {});
        return true;
    }
    return false;
}

nlohmann::json OdDataTableRecord::ToJson() const {
    nlohmann::json jsonArray = nlohmann::json::array();
    for (const auto& obj : m_objects) {
        OdDbObject* dbObj = dynamic_cast<OdDbObject*>(obj.second.get());
        if (dbObj == nullptr) {
            continue;
        }
        jsonArray.push_back(dbObj->ToJson());
    }
    return jsonArray;
}

OdObjectBase* OdDataTableRecord::Clone() const
{
    return nullptr;
}
