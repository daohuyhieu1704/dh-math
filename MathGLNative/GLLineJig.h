#pragma once
#include "OdJig.h"
#include "GLLine.h"

class GLLineJig : public OdJig
{
public:
	GLLineJig(OdGePoint3d point) : GLLineJig()
	{
		m_Line.setStartPnt(point);
	}
	GLLineJig() : m_Line() {}
	~GLLineJig();
	// Inherited via OdJig
	OdObjectBase* entity() const override;
	DragStatus sampler() override;
	bool update() override;
	bool Preview() override;
	DragStatus AcquirePoint(OdGePoint3d point) override;
private:
	GLLine m_Line;
};

