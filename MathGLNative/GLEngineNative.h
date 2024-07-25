#pragma once
#include "pch.h"
#include "IEngine.h"

class GLEngineNative : public IEngine
{
public:
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	// Inherited via IEngine
	HWND InitializeWindow(HINSTANCE hInstance, int nCmdShow, HWND parentHwnd) override;
	HRESULT InitializeCore(HWND hwnd);

	GLFWwindow* m_window;
	GLuint m_framebuffer;
	GLuint m_texture;
	GLuint m_rbo;
	HWND m_glWindow;
	HDC m_hdc;
	HGLRC m_hglrc;
};

