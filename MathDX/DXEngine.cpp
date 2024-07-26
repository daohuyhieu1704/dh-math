#include "pch.h"
#include "DXEngine.h"

namespace MathDX
{
	DXEngine::DXEngine()
	{
		throw gcnew System::NotImplementedException();
	}
	DXEngine::~DXEngine()
	{
		throw gcnew System::NotImplementedException();
	}
	IntPtr DXEngine::InitializeWindow(IntPtr parentHandle)
	{
		HINSTANCE hInstance = GetModuleHandle(nullptr);
		m_hwnd = m_pEngine->InitializeWindow(hInstance, SW_SHOW, static_cast<HWND>(parentHandle.ToPointer()));
		return IntPtr(m_hwnd);
	}
}
