#pragma once

namespace Geometry
{
	class OdGePoint2d
	{
	public:
		OdGePoint2d();
		OdGePoint2d(float x, float y);
		~OdGePoint2d();
		float x;
		float y;
	};
}
