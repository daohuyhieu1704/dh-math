#include "pch.h"
#include "OdGeExtend3d.h"

namespace Geometry
{
	OdGePoint3d OdGeExtend3d::getCenter() const
	{
		return m_minPnt.CenterTo(m_maxPnt);
	}
}