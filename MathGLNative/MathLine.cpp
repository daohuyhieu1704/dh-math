#include "pch.h"
#include "MathLine.h"

MathLine::~MathLine()
{
	delete m_renderMethod;
}

void MathLine::setStartPnt(OdGePoint3d startPnt)
{
	OdDbLine::setStartPnt(startPnt);
	((GLLine*)m_renderMethod)->setStartPnt(startPnt);
}

void MathLine::setEndPnt(OdGePoint3d endPnt)
{
	OdDbLine::setEndPnt(endPnt);
	((GLLine*)m_renderMethod)->setEndPnt(endPnt);
}
