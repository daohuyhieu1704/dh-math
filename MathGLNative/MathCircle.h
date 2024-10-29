#pragma once
#include "OdDbCircle.h"
#include "GLCircle.h"

class MathCircle : public OdDbCircle
{
public:
    MathCircle() : OdDbCircle()
    {
        m_renderMethod = GLCircle::createObject();
    }
    ~MathCircle();

    void setCenter(OdGePoint3d center) override;
    void setRadius(float radius) override;
};