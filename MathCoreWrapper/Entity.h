#pragma once

#include "OdDbEntity.h"
#include "DisposableWrapper.h"
#include "DbObject.h"
#include "Extend2d.h"

namespace MathCore
{
	public ref class Entity : DbObject
	{
	public:
		Entity(System::IntPtr UnmanagedObject, bool autoDelete)
			: DbObject(UnmanagedObject, autoDelete) {};

        property Extend2d Boundary
        {
            Extend2d get()
            {
                return Extend2d::FromNative(GetImpObj()->GetBoundary());
            }

            void set(Extend2d value)
            {
                static_cast<OdDbEntity*>(GetImpObj())->SetBoundary(value.ToNative());
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

