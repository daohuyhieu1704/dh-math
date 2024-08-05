#include "pch.h"
#include "OdDbLine.h"

OdDbLine::OdDbLine() : OdDbEntity()
{
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
}

OdGePoint3d OdDbLine::getEndPnt() const
{
	return m_endPnt;
}

void OdDbLine::setEndPnt(OdGePoint3d endPnt)
{
	m_endPnt = endPnt;
}

nlohmann::json OdDbLine::ToJson() const
{
	nlohmann::json j = OdDbEntity::ToJson();
	j["Type"] = "Line";
	return j;
}

void OdDbLine::WorldDraw()
{
}
