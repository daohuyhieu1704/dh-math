#pragma once
#include "pch.h"
#include "DXEngineNative.h"

using namespace System;

namespace MathDX
{
	public ref class DXEngine
	{
	private:
		HWND m_hwnd;
	public:
		DXEngine();
		~DXEngine();
		IntPtr InitializeWindow(IntPtr parentHandle);
	protected:
		DXEngineNative* m_pEngine;
	};
}
