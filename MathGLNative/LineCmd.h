#pragma once
#include "pch.h"
#include "CommandPrompt.h"
#include <stdexcept>
#include "OdGePoint3d.h"

class LineCmd : public IActionCmd
{
public:
	bool execute() override;
	void serialize(const std::vector<std::string>& strData) override;
private:
	Geometry::OdGePoint3d startPnt;
	Geometry::OdGePoint3d endPnt;
};

