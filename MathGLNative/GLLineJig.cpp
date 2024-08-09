#include "pch.h"
#include "GLLineJig.h"
#include "GLEngineNative.h"

GLLineJig::~GLLineJig()
{
    m_Line.~GLLine();
}

OdObjectBase* GLLineJig::entity() const
{
    return nullptr;
}

DragStatus GLLineJig::sampler()
{
    if (m_Line.getStartPnt().IsEqual(m_Line.getEndPnt()))
	{
		return kCancel;
	}
    return kNormal;
}

bool GLLineJig::update()
{
    return false;
}

bool GLLineJig::Preview()
{
	GLEngineNative::GetInstance()->m_tempRenders.push_back(&m_Line);
	return true;
}

DragStatus GLLineJig::AcquirePoint(OdGePoint3d point)
{
	m_Line.setEndPnt(point);
	return kNormal;
}
