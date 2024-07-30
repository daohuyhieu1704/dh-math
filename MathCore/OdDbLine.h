#pragma once
#include "OdDbEntity.h"

class OdDbLine : public OdDbEntity
{
	OdGePoint3d m_startPnt;
	OdGePoint3d m_endPnt;
public:
	OdDbLine();
	~OdDbLine();

	virtual OdGePoint3d getStartPnt() const;
	virtual void setStartPnt(OdGePoint3d startPnt);

	virtual OdGePoint3d getEndPnt() const;
	virtual void setEndPnt(OdGePoint3d endPnt);

	nlohmann::json ToJson() const override;
	void WorldDraw() override;
};

