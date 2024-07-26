#pragma once
#include "pch.h"
#include "GLEngineNative.h"

using namespace System;

namespace MathGL
{
	public ref class GLEngine
	{
	private:
		static GLEngine^ m_instance;
		HWND m_hwnd;
		GLEngine();
		~GLEngine();
	public:
		delegate IntPtr InitializeWindowDelegate(IntPtr parentHandle);
		static property GLEngine^ Instance
		{
			GLEngine^ get()
			{
				if (m_instance == nullptr)
				{
					m_instance = gcnew GLEngine();
				}
				return m_instance;
			}
		}

		IntPtr InitializeWindow(IntPtr parentHandle);
	protected:
		GLEngineNative* m_pEngine;
	};
}

