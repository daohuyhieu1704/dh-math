#pragma once
#include "Jig.h"
#include "Point3d.h"
#include "GLLineJig.h"
#include "GLEngine.h"

using namespace System;
using namespace MathCore;
using namespace MathCore::Geom;
namespace MathGL
{
    public ref class LineJig : public Jig
    {
    public:
        LineJig();
        LineJig(Geom::Point3d startPnt);
        ~LineJig()
        {
        }

        ObjectBase^ Entity() override
        {
            if (GetImpObj() == nullptr) return nullptr;
            return gcnew ObjectBase(IntPtr(GetImpObj()->entity()), false);
        }

        DragStatusManaged Sampler() override
        {
            if (GetImpObj() == nullptr) return DragStatusManaged::NoChange;
            return static_cast<DragStatusManaged>(GetImpObj()->sampler());
        }

        bool Update() override
        {
            if (GetImpObj() == nullptr) return false;
            return GetImpObj()->update();
        }

        bool Preview() override
        {
            if (GetImpObj() == nullptr) return false;
            return GetImpObj()->Preview();
        }

        DragStatusManaged AcquirePoint(Geom::Point3d point) override
        {
            if (GetImpObj() == nullptr) return DragStatusManaged::NoChange;
            return static_cast<DragStatusManaged>(GetImpObj()->AcquirePoint(point.ToNative()));
        }

        void Commit()
		{
			if (GetImpObj() == nullptr) return;
			GLEngine::Instance->AddJig(this);
		}
    protected:
        GLLineJig* GetImpObj()
        {
            return static_cast<GLLineJig*>(DisposableWrapper::GetImpObj());
        }
    };

}
