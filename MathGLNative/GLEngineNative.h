#pragma once
#include "pch.h"
#include "IEngine.h"

class GLEngineNative : public IEngine
{
	static GLEngineNative* m_instance;
public:
	static GLEngineNative* GetInstance()
	{
		if (m_instance == nullptr)
		{
			m_instance = new GLEngineNative();
		}
		return m_instance;
	}
	GLEngineNative() : m_window(nullptr), m_framebuffer(0), m_texture(0), m_rbo(0), m_glWindow(nullptr), m_hdc(nullptr), m_hglrc(nullptr) {}
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	// Inherited via IEngine
	HWND InitializeWindow(HINSTANCE hInstance, int nCmdShow, HWND parentHwnd) override;
	HRESULT InitializeCore(HWND hwnd);
	void RenderCube(int windowWidth, int windowHeight);
	void EnableOpenGL(HWND hWnd, HDC* hDC, HGLRC* hRC);
	void DisableOpenGL(HWND hWnd, HDC hDC, HGLRC hRC);

	GLFWwindow* m_window;
	GLuint m_framebuffer;
	GLuint m_texture;
	GLuint m_rbo;
	HWND m_glWindow;
	HDC m_hdc;
	HGLRC m_hglrc;
	float theta = 0.0f;
};

