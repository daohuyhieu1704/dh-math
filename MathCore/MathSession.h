#pragma once
#include "CommandPrompt.h"
#include <algorithm>
#include <string>
#include <stack>

using namespace EditorInput;

class MathSession
{
	std::string fileName = "";
public:
    MathSession()
	{
		mathPrompt = CommandPrompt();
	}
	~MathSession() = default;
	std::string getFileName() { return fileName; }
	void setFileName(std::string name) { fileName = name; }
	void undo();
	void redo();
	CommandPrompt& getPrompts() { return mathPrompt; }
	void ExecuteAllPrompts()
	{
		mathPrompt.executeAllPrompts();
	}
    CommandPrompt mathPrompt;
};

