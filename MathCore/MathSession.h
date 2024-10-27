#pragma once
#include "CommandPrompt.h"
#include <algorithm>
#include <string>
#include <stack>

using namespace EditorInput;

class MathSession : public OdObjectBase
{
	std::string fileName = "";
public:
	ODBASE_DECLARE_MEMBERS(MathSession);
    MathSession()
	{
		mathPrompt = CommandPrompt::createObject();
	}
	~MathSession() = default;
	std::string getFileName() { return fileName; }
	void setFileName(std::string name) { fileName = name; }
	void undo();
	void redo();
	CommandPromptPtr getPrompts() { return mathPrompt; }
	void ExecuteAllPrompts()
	{
		mathPrompt->executeAllPrompts();
	}
    CommandPromptPtr mathPrompt;
};

typedef OdSmartPtr<MathSession> MathSessionPtr;
