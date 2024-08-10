#pragma once
#include <Windows.h>
#include "OdDatabase.h"

using namespace DatabaseServices;
class IEngine
{
public:
    virtual ~IEngine() = default;
	virtual HWND InitializeWindow(HINSTANCE hInstance, int nCmdShow, HWND parentHwnd) = 0;
	// virtual OdDatabasePtr CurDoc() = 0;
};

