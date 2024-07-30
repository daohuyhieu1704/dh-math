#include "pch.h"
#include "GLLine.h"
#include "GLEngineNative.h"

OdGePoint3d GLLine::getStartPnt() const
{
	return m_startPnt;
}

void GLLine::setStartPnt(OdGePoint3d startPnt)
{
	m_startPnt = startPnt;
}

OdGePoint3d GLLine::getEndPnt() const
{
	return m_endPnt;
}

void GLLine::setEndPnt(OdGePoint3d endPnt)
{
	m_endPnt = endPnt;
}

void GLLine::render()
{
    glBegin(GL_LINES);
	glVertex3f(m_startPnt.x, m_startPnt.y, m_startPnt.z);
	glVertex3f(m_endPnt.x, m_endPnt.y, m_endPnt.z);
    glEnd();
}
