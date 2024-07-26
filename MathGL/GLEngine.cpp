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

	void GLEngine::TLViewport()
	{
		m_pEngine->TLViewport();
	}

	void GLEngine::TMViewport()
	{
		m_pEngine->TMViewport();
	}

	void GLEngine::TRViewport()
	{
		m_pEngine->TRViewport();
	}

	void GLEngine::MLViewport()
	{
		m_pEngine->MLViewport();
	}

	void GLEngine::TMMViewport()
	{
		m_pEngine->TMMViewport();
	}

	void GLEngine::BMMViewport()
	{
		m_pEngine->BMMViewport();
	}

	void GLEngine::MRViewport()
	{
		m_pEngine->MRViewport();
	}

	void GLEngine::BLViewport()
	{
		m_pEngine->BLViewport();
	}

	void GLEngine::BMViewport()
	{
		m_pEngine->BMViewport();
	}

	void GLEngine::BRViewport()
	{
		m_pEngine->BRViewport();
	}
}
