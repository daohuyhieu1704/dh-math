#pragma once
#include "pch.h"
#include "GLEngineNative.h"
#include "Point3d.h"

using namespace System;
using namespace MathCore::Geom;

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
		void TLViewport();
		void TMViewport();
		void TRViewport();
		void MLViewport();
		void TMMViewport();
		void BMMViewport();
		void MRViewport();
		void BLViewport();
		void BMViewport();
		void BRViewport();
		void AddLine(Point3d startPnt, Point3d endPnt);
	protected:
		GLEngineNative* m_pEngine;
	};
}

