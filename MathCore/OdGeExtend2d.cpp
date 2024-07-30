#include "pch.h"
#include "OdGeExtend2d.h"

namespace Geometry
{
	OdGePoint2d OdGeExtend2d::GetMinPnt() const
	{
		return m_minPnt;
	}

	void OdGeExtend2d::SetMinPnt(OdGePoint2d minPnt)
	{
		m_minPnt = minPnt;
	}

	OdGePoint2d OdGeExtend2d::GetMaxPnt() const
	{
		return m_maxPnt;
	}

	void OdGeExtend2d::SetMaxPnt(OdGePoint2d maxPnt)
	{
		m_maxPnt = maxPnt;
	}

	OdGeExtend2d::OdGeExtend2d(OdGePoint2d minPnt, OdGePoint2d maxPnt)
	{
		m_minPnt = minPnt;
		m_maxPnt = maxPnt;
	}

	OdGeExtend2d::~OdGeExtend2d()
	{
	}
}