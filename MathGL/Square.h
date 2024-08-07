#pragma once
#include "pch.h"
#include "MathSquare.h"
#include "ObjectBase.h"
#include "Point3d.h"
#include "GLEngine.h"

using namespace System;
using namespace MathCore::Geom;
using namespace MathCore;

namespace MathGL
{
	public ref class Square : public ObjectBase
	{
	public:
		Square(IntPtr unmanagedObjPtr, bool autoDelete) : ObjectBase(System::IntPtr(unmanagedObjPtr), autoDelete)
		{
		}
		Square(Point2d minPnt, Point2d maxPnt, double height) : ObjectBase(System::IntPtr(new MathSquare()), true)
		{
			MinPnt = minPnt;
			MaxPnt = maxPnt;
			Height = height;
		}

		property Point2d MinPnt
		{
			Point2d get()
			{
				return Point2d::FromNative(GetImpObj()->getMinPnt());
			}
			void set(Point2d value)
			{
				GetImpObj()->setMinPnt(value.ToNative());
			}
		}

		property Point2d MaxPnt
		{
			Point2d get()
			{
				return Point2d::FromNative(GetImpObj()->getMaxPnt());
			}
			void set(Point2d value)
			{
				GetImpObj()->setMaxPnt(value.ToNative());
			}
		}

		property double Height
		{
			double get()
			{
				return GetImpObj()->getHeight();
			}
			void set(double value)
			{
				GetImpObj()->setHeight(value);
			}
		}

		void Draw()
		{
			GLEngine::Instance->AppendCommand("SQUARE " + MinPnt.ToString() + " " + MaxPnt.ToString() + " " + Height.ToString());
		}

		String^ GetCommand()
		{
			return "SQUARE " + MinPnt.ToString() + " " + MaxPnt.ToString() + " " + Height.ToString();
		}
	private:
		MathSquare* GetImpObj()
		{
			return static_cast<MathSquare*>(ObjectBase::GetImpObj());
		}
	};
}