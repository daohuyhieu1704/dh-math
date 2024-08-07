#pragma once
#include "pch.h"
#include "MathCircle.h"
#include "ObjectBase.h"
#include "Point3d.h"
#include "GLEngine.h"

using namespace System;
using namespace MathCore::Geom;
using namespace MathCore;

namespace MathGL
{
	public ref class Circle : public ObjectBase
	{
	public:
		Circle(IntPtr unmanagedObjPtr, bool autoDelete) : ObjectBase(System::IntPtr(unmanagedObjPtr), autoDelete)
		{
		}
		Circle(Point3d center, double radius) : ObjectBase(System::IntPtr(new MathCircle()), true)
		{
			Center = center;
			Radius = radius;
		}

		property Point3d Center
		{
			Point3d get()
			{
				return Point3d::FromNative(GetImpObj()->getCenter());
			}
			void set(Point3d value)
			{
				GetImpObj()->setCenter(value.ToNative());
			}
		}

		property double Radius
		{
			double get()
			{
				return GetImpObj()->getRadius();
			}
			void set(double value)
			{
				GetImpObj()->setRadius(value);
			}
		}

		property double Diameter
		{
			double get()
			{
				return Radius * 2;
			}
		}

		void Draw()
		{
			GLEngine::Instance->AppendCommand("CIRCLE " + Center.ToString() + " " + Radius.ToString());
		}

		String^ GetCommand()
		{
			return "CIRCLE " + Center.ToString() + " " + Radius.ToString();
		}
	private:
		MathCircle* GetImpObj()
		{
			return static_cast<MathCircle*>(ObjectBase::GetImpObj());
		}
	};
}