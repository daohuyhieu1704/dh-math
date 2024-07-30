#pragma once
#include "RenderEntity.h"
#include "OdGePoint3d.h"

using namespace Geometry;

class GLLine : public RenderEntity
{
private:
	OdGePoint3d m_startPnt;
	OdGePoint3d m_endPnt;

public:
#pragma region Properties
	OdGePoint3d getStartPnt() const;
	void setStartPnt(OdGePoint3d startPnt);

	OdGePoint3d getEndPnt() const;
	void setEndPnt(OdGePoint3d endPnt);
#pragma endregion

	void render() override;
	~GLLine(){}
};

