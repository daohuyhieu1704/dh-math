#include "pch.h"
#include "DXEngine.h"

namespace MathDX
{
	DXEngine::DXEngine() : m_pEngine(DXEngineNative::GetInstance())
	{
	}
	DXEngine::~DXEngine()
	{
		delete m_pEngine;
	}
	IntPtr DXEngine::InitializeWindow(IntPtr parentHandle)
	{
		HINSTANCE hInstance = GetModuleHandle(nullptr);
		m_hwnd = m_pEngine->InitializeWindow(hInstance, SW_SHOW, static_cast<HWND>(parentHandle.ToPointer()));
		return IntPtr(m_hwnd);
	}
}
