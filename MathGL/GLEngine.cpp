// MathGL.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "GLEngine.h"
#include <msclr/marshal.h>
#include <msclr/marshal_cppstd.h>

namespace MathGL
{
	using namespace MathCore::Geom;
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

	List<Point3d>^ GLEngine::Points::get()
	{
		List<Point3d>^ points = gcnew List<Point3d>(m_pEngine->points.size());
		for (auto& point : m_pEngine->points)
		{
			points->Add(Point3d(point.x, point.y, 0));
		}
		return points;
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
	void GLEngine::AppendCommand(String^ command)
	{
		std::string standardStr = msclr::interop::marshal_as<std::string>(command);
		m_pEngine->AppendCommand(standardStr);
	}
	void GLEngine::CreateSession(String^ fileName)
	{
		std::string standardStr = msclr::interop::marshal_as<std::string>(fileName);
		m_pEngine->CreateSession(standardStr);
	}
	void GLEngine::Undo()
	{
		m_pEngine->Undo();
	}
	void GLEngine::Redo()
	{
		m_pEngine->Redo();
	}
	void GLEngine::AddJig(Jig^ jig)
	{
		m_pEngine->m_jigs.push_back(static_cast<OdJig*>(jig->GetImpObj()));
	}
}
