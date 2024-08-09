#pragma once
#include "OdJig.h"
#include "GLCircle.h"

class GLCircleJig : public OdJig
{
public:
    GLCircleJig(OdGePoint3d center) : GLCircleJig()
    {
        m_Circle.setCenter(center);
    }
    GLCircleJig() : m_Circle() {}
    ~GLCircleJig();

    // Inherited via OdJig
    OdObjectBase* entity() const override;
    DragStatus sampler() override;
    bool update() override;
    bool Preview() override;
    DragStatus AcquirePoint(OdGePoint3d point) override;

private:
    GLCircle m_Circle;
};
