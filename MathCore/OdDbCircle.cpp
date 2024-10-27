#include "pch.h"
#include "OdDbCircle.h"

OdDbCircle::OdDbCircle()
	: OdDbEntity(), m_center(OdGePoint3d(0, 0, 0)), m_radius(0)
{
    m_shape = "Circle";
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
	SetPosition(center);
    m_center = center;
    WorldDraw();
}

float OdDbCircle::getRadius() const
{
    return m_radius;
}

void OdDbCircle::setRadius(float radius)
{
    m_radius = radius;
    WorldDraw();
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
	m_boundary = OdGeExtents3d(OdGePoint3d({ m_center.x - m_radius, m_center.y - m_radius, 0 }), OdGePoint3d({ m_center.x + m_radius, m_center.y + m_radius, 0 }));
}