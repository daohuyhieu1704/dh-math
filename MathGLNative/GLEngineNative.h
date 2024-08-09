#pragma once
#include "pch.h"
#include "IEngine.h"
#include <vector>
#include <RenderEntity.h>
#include <OdGePoint3d.h>
#include <OdHostAppService.h>
#include <string>
#include "LineCmd.h"
#include "CircleCmd.h"
#include "SquareCmd.h"
#include <OdJig.h>
#include "glm/glm.hpp"

using namespace Geometry;

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

using PointPickedCallback = void(*)(std::vector<Geometry::OdGePoint2d> resPnt);

class GLEngineNative : public IEngine
{
	static GLEngineNative* m_instance;
	OdHostAppService* m_appServices;
public:
	std::vector<OdDbEntity*> m_entities;
	std::vector<RenderEntity*> m_tempRenders;
	std::vector<OdJig*> m_jigs;
	static GLEngineNative* GetInstance()
	{
		if (m_instance == nullptr)
		{
			m_instance = new GLEngineNative();
		}
		return m_instance;
	}
	GLEngineNative() : m_window(nullptr), m_framebuffer(0), m_texture(0), m_rbo(0), m_glWindow(nullptr), m_hdc(nullptr), m_hglrc(nullptr) 
	{
		RegisterCommandPattern();
	}
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	// Inherited via IEngine
	HWND InitializeWindow(HINSTANCE hInstance, int nCmdShow, HWND parentHwnd) override;
	void PickPoint();
	void ResizeChild(int width, int height);
	HRESULT InitializeCore(HWND hwnd);
	void RenderCube(int windowWidth, int windowHeight);
	void EnableOpenGL(HWND hWnd, HDC* hDC, HGLRC* hRC);
	void DisableOpenGL(HWND hWnd, HDC hDC, HGLRC hRC);


	void drawAxis(float size = 2.5f);
	void drawGridXZ(float size = 10.0f, float step = 1.0f);
	void drawGridXY(float size = 10.0f, float step = 1.0f);
	void Draw3DGrid(float size, float step);

	void AddLine(OdGePoint3d startPnt, OdGePoint3d endPnt);
	void AppendCommand(const std::string command);
	void RegisterCommandPattern();
	void SelectEntity(int mouseX, int mouseY, int screenWidth, int screenHeight, glm::mat4 viewMatrix, glm::mat4 projectionMatrix);
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

	void MoveCamera(float dx, float dy);
	void GetCurrentViewport(int& x, int& y, int& width, int& height);
	void RenderScene();

	void initLights()
	{
		// set up light colors (ambient, diffuse, specular)
		GLfloat lightKa[] = { .2f, .2f, .2f, 1.0f };  // ambient light
		GLfloat lightKd[] = { .7f, .7f, .7f, 1.0f };  // diffuse light
		GLfloat lightKs[] = { 1, 1, 1, 1 };           // specular light
		glLightfv(GL_LIGHT0, GL_AMBIENT, lightKa);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, lightKd);
		glLightfv(GL_LIGHT0, GL_SPECULAR, lightKs);

		// position the light
		float lightPos[4] = { 0, 1, 1, 0 }; // directional light
		glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

		glEnable(GL_LIGHT0);                        // MUST enable each light source after configuration
	}

	void SetPointPickedCallback(PointPickedCallback callback);
	void TriggerPointPicked(std::vector<OdGePoint2d> resPnt);

	bool pointPicked = false;
	int m_totalPick = 1;
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
	std::vector<OdGePoint2d> points;
	OdGePoint3d m_camPosition;
private:
	PointPickedCallback pointPickedCallback = nullptr;
};

