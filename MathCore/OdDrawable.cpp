#include "pch.h"
#include "OdDrawable.h"

ODBASE_DEFINE_RTTI_MEMBERS_GENERIC(OdDrawable, OdDrawable, OdObjectBase)

OdDrawable::OdDrawable()
{
	setDefaults();
}

void OdDrawable::setDefaults()
{
	m_position = OdGePoint3d(0, 0, 0);
	m_rotation = 0;
	m_color[0] = 1.0f;
	m_color[1] = 1.0f;
	m_color[2] = 1.0f;
	m_color[3] = 1.0f;
}

OdGePoint3d OdDrawable::GetPosition() const
{
	return m_position;
}

void OdDrawable::SetPosition(OdGePoint3d position)
{
	m_position = position;
}

void OdDrawable::SetPosition(float x, float y)
{
	m_position.x = x;
	m_position.y = y;
}

float OdDrawable::GetRotation() const
{
	return m_rotation;
}

void OdDrawable::SetRotation(float rotation)
{
	m_rotation = rotation;
}

void OdDrawable::GetColor(float* color) const
{
	for (int i = 0; i < 4; ++i) {
		color[i] = m_color[i];
	}
}

std::vector<float> OdDrawable::GetColor() const
{
	std::vector<float> color;
	for (int i = 0; i < 4; ++i) {
		color.push_back(m_color[i]);
	}
	return color;
}

void OdDrawable::SetColor(float red, float green, float blue, float alpha)
{
	m_color[0] = red;
	m_color[1] = green;
	m_color[2] = blue;
	m_color[3] = alpha;
}

OdResult OdDrawable::getGeomExtents(OdGeExtents3d& extents) const
{
	return OdResult();
}

void OdDrawable::addRef()
{
}

void OdDrawable::release()
{
}
