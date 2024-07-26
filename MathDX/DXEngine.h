#pragma once
#include "pch.h"
#include "DXEngineNative.h"

using namespace System;

namespace MathDX
{
	public ref class DXEngine
	{
	private:
		static DXEngine^ m_instance;
		HWND m_hwnd;
		DXEngine();
		~DXEngine();
	public:
		static property DXEngine^ Instance
		{
			DXEngine^ get()
			{
				if (m_instance == nullptr)
				{
					m_instance = gcnew DXEngine();
				}
				return m_instance;
			}
		}
		IntPtr InitializeWindow(IntPtr parentHandle);
	protected:
		DXEngineNative* m_pEngine;
	};
}
