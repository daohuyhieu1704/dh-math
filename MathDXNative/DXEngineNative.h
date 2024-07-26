#pragma once
#include "pch.h"
#include <vector>
#include "IEngine.h"

class DXEngineNative : public IEngine
{
private:
    static DXEngineNative* m_instance;
    DXEngineNative()
	{
    }
public:
    static DXEngineNative* GetInstance()
    {
        if (m_instance == nullptr)
        {
            m_instance = new DXEngineNative();
        }
        return m_instance;
    }
#pragma region Properties
#pragma endregion

    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    HWND InitializeWindow(HINSTANCE hInstance, int nCmdShow, HWND parentHwnd);
    void ResizeWindow(HWND hwnd, int width, int height);
    HRESULT InitializeCore(HWND hwnd);
};
