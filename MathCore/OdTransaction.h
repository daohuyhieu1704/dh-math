#pragma once

#include "OdObjectBase.h"
#include "OdDrawable.h"
#include <map>
#include <deque>
#include <memory>
#include <stdexcept>

namespace DatabaseServices {
    class OdDatabase;
    typedef OdSmartPtr<OdDatabase> OdDatabasePtr;

    class OdTransaction : public OdObjectBase
    {
    protected:
        bool m_transactionActive;
        OdDatabasePtr m_Doc;
        std::map<OdDbObjectId, OdDrawablePtr> m_newlyAddedObjects;
        bool m_isUndoRedoInProgress;
        std::deque<OdObjectBasePtr> m_undoneObjects;

    public:
		ODBASE_DECLARE_MEMBERS(OdTransaction);
        OdTransaction();
        OdTransaction(OdDatabasePtr parentDoc) : m_transactionActive(false), m_Doc(parentDoc), m_isUndoRedoInProgress(false) {}

        void StartTransaction();
        void AddNewlyObject(OdDrawablePtr obj);
        void Abort();
        void Commit();
        virtual ~OdTransaction() = default;

    protected:
        RenderEntityPtr m_renderTarget;
        virtual void DrawObject(OdDrawablePtr obj) = 0;
    };

    typedef OdSmartPtr<OdTransaction> OdTransactionPtr;
}