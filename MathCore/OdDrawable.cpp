#include "pch.h"
#include "OdDrawable.h"

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