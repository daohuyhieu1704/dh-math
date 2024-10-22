#pragma once

#include "OdObjectBase.h"
#include <map>
#include <deque>
#include <memory>
#include <stdexcept>

namespace DatabaseServices {

    typedef OdSmartPtr<class OdDatabase> OdDatabasePtr;

    class OdTransaction : public OdObjectBase
    {
    protected:
        bool m_transactionActive;
        OdDatabasePtr m_Doc;
        std::map<std::string, std::shared_ptr<OdObjectBase>> m_newlyAddedObjects;
        bool m_isUndoRedoInProgress;
        std::deque<std::shared_ptr<OdObjectBase>> m_undoneObjects;

    public:
        OdTransaction() : OdObjectBase(), m_transactionActive(false), m_Doc(nullptr), m_renderTarget(nullptr), m_isUndoRedoInProgress(false) {}
        OdTransaction(OdDatabasePtr parentDoc)
            : OdObjectBase(), m_transactionActive(false), m_Doc(parentDoc), m_renderTarget(nullptr), m_isUndoRedoInProgress(false) {}

        void StartTransaction();
        void AddNewlyObject(OdObjectBasePtr obj);
        void Abort();
        void Commit();
        virtual ~OdTransaction() = default;

    protected:
        void* m_renderTarget;
        virtual void DrawObject(std::shared_ptr<OdObjectBase> obj) = 0;
    };

    typedef std::shared_ptr<OdTransaction> OdTransactionPtr;
}