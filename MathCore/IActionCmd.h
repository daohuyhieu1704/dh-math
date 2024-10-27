#pragma once
#include "ObjectBase.h"
#include <string>
#include <vector>

class IActionCmd : public OdObjectBase
{
public:
	ODBASE_DECLARE_MEMBERS(IActionCmd);
	IActionCmd(){}
	virtual ~IActionCmd() = default;
	virtual bool execute() = 0;
	virtual bool serialize(const std::vector<std::string>& strData) = 0;
	std::string m_commandName;
};

typedef OdSmartPtr<IActionCmd> IActionCmdPtr;