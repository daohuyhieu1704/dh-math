#pragma once
#include "ObjectBase.h"
#include "OdTransaction.h"
#include "IEngine.h"
#include <MathLog.h>

using namespace DatabaseServices;

namespace MathCore {
    namespace DbServices {
        public ref class Trans : public ObjectBase
        {
        public:
            Trans(IntPtr unmanagedObjPtr, bool autoDelete) : ObjectBase(System::IntPtr(unmanagedObjPtr), autoDelete) {}

            void StartTransaction()
            {  
                if (GetImpObj() == nullptr) {
                    return;
                }
                GetImpObj()->StartTransaction();
            }

            void AddNewlyObject(ObjectBase^ obj)
            {
                GetImpObj()->AddNewlyObject(std::shared_ptr<OdObjectBase>(obj->GetImpObj()));
            }

            void Abort()
            {
                GetImpObj()->Abort();
            }

            void Commit()
            {
                GetImpObj()->Commit();
            }

        private:
            DatabaseServices::OdTransaction* GetImpObj()
            {
                void* obj = DisposableWrapper::GetImpObj();
                MathLog::LogFunction("Trans impObj", obj);
                return static_cast<DatabaseServices::OdTransaction*>(obj);
            }
        };
    }
}
