#include "pch.h"
#include "MathLog.h"
#include "OdTransaction.h"
#include "OdDatabase.h"
#include "OdDrawable.h"
#include <type_traits>

namespace DatabaseServices {

    ODBASE_DEFINE_RTTI_MEMBERS_GENERIC(OdTransaction, OdTransaction, OdObjectBase)
        OdTransaction::OdTransaction() : m_transactionActive(false), m_isUndoRedoInProgress(false) {}

    void OdTransaction::StartTransaction() {
        MathLog::LogFunction("OdTransaction::StartTransaction", "MathCore", m_transactionActive);
        if (m_transactionActive) {
            throw std::runtime_error("Transaction is already active");
        }

        m_transactionActive = true;
        m_newlyAddedObjects.clear();
    }

    void OdTransaction::AddNewlyObject(OdDrawablePtr obj) {
        if (!m_transactionActive) {
            throw std::runtime_error("No active transaction");
        }
        if (obj.isNull()) return;
        if (m_newlyAddedObjects.find(obj->objectId()) != m_newlyAddedObjects.end()) {
            throw std::runtime_error("Object with the given ID already exists");
        }
        m_newlyAddedObjects[obj->objectId()] = obj;
    }

    void OdTransaction::Abort() {
        if (!m_transactionActive) {
            throw std::runtime_error("No active transaction to abort");
        }
        m_newlyAddedObjects.clear();
        m_transactionActive = false;
    }

    void OdTransaction::Commit() {
        if (!m_transactionActive) {
            throw std::runtime_error("No active transaction to commit");
        }
        for (auto& pair : m_newlyAddedObjects) {
            m_Doc->AppendObject(pair.second);
            DrawObject(pair.second);
        }
        m_newlyAddedObjects.clear();
        m_transactionActive = false;
    }
}
