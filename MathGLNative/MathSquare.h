#pragma once
#include "OdDbSquare.h"
#include "GLSquare.h"

class MathSquare : public OdDbSquare
{
public:
    MathSquare() : OdDbSquare()
    {
        m_renderMethod = new GLSquare();
    }
    ~MathSquare();

    void setMinPnt(OdGePoint2d minPnt) override;
    void setMaxPnt(OdGePoint2d maxPnt) override;
    void setHeight(double height) override;
};
