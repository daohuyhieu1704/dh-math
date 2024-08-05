#pragma once
#include "OdDbCircle.h"
#include "GLCircle.h"

class MathCircle : public OdDbCircle
{
public:
    MathCircle() : OdDbCircle()
    {
        m_renderMethod = new GLCircle();
    }
    ~MathCircle();

    void setCenter(OdGePoint3d center) override;
    void setRadius(double radius) override;
};