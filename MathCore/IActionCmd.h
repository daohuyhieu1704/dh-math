#pragma once
#include <string>
#include <vector>

class IActionCmd
{
private:
	std::string m_id;
public:
	IActionCmd();
	std::string getId() const;
	virtual ~IActionCmd() = default;
	virtual bool execute() = 0;
	virtual void serialize(const std::vector<std::string>& strData) = 0;

	std::string m_commandName;
};

