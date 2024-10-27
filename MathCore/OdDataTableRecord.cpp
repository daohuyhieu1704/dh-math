#include "pch.h"
#include "OdDataTableRecord.h"

std::vector<OdDrawablePtr> OdDataTableRecord::GetObjects() const
{
    std::vector<OdDrawablePtr> objects;
    //for (const auto& pair : m_objects) {
    //    objects.push_back(pair.second);
    //}
    return objects;
}

void OdDataTableRecord::AddObject(OdDrawablePtr obj)
{
    // m_objects[obj->objectId()] = obj;
}

bool OdDataTableRecord::GetObjectById(const OdDbObjectId& id, OdDrawablePtr obj) {
    //auto it = m_objects.find(id);
    //if (it != m_objects.end()) {
    //    obj = it->second;
    //    return true;
    //}
    return false;
}

nlohmann::json OdDataTableRecord::ToJson() const {
    nlohmann::json jsonArray = nlohmann::json::array();
    //for (const auto& obj : m_objects) {
    //    OdDbObjectPtr dbObj = OdDbObject::cast(obj.second.get());
    //    if (dbObj.isNull()) continue;
    //    jsonArray.push_back(dbObj->ToJson());
    //}
    return jsonArray;
}

void OdDataTableRecord::addRef()
{

}

void OdDataTableRecord::release()
{
}
