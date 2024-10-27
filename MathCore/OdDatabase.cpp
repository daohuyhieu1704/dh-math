#include "pch.h"
#include "OdDatabase.h"
#include "OdDataTableRecord.h"
#include "OdDbObject.h"
#include <fstream>

namespace DatabaseServices {

    ODBASE_DEFINE_RTTI_MEMBERS_GENERIC(OdDatabase, OdDatabase, OdObjectBase)
    std::string OdDatabase::GetName() const {
        return m_name;
    }

    void OdDatabase::SetName(const std::string& name) {
        m_name = name;
    }

    void OdDatabase::AppendObject(OdDrawablePtr obj) {
        m_ObjectRecords->AddObject(obj);
    }

    void OdDatabase::SaveToJson(const std::string& filename) {
        nlohmann::json json;
        for (const auto& record : m_ObjectRecords->GetObjects()) {
            OdDbObjectPtr dbObj = OdDbObject::cast(record.get());
            if (dbObj.isNull()) continue;
            json.push_back(dbObj->ToJson());
        }
        std::ofstream file(filename);
        file << json.dump(4);
    }
}
