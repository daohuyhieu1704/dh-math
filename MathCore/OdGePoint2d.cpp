#include "pch.h"
#include "OdGePoint2d.h"

namespace Geometry
{
	OdGePoint2d::OdGePoint2d()
	{
		x = 0;
		y = 0;
	}

	OdGePoint2d::OdGePoint2d(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	OdGePoint2d::~OdGePoint2d()
	{
	}
	double OdGePoint2d::DistanceTo(OdGePoint2d point)
	{
		return sqrt(pow(point.x - x, 2) + pow(point.y - y, 2));
	}
}