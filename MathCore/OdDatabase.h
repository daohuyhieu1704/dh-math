#pragma once

#include "OdObjectBase.h"
#include "OdDataTableRecord.h"
#include "OdTransaction.h" 
#include <memory>
#include <string>
#include <map>
#include <deque>
#include <nlohmann/json.hpp>

namespace DatabaseServices {
    typedef OdSmartPtr<class OdTransaction> OdTransactionPtr;
    typedef OdSmartPtr<class OdDatabase> OdDatabasePtr;
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
        void AppendObject(OdObjectBasePtr obj);
        void SaveToJson(const std::string& filename);
        OdTransactionPtr TransactionManager;
        OdObjectBasePtr Clone() const override;
    };
}
