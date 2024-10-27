#include "pch.h"
#include "OdDbLine.h"

OdDbLine::OdDbLine() : OdDbEntity()
{
	m_shape = "Line";
}

OdDbLine::~OdDbLine()
{
	delete m_renderMethod;
}

OdGePoint3d OdDbLine::getStartPnt() const
{
	return m_startPnt;
}

void OdDbLine::setStartPnt(OdGePoint3d startPnt)
{
	m_startPnt = startPnt;
	WorldDraw();
}

OdGePoint3d OdDbLine::getEndPnt() const
{
	return m_endPnt;
}

void OdDbLine::setEndPnt(OdGePoint3d endPnt)
{
	m_endPnt = endPnt;
	WorldDraw();
}

nlohmann::json OdDbLine::ToJson() const
{
	nlohmann::json j = OdDbEntity::ToJson();
	j["Type"] = "Line";
	return j;
}

void OdDbLine::WorldDraw()
{
	m_boundary = OdGeExtents3d(OdGePoint3d({ m_startPnt.x, m_startPnt.y, 0 }), OdGePoint3d({ m_endPnt.x, m_endPnt.y, 0 }));
}
