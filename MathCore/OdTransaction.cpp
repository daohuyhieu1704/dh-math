#include "pch.h"
#include "MathLog.h"
#include "OdTransaction.h"
#include "OdDatabase.h"
#include "OdDrawable.h"
#include <type_traits>

namespace DatabaseServices {
    void OdTransaction::StartTransaction() {
        MathLog::LogFunction("OdTransaction::StartTransaction", "MathCore", m_transactionActive);
        if (m_transactionActive) {
            throw std::runtime_error("Transaction is already active");
        }

        m_transactionActive = true;
        m_newlyAddedObjects.clear();
    }

    void OdTransaction::AddNewlyObject(std::shared_ptr<OdObjectBase> obj) {
        if (!m_transactionActive) {
            throw std::runtime_error("No active transaction");
        }
        if (obj == nullptr) {
            return;
        }
        if (m_newlyAddedObjects.find(obj.get()->GetObjectId()) != m_newlyAddedObjects.end()) {
            throw std::runtime_error("Object with the given ID already exists");
        }
        m_newlyAddedObjects[obj->GetObjectId()] = obj;
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
            m_Doc.get()->AppendObject(pair.second);
            DrawObject(pair.second);
        }
        m_newlyAddedObjects.clear();
        m_transactionActive = false;
    }
}
