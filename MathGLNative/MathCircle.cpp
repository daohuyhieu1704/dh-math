#include "pch.h"
#include "MathCircle.h"

MathCircle::~MathCircle()
{
	delete m_renderMethod;
}

void MathCircle::setCenter(OdGePoint3d center)
{
    OdDbCircle::setCenter(center);
    ((GLCircle*)m_renderMethod)->setCenter(center);
}

void MathCircle::setRadius(float radius)
{
    OdDbCircle::setRadius(radius);
    ((GLCircle*)m_renderMethod)->setRadius(radius);
}