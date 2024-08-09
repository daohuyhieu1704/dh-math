#pragma once
#include "pch.h"
#include "GLEngineNative.h"
#include "Point3d.h"
#include <Jig.h>

using namespace System;
using namespace MathCore;
using namespace MathCore::Geom;
using namespace System::Collections::Generic;

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
		property List<Point3d>^ Points
		{
			List<Point3d>^ get();
		}

		property double ZoomFactor
		{
			double get()
			{
				return m_pEngine->zoomFactor;
			}
			void set(double value)
			{
				m_pEngine->zoomFactor = value;
			}
		}

		property String^ CurrentFilePath
		{
			String^ get()
			{
				return gcnew String(m_pEngine->GetCurrentFilePath().c_str());
			}
		}
		property List<String^>^ History
		{
			List<String^>^ get()
			{
				List<String^>^ history = gcnew List<String^>(m_pEngine->getHistorySize());
				for (auto& command : m_pEngine->getHistory())
				{
					history->Add(gcnew String(command.c_str()));
				}
				return history;
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
		void CreateSession(String^ fileName);
		void AppendCommand(String^ command);
		void AddJig(Jig^ jig);
		void Undo();
		void Redo();
	protected:
		GLEngineNative* m_pEngine;
	};
}

