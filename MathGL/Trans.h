#pragma once
#include "ObjectBase.h"
#include "FmTransaction.h"
#include "FmRenderer.h"
#include <FumoLog.h>

namespace FumoWrapper {
    namespace DbServices {
        public ref class Trans : public ObjectBase
        {
        public:
            Trans(IntPtr unmanagedObjPtr, bool autoDelete) : ObjectBase(System::IntPtr(unmanagedObjPtr), autoDelete) {}
            Trans() : ObjectBase(System::IntPtr(new TransactionNative(FmRenderer::Instance->GetImpObj()->CurDoc())), true) {}

            void StartTransaction()
            {  
                if (GetImpObj() == nullptr) {
                    return;
                }
                GetImpObj()->StartTransaction(FmRenderer::Instance->GetImpObj()->pRenderTarget);
            }

            void AddNewlyObject(ObjectBase^ obj)
            {
                GetImpObj()->AddNewlyObject(std::shared_ptr<FmObjectBase>(obj->GetImpObj()));
            }

            void Abort()
            {
                GetImpObj()->Abort();
            }

            void Commit()
            {
                GetImpObj()->Commit();
            }

            void Undo()
            {
                GetImpObj()->Undo();
            }

            void Redo()
            {
                GetImpObj()->Redo();
            }

        private:
            DatabaseServices::TransactionNative* GetImpObj()
            {
                void* obj = DisposableWrapper::GetImpObj();
                FumoLog::LogFunction("Trans impObj", obj);
                return static_cast<DatabaseServices::TransactionNative*>(obj);
            }
        };
    }
}
