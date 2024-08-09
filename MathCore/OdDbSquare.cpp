#include "pch.h"
#include "OdDbSquare.h"

OdDbSquare::OdDbSquare()
    : m_minPnt(OdGePoint2d(0, 0)), m_maxPnt(OdGePoint2d(1, 1)), m_height(1.0)
{
	m_shape = "Square";
}

OdDbSquare::~OdDbSquare()
{
}

OdGePoint2d OdDbSquare::getMinPnt() const
{
    return m_minPnt;
}

void OdDbSquare::setMinPnt(OdGePoint2d minPnt)
{
    m_minPnt = minPnt;
    WorldDraw();
}

OdGePoint2d OdDbSquare::getMaxPnt() const
{
    return m_maxPnt;
}

void OdDbSquare::setMaxPnt(OdGePoint2d maxPnt)
{
    m_maxPnt = maxPnt;
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
    j["minPnt"] = { m_minPnt.x, m_minPnt.y };
    j["maxPnt"] = { m_maxPnt.x, m_maxPnt.y };
    j["height"] = m_height;
    return j;
}

void OdDbSquare::WorldDraw()
{
	m_boundary = OdGeExtend3d(OdGePoint3d({ m_minPnt.x, m_minPnt.y, 0 }), OdGePoint3d({ m_maxPnt.x, m_maxPnt.y, 0 }));
}
