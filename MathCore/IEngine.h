#pragma once
#include <Windows.h>

class IEngine
{
public:
    virtual ~IEngine() = default;
	virtual HWND InitializeWindow(HINSTANCE hInstance, int nCmdShow, HWND parentHwnd) = 0;
};

