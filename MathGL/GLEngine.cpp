// MathGL.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "GLEngine.h"

namespace MathGL
{
	GLEngine::GLEngine() : m_pEngine(GLEngineNative::GetInstance())
	{
	}
	GLEngine::~GLEngine()
	{
		delete m_pEngine;
	}

	IntPtr GLEngine::InitializeWindow(IntPtr parentHandle)
	{
		HINSTANCE hInstance = GetModuleHandle(nullptr);
		m_hwnd = m_pEngine->InitializeWindow(hInstance, SW_SHOW, static_cast<HWND>(parentHandle.ToPointer()));
		return IntPtr(m_hwnd);
	}
}
