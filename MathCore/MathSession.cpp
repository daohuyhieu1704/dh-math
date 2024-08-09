#include "pch.h"
#include "MathSession.h"

void MathSession::undo()
{
	mathPrompt.undo();
}

void MathSession::redo()
{
	mathPrompt.redo();
}