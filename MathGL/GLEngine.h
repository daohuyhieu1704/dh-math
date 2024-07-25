#pragma once
#include "pch.h"
#include "GLEngineNative.h"

using namespace System;

namespace MathGL
{
	public ref class GLEngine
	{
	private:
		HWND m_hwnd;
	public:
		GLEngine();
		~GLEngine();
		IntPtr InitializeWindow(IntPtr parentHandle);
	protected:
		GLEngineNative* m_pEngine;
	};
}

