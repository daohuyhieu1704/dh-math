#pragma once
#include "CommandPrompt.h"
#include <algorithm>

using namespace EditorInput;

class MathSession
{
public:
    MathSession()
	{
		mathPrompt = CommandPrompt();
	}
	void undo();
	void redo();
	CommandPrompt& getPrompts() { return mathPrompt; }
    CommandPrompt mathPrompt;
private:
};

