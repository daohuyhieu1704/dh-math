#pragma once
#include "pch.h"
#include "CommandPrompt.h"
#include <stdexcept>
#include "OdGePoint3d.h"

class LineCmd : public IActionCmd
{
public:
	ODBASE_DECLARE_MEMBERS(LineCmd);
	bool execute() override;
	bool serialize(const std::vector<std::string>& strData) override;
private:
	Geometry::OdGePoint3d startPnt;
	Geometry::OdGePoint3d endPnt;

	// Inherited via IActionCmd
	void addRef() override;
	void release() override;
};

typedef OdSmartPtr<LineCmd> LineCmdPtr;
