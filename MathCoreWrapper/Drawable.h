#pragma once

#include "OdDrawable.h"
#include "OdGePoint3d.h"
#include "RenderEntity.h"
#include "ObjectBase.h"
#include "Point3d.h"

using namespace System;
using namespace System::Collections::Generic;

namespace MathCore
{
    using namespace MathCore::Geom;
    public ref class Drawable : public ObjectBase
    {
    public:
        Drawable(IntPtr unmanagedObjPtr, bool autoDelete)
            : ObjectBase(unmanagedObjPtr, autoDelete)
        {
        }

        ~Drawable()
        {
        }

        property Point3d Position
        {
            Point3d get()
            {
                return Point3d::FromNative(GetImpObj()->GetPosition());
            }

            void set(Point3d value)
            {
                if (GetImpObj() != nullptr)
                {
                    GetImpObj()->SetPosition(value.ToNative());
                }
            }
        }

        property float Rotation
        {
            float get()
            {
                if (GetImpObj() == nullptr) return 0.0f;
                return GetImpObj()->GetRotation();
            }

            void set(float value)
            {
                if (GetImpObj() != nullptr)
                {
                    GetImpObj()->SetRotation(value);
                }
            }
        }

        property List<float>^ Color
        {
            List<float>^ get()
            {
                List<float>^ color = gcnew List<float>(4);
                if (GetImpObj() == nullptr) return color;
                array<float>^ colorArray = color->ToArray();
                pin_ptr<float> pinnedArray = &colorArray[0];

                float* colorPtr = pinnedArray;

                GetImpObj()->GetColor(colorPtr);
                return color;
            }

            void set(List<float>^ value)
            {
                if (GetImpObj() != nullptr)
                {
                    array<float>^ colorArray = value->ToArray();
                    pin_ptr<float> pinnedArray = &colorArray[0];

                    float* colorPtr = pinnedArray;

                    GetImpObj()->SetColor(colorPtr[0], colorPtr[1], colorPtr[2], colorPtr[3]);
                }
            }
        }

        virtual Drawable^ Clone()
        {
            if (GetImpObj() == nullptr) return nullptr;
            return gcnew Drawable(IntPtr(GetImpObj()->Clone()), false);
        }
    protected:
        OdDrawable* GetImpObj()
        {
            return static_cast<OdDrawable*>(DisposableWrapper::GetImpObj());
        }
    };
}