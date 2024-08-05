#include "pch.h"
#include "OdDbCircle.h"

OdDbCircle::OdDbCircle()
    : m_center(OdGePoint3d(0, 0, 0)), m_radius(0)
{
}

OdDbCircle::~OdDbCircle()
{
}

OdGePoint3d OdDbCircle::getCenter() const
{
    return m_center;
}

void OdDbCircle::setCenter(OdGePoint3d center)
{
    m_center = center;
}

double OdDbCircle::getRadius() const
{
    return m_radius;
}

void OdDbCircle::setRadius(double radius)
{
    m_radius = radius;
}

nlohmann::json OdDbCircle::ToJson() const
{
    nlohmann::json j;
    j["center"] = { m_center.x, m_center.y, m_center.z };
    j["radius"] = m_radius;
    return j;
}

void OdDbCircle::WorldDraw()
{
}