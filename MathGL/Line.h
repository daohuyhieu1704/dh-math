#pragma once
#include "pch.h"
#include "MathLine.h"
#include "ObjectBase.h"
#include "Point3d.h"
#include "GLEngine.h"

using namespace System;
using namespace MathCore::Geom;
using namespace MathCore;

namespace MathGL
{
	public ref class Line : public ObjectBase
	{
	public:
		Line(IntPtr unmanagedObjPtr, bool autoDelete) : ObjectBase(System::IntPtr(unmanagedObjPtr), autoDelete)
		{
		}
		Line(Point3d startPnt, Point3d endPnt) : ObjectBase(System::IntPtr(new MathLine()), true)
		{
			StartPnt = startPnt;
			EndPnt = endPnt;
		}

		property Point3d StartPnt
		{
			Point3d get()
			{
				return Point3d::FromNative(GetImpObj()->getStartPnt());
			}
			void set(Point3d value)
			{
				GetImpObj()->setStartPnt(value.ToNative());
			}
		}

		property Point3d EndPnt
		{
			Point3d get()
			{
				return Point3d::FromNative(GetImpObj()->getEndPnt());
			}
			void set(Point3d value)
			{
				GetImpObj()->setEndPnt(value.ToNative());
			}
		}

		void Draw()
		{
			GLEngine::Instance->AppendCommand("LINE " + StartPnt.ToString() + " " + EndPnt.ToString());
		}

		String^ GetCommand()
		{
			return "LINE " + StartPnt.ToString() + " " + EndPnt.ToString();
		}
	private:
		MathLine* GetImpObj()
		{
			return static_cast<MathLine*>(ObjectBase::GetImpObj());
		}
	};
}