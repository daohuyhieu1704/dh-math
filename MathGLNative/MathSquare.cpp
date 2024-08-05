#include "pch.h"
#include "MathSquare.h"

MathSquare::~MathSquare()
{
}

void MathSquare::setMinPnt(OdGePoint2d minPnt)
{
    OdDbSquare::setMinPnt(minPnt);
    ((GLSquare*)m_renderMethod)->setMinPnt(minPnt);
}

void MathSquare::setMaxPnt(OdGePoint2d maxPnt)
{
    OdDbSquare::setMaxPnt(maxPnt);
    ((GLSquare*)m_renderMethod)->setMaxPnt(maxPnt);
}

void MathSquare::setHeight(double height)
{
    OdDbSquare::setHeight(height);
    ((GLSquare*)m_renderMethod)->setHeight(height);
}
