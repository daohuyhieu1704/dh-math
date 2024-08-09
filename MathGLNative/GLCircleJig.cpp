#include "pch.h"
#include "GLCircleJig.h"
#include "GLEngineNative.h"

GLCircleJig::~GLCircleJig()
{
    m_Circle.~GLCircle();
}

OdObjectBase* GLCircleJig::entity() const
{
    return nullptr;
}

DragStatus GLCircleJig::sampler()
{
    if (m_Circle.getRadius() == 0.0)
    {
        return kCancel;
    }
    return kNormal;
}

bool GLCircleJig::update()
{
    return false;
}

bool GLCircleJig::Preview()
{
    GLEngineNative::GetInstance()->m_tempRenders.push_back(&m_Circle);
    return true;
}

DragStatus GLCircleJig::AcquirePoint(OdGePoint3d point)
{
    m_Circle.setRadius(point.DistanceTo(m_Circle.getCenter()));
    return kNormal;
}
