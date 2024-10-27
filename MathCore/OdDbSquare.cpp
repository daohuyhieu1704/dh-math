#include "pch.h"
#include "OdDbSquare.h"

OdDbSquare::OdDbSquare()
    : m_min(OdGePoint2d(0, 0)), m_max(OdGePoint2d(1, 1)), m_height(1.0)
{
	m_shape = "Square";
}

OdDbSquare::~OdDbSquare()
{
}

OdGePoint2d OdDbSquare::getMinPnt() const
{
    return m_min;
}

void OdDbSquare::setMinPnt(OdGePoint2d minPnt)
{
    m_min = minPnt;
    WorldDraw();
}

OdGePoint2d OdDbSquare::getMaxPnt() const
{
    return m_max;
}

void OdDbSquare::setMaxPnt(OdGePoint2d maxPnt)
{
    m_max = maxPnt;
    WorldDraw();
}

double OdDbSquare::getHeight() const
{
    return m_height;
}

void OdDbSquare::setHeight(double height)
{
    m_height = height;
    WorldDraw();
}

nlohmann::json OdDbSquare::ToJson() const
{
    nlohmann::json j;
    j["minPnt"] = { m_min.x, m_min.y };
    j["maxPnt"] = { m_max.x, m_max.y };
    j["height"] = m_height;
    return j;
}

void OdDbSquare::WorldDraw()
{
	m_boundary = OdGeExtents3d(OdGePoint3d({ m_min.x, m_min.y, 0 }), OdGePoint3d({ m_max.x, m_max.y, (float)m_height }));
    m_position = m_boundary.getCenter();
}
