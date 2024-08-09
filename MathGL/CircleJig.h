#pragma once
#include "Jig.h"
#include "Point3d.h"
#include "GLCircleJig.h"
#include "GLEngine.h"

using namespace System;
using namespace MathCore;
using namespace MathCore::Geom;

namespace MathGL
{
    public ref class CircleJig : public Jig
    {
    public:
        CircleJig();
        CircleJig(Geom::Point3d centerPnt);
        ~CircleJig()
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

        DragStatusManaged AcquireRadius(Geom::Point3d point) override
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
        GLCircleJig* GetImpObj()
        {
            return static_cast<GLCircleJig*>(DisposableWrapper::GetImpObj());
        }
    };
}
