#pragma once
#include "DisposableWrapper.h"
#include <msclr/marshal_cppstd.h>

using namespace System;

namespace MathCore
{
    public ref class ObjectBase : public DisposableWrapper
    {
    public:
        ObjectBase(IntPtr unmanagedObjPtr, bool autoDelete) : DisposableWrapper(System::IntPtr(unmanagedObjPtr), autoDelete)
        {
        }
    };
}
