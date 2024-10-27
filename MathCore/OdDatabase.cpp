#include "pch.h"
#include "OdDatabase.h"
#include "OdDataTableRecord.h"
#include "OdDbObject.h"
#include <fstream>

namespace DatabaseServices {

    OdDatabase::OdDatabase()
        : m_name(""), m_ObjectRecords(std::make_shared<OdDataTableRecord>()) {}

    std::string OdDatabase::GetName() const {
        return m_name;
    }

    void OdDatabase::SetName(const std::string& name) {
        m_name = name;
    }

    void OdDatabase::AppendObject(std::shared_ptr<OdObjectBase> obj) {
        m_ObjectRecords->AddObject(obj);
    }

    void OdDatabase::SaveToJson(const std::string& filename) {
        nlohmann::json json;
        for (const auto& record : m_ObjectRecords->GetObjects()) {
            OdDbObject* dbObj = dynamic_cast<OdDbObject*>(record.get());
            if (dbObj == nullptr) {
                continue;
            }
            json.push_back(dbObj->ToJson());
        }
        std::ofstream file(filename);
        file << json.dump(4);
    }
}
