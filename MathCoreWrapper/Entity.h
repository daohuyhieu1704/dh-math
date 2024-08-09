#pragma once
#include "OdDbEntity.h"
#include "DisposableWrapper.h"
#include "DbObject.h"
#include "Extend3d.h"

namespace MathCore
{
	public ref class Entity : public DbObject
	{
	public:
		Entity(System::IntPtr UnmanagedObject, bool autoDelete)
			: DbObject(UnmanagedObject, autoDelete) {};

		property String^ Shape
		{
			String^ get()
			{
				return gcnew String(GetImpObj()->getShape().c_str());
			}
		}

        property Extend3d Boundary
        {
            Extend3d get()
            {
                return Extend3d::FromNative(GetImpObj()->GetBoundary());
            }

            void set(Extend3d value)
            {
                static_cast<OdDbEntity*>(GetImpObj())->SetBoundary(value.ToNative());
            }
        }

        property String^ Json
        {
            String^ get() override
            {
                nlohmann::json json = GetImpObj()->ToJson();
                std::string jsonString = json.dump();
                return gcnew System::String(jsonString.c_str());
            }
        }

        virtual void WorldDraw()
        {
            static_cast<OdDbEntity*>(GetImpObj())->WorldDraw();
        }

		Drawable^ Clone() override
        {
            OdDrawable* clonedEntity = static_cast<OdDrawable*>(GetImpObj()->Clone());
            return gcnew Drawable(IntPtr(clonedEntity), true);
        }
    protected:
		OdDbEntity* GetImpObj()
		{
			return static_cast<OdDbEntity*>(DisposableWrapper::GetImpObj());
		}
	};

}

