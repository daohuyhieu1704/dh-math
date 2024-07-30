#pragma once
#include "pch.h"
#include "MathLine.h"
// #using <MathCoreWrapper.dll> as_friend;

using namespace System;
namespace MathGL
{
	//using namespace MathCore::Geom;
	//using namespace MathCore;
	//public ref class Line : public ObjectBase
	//{
	//public:
	//	Line(IntPtr unmanagedObjPtr, bool autoDelete) : ObjectBase(System::IntPtr(unmanagedObjPtr), autoDelete)
	//	{
	//	}
	//	Line(Point3d startPnt, Point3d endPnt) : ObjectBase(System::IntPtr(new MathLine()), true)
	//	{
	//		StartPnt = startPnt;
	//		EndPnt = endPnt;
	//	}

	//	property Point3d StartPnt
	//	{
	//		Point3d get()
	//		{
	//			return Point3d::FromNative(GetImpObj()->getStartPnt());
	//		}
	//		void set(Point3d value)
	//		{
	//			GetImpObj()->setStartPnt(value.ToNative());
	//		}
	//	}

	//	property Point3d EndPnt
	//	{
	//		Point3d get()
	//		{
	//			return Point3d::FromNative(GetImpObj()->getEndPnt());
	//		}
	//		void set(Point3d value)
	//		{
	//			GetImpObj()->setEndPnt(value.ToNative());
	//		}
	//	}

	//private:
	//	MathLine* GetImpObj()
	//	{
	//		void* obj = GetImpObj();
	//		MathLine* line = static_cast<MathLine*>(obj);
	//		return line;
	//	}
	//}
}