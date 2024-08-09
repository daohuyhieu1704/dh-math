#pragma once
#include "Drawable.h"
#include "OdGePoint3d.h"
#include "RenderEntity.h"
#include "ObjectBase.h"
#include "Point3d.h"
#include <OdDbObject.h>

using namespace System;
using namespace System::Collections::Generic;

namespace MathCore
{
    public ref class DbObject : public Drawable
    {
    public:
        DbObject(IntPtr unmanagedObjPtr, bool autoDelete) : Drawable(unmanagedObjPtr, autoDelete)
        {
        }
        ~DbObject() {}
        virtual property String^ Json
        {
            String^ get()
            {
                nlohmann::json json = GetImpObj()->ToJson();
                std::string jsonString = json.dump();
                return gcnew System::String(jsonString.c_str());
            }
        }
    protected:
        OdDbObject* GetImpObj()
        {
            return static_cast<OdDbObject*>(Drawable::GetImpObj());
        }
    };
}