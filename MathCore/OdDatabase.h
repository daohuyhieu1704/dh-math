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

    class OdDatabase : public OdObjectBase
    {
    private:
        std::string m_name;
    protected:
        OdDataTableRecordPtr m_ObjectRecords;
    public:
		ODBASE_DECLARE_MEMBERS(OdDatabase);
        OdDatabase();
#pragma region Properties
        std::string GetName() const;
        void SetName(const std::string& name);
#pragma endregion

        virtual void ReRender(RenderEntityPtr renderTarget) = 0;
        virtual OdDatabasePtr CreateInstance() const = 0;
        void AppendObject(OdDrawablePtr obj);
        void SaveToJson(const std::string& filename);
        OdTransactionPtr TransactionManager;
    };

    typedef OdSmartPtr<OdDatabase> OdDatabasePtr;
}
