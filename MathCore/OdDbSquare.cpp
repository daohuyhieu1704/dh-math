#include "pch.h"
#include "OdDbSquare.h"

OdDbSquare::OdDbSquare()
    : m_minPnt(OdGePoint2d(0, 0)), m_maxPnt(OdGePoint2d(1, 1)), m_height(1.0)
{
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
}

OdGePoint2d OdDbSquare::getMaxPnt() const
{
    return m_maxPnt;
}

void OdDbSquare::setMaxPnt(OdGePoint2d maxPnt)
{
    m_maxPnt = maxPnt;
}

double OdDbSquare::getHeight() const
{
    return m_height;
}

void OdDbSquare::setHeight(double height)
{
    m_height = height;
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
}
