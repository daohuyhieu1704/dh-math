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
				OdDrawablePtr drawable = OdDrawable::cast(obj->GetImpObj());
				if (drawable.isNull()) return;
                GetImpObj()->AddNewlyObject(drawable);
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
            DatabaseServices::OdTransactionPtr GetImpObj()
            {
                OdTransactionPtr obj = OdTransaction::cast(ObjectBase::GetImpObj());
                if (obj.isNull())
                {
                    MathLog::LogFunction("Error Trans impObj", obj);
                }
                return obj;
            }
        };
    }
}
