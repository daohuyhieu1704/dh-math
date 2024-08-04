#pragma once
#include "pch.h"
#include "OdGeVector3d.h"
#include "OdGePoint2d.h"

namespace Geometry
{
	class OdGePoint3d
	{
	public:
		OdGePoint3d();
		OdGePoint3d(float x, float y, float z);
		~OdGePoint3d();

		float DistanceTo(OdGePoint3d other) const;
		OdGePoint2d ConvertTo2d();

		void operator+=(const OdGePoint3d& other);
		void operator+=(const OdGeVector3d& other);
		bool operator==(const OdGePoint3d& other) const;
		OdGePoint3d operator*(float scalar) const;

		float x;
		float y;
		float z;
	};
}