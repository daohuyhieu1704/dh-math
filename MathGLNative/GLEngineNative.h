#pragma once
#include "pch.h"
#include "IEngine.h"

enum class ViewportType
{
	TL = 0,
	TM = 1,
	TR = 2,
	ML = 3,
	TMM = 4,
	BMM = 5,
	MR = 6,
	BL = 7,
	BM = 8,
	BR = 9
};

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
	void ResizeChild(int width, int height);
	HRESULT InitializeCore(HWND hwnd);
	void RenderCube(int windowWidth, int windowHeight);
	void EnableOpenGL(HWND hWnd, HDC* hDC, HGLRC* hRC);
	void DisableOpenGL(HWND hWnd, HDC hDC, HGLRC hRC);
	void Draw3DGrid(float size, float step);

	// Viewport functions
#pragma region Viewport
	void Setup3DViewport(int width, int height);
	void Setup2DViewport(int width, int height);
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
#pragma endregion

	void GetCurrentViewport(int& x, int& y, int& width, int& height);
	void RenderScene();

	GLFWwindow* m_window;
	GLuint m_framebuffer;
	GLuint m_texture;
	GLuint m_rbo;
	HWND m_glWindow;
	HDC m_hdc;
	HGLRC m_hglrc;
	float theta = 0.0f;
	float zoomFactor = 45.0f;
	float angleX = 45.0f, angleY = 45.0f;
	bool is3D = true;
	int lastMouseX, lastMouseY;
	bool isDragging = false;
	ViewportType m_viewportType = ViewportType::TL;
};

