#pragma once
#include "ObjectBase.h"

using namespace System::Collections::Generic;

namespace FumoWrapper {
    namespace DbServices {
        public ref class Dtr : public ObjectBase
        {
        public:
            Dtr(IntPtr unmanagedObjPtr, bool autoDelete) : ObjectBase(System::IntPtr(unmanagedObjPtr), autoDelete) {}
            Dtr() : ObjectBase(System::IntPtr(new DataTableRecordNative()), true) {}

            void AddObject(ObjectBase^ obj)
            {
                GetImpObj()->AddObject(std::unique_ptr<FmObjectBase>(obj->GetImpObj()));
            }

            bool GetObjectById(System::String^ id, ObjectBase^% obj)
            {
                std::string nativeId = msclr::interop::marshal_as<std::string>(id);
                std::shared_ptr<FmObjectBase> nativeObj;
                bool result = GetImpObj()->GetObjectById(nativeId, nativeObj);
                if (result)
                {
                    obj = gcnew ObjectBase(System::IntPtr(nativeObj.get()), true);
                }
                return result;
            }

            property List<ObjectBase^>^ Objects
            {
                List<ObjectBase^>^ get()
                {
                    auto objects = GetImpObj()->GetObjects();
                    List<ObjectBase^>^ list = gcnew List<ObjectBase^>(objects.size());
                    for (const auto& obj : objects)
                    {
                        list->Add(gcnew ObjectBase(System::IntPtr(obj.get()), true));
                    }
                    return list;
                }
            }

            property System::String^ Json
            {
                System::String^ get()
                {
                    nlohmann::json json = GetImpObj()->ToJson();
                    std::string jsonString = json.dump();
                    return gcnew System::String(jsonString.c_str());
                }
            }

        private:
            DataTableRecordNative* GetImpObj()
            {
                return static_cast<DataTableRecordNative*>(ObjectBase::GetImpObj());
            }
        };
    }
}
