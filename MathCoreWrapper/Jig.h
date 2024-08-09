#pragma once
#include "OdGePoint3d.h"
#include "OdJig.h"
#include "ObjectBase.h"
#include "Point3d.h"

using namespace System;

namespace MathCore
{
    public enum class DragStatusManaged {
        Normal = 0,
        Cancel = 1,
        Other = 2,
        NoChange = 3
    };

	public ref class Jig : public DisposableWrapper
    {
    private:
        OdJig* m_pJig;

    public:
        Jig(OdJig* pJig)
			: DisposableWrapper(IntPtr(pJig), true)
        {
        }

        ~Jig()
        {
        }

        virtual ObjectBase^ Entity()
        {
            if (m_pJig == nullptr) return nullptr;
            return gcnew ObjectBase(IntPtr(GetImpObj()->entity()), false);
        }

        virtual DragStatusManaged Sampler()
        {
            if (m_pJig == nullptr) return DragStatusManaged::NoChange;
            return static_cast<DragStatusManaged>(m_pJig->sampler());
        }

        virtual bool Update()
        {
            if (m_pJig == nullptr) return false;
            return m_pJig->update();
        }

        virtual bool Preview()
        {
            if (m_pJig == nullptr) return false;
            return GetImpObj()->Preview();
        }

        virtual DragStatusManaged AcquirePoint(Geom::Point3d point)
        {
            if (GetImpObj() == nullptr) return DragStatusManaged::NoChange;
            return static_cast<DragStatusManaged>(GetImpObj()->AcquirePoint(point.ToNative()));
        }
    protected:
		OdJig* GetImpObj()
		{
			return static_cast<OdJig*>(DisposableWrapper::GetImpObj());
		}
    };
}