#pragma once
#include "CommandPrompt.h"
#include <algorithm>

using namespace EditorInput;

class MathSession
{
public:
    MathSession() : mathPrompt() {}
	void undo();
	void redo();
private:
    CommandPrompt mathPrompt;
};

