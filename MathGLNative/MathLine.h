#pragma once
#include "OdDbLine.h"
#include "GLLine.h"

class MathLine : public OdDbLine
{
public:
	MathLine() : OdDbLine() 
	{
		m_renderMethod = new GLLine();
	}
	~MathLine();

	void setStartPnt(OdGePoint3d startPnt) override;

	void setEndPnt(OdGePoint3d endPnt) override;
};

