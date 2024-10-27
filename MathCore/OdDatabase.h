#pragma once

#include "ObjectBase.h"
#include "OdDataTableRecord.h"
#include "OdTransaction.h" 
#include <memory>
#include <string>
#include <map>
#include <deque>
#include <nlohmann/json.hpp>

namespace DatabaseServices {
    typedef std::shared_ptr<class OdDatabase> OdDatabasePtr;

    class OdDatabase : public OdObjectBase
    {
    private:
        std::string m_name;
    protected:
        OdDataTableRecordPtr m_ObjectRecords;
    public:
        OdDatabase();
#pragma region Properties
        std::string GetName() const;
        void SetName(const std::string& name);
#pragma endregion

        virtual void ReRender(void* renderTarget) = 0;
        virtual OdDatabasePtr CreateInstance() const = 0;
        void AppendObject(std::shared_ptr<OdObjectBase> obj);
        void SaveToJson(const std::string& filename);
        OdTransactionPtr TransactionManager;
    };
}
