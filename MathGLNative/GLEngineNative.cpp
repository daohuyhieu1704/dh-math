#include "pch.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "GLEngineNative.h"
#include <corecrt_math.h>
#include "MathLine.h"
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "APIGLConverter.h"
#include <glm/gtc/type_ptr.hpp>
#include <MathLog.h>
#include "GLCircle.h"
#include "GLNativeConverter.h"

GLEngineNative* GLEngineNative::m_instance = nullptr;
POINT prevMousePos;

//std::string LoadShaderSource(const std::string& filePath)
//{
//    std::ifstream shaderFile(filePath);
//    if (!shaderFile.is_open())
//    {
//        MathLog::LogFunction("Failed to open shader file: " + filePath);
//        return "";
//    }
//
//    std::stringstream shaderStream;
//    shaderStream << shaderFile.rdbuf();
//    shaderFile.close();
//    return shaderStream.str();
//}
//
//GLuint CompileShader(const std::string& source, GLenum shaderType)
//{
//    const char* sourceCStr = source.c_str();
//    GLuint shaderID = glCreateShader(shaderType);
//    glShaderSource(shaderID, 1, &sourceCStr, nullptr);
//    glCompileShader(shaderID);
//
//    GLint success;
//    GLchar infoLog[512];
//    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
//    if (!success)
//    {
//        glGetShaderInfoLog(shaderID, 512, nullptr, infoLog);
//        std::string logMessage(infoLog);
//        MathLog::LogFunction("ERROR::SHADER::COMPILATION_FAILED" + logMessage);
//    }
//
//    return shaderID;
//}
//
//GLuint CreateShaderProgram()
//{
//    GLuint vertexShader = CompileShader("../directional_shadow_map.vert", GL_VERTEX_SHADER);
//    GLuint fragmentShader = CompileShader("../Shaders/directional_shadow_map.frag", GL_FRAGMENT_SHADER);
//
//    GLuint shaderProgram = glCreateProgram();
//    glAttachShader(shaderProgram, vertexShader);
//    glAttachShader(shaderProgram, fragmentShader);
//    glLinkProgram(shaderProgram);
//
//    // Check for linking errors
//    GLint success;
//    GLchar infoLog[512];
//    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
//    if (!success)
//    {
//        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
//
//        std::string logMessage(infoLog);
//        MathLog::LogFunction("ERROR::SHADER::PROGRAM::LINKING_FAILED" + logMessage);
//    }
//
//    glDeleteShader(vertexShader);
//    glDeleteShader(fragmentShader);
//
//    return shaderProgram;
//}

LRESULT GLEngineNative::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    GLEngineNative* engineNative = GLEngineNative::GetInstance();
    switch (uMsg) {
    case WM_CREATE:
    {
        HGDIOBJ hfDefault = GetStockObject(DEFAULT_GUI_FONT);
        SendMessage(engineNative->m_glWindow,
            WM_SETFONT,
            (WPARAM)hfDefault,
            MAKELPARAM(FALSE, 0));
        SendMessage(engineNative->m_glWindow,
            WM_SETTEXT,
            NULL,
            (LPARAM)"Length");
        return 0;
    }
    case WM_MOUSEWHEEL:
    {
        int delta = GET_WHEEL_DELTA_WPARAM(wParam);
        if (delta > 0)
        {
            engineNative->zoomFactor -= 1.0f; // Zoom in
        }
        else
        {
            engineNative->zoomFactor += 1.0f; // Zoom out
        }

        RECT rect;
        GetClientRect(hwnd, &rect);
        engineNative->ResizeChild(rect.right - rect.left, rect.bottom - rect.top);
        return 0;
    }
    case WM_MOUSEMOVE:
    {
        if (engineNative->isDragging)
        {
            int x = LOWORD(lParam);
            int y = HIWORD(lParam);

            float dx = static_cast<float>(x - prevMousePos.x);
            float dy = static_cast<float>(y - prevMousePos.y);

            engineNative->MoveCamera(dx, dy);

            prevMousePos.x = x;
            prevMousePos.y = y;

            RECT rect;
            GetClientRect(hwnd, &rect);
            engineNative->Setup3DViewport(rect.right - rect.left, rect.bottom - rect.top);
            InvalidateRect(hwnd, nullptr, FALSE);
        }
        return 0;
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_SIZE:
    {
        int width = LOWORD(lParam);
        int height = HIWORD(lParam);
        // engineNative->ResizeChild(width, height);
        return 0;
    }
    case WM_DPICHANGED:
    {
        RECT* const prcNewWindow = (RECT*)lParam;
        SetWindowPos(hwnd,
            NULL,
            prcNewWindow->left,
            prcNewWindow->top,
            prcNewWindow->right - prcNewWindow->left,
            prcNewWindow->bottom - prcNewWindow->top,
            SWP_NOZORDER | SWP_NOACTIVATE);
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        BeginPaint(hwnd, &ps);
        EndPaint(hwnd, &ps);

        RECT rect;
        GetClientRect(hwnd, &rect);
		engineNative->Setup3DViewport(rect.right - rect.left, rect.bottom - rect.top);
        int width = rect.right - rect.left;
        int height = rect.bottom - rect.top;
        engineNative->RenderScene();
        SwapBuffers(engineNative->m_hdc);
        return 0;
    }
    break;
    case WM_LBUTTONDOWN:
    {
        engineNative->isDragging = true;

        prevMousePos.x = LOWORD(lParam);
        prevMousePos.y = HIWORD(lParam);

        GLint viewport[4];
        GLdouble modelview[16];
        GLdouble projection[16];
        GLfloat winX, winY, winZ;
        GLdouble posX, posY, posZ;

        glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
        glGetDoublev(GL_PROJECTION_MATRIX, projection);
        glGetIntegerv(GL_VIEWPORT, viewport);

        winX = (float)prevMousePos.x;
        winY = (float)viewport[3] - (float)prevMousePos.y;
        glReadPixels(prevMousePos.x, (int)winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);

        gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);

        engineNative->points.push_back(OdGePoint2d(posX, posY));

        PostMessage(GetParent(hwnd), WM_MY_MESSAGE, wParam, lParam);
        return 0;
    }
    case WM_LBUTTONUP:
    {
        engineNative->isDragging = false;
        return 0;
    }
    break;
    case WM_SYSCHAR:
        break;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

void GLEngineNative::MoveCamera(float dx, float dy)
{
	m_camPosition = OdGePoint3d(
		m_camPosition.x + dx,
		m_camPosition.y + dy,
		m_camPosition.z
	);
}

void GLEngineNative::Setup3DViewport(int width, int height) {
    glViewport(0, 0, width, height);

    switch (m_viewportType)
    {
    case ViewportType::TL:
    {
        m_camPosition = OdGePoint3d(-10.0, 10.0, 10.0);
    }
    break;
    case ViewportType::TM:
    {
        m_camPosition = OdGePoint3d(0.0, 10.0, 10.0);
    }
    break;
    case ViewportType::TR:
    {
        m_camPosition = OdGePoint3d(10.0, 10.0, 10.0);
    }
    break;
    case ViewportType::ML:
    {
        m_camPosition = OdGePoint3d(-10.0, 0.0, 10.0);
    }
    break;
    case ViewportType::TMM:
    {
        m_camPosition = OdGePoint3d(0.0, 0.0, 10.0);
    }
    break;
    case ViewportType::BMM:
    {
        m_camPosition = OdGePoint3d(0.0, -10.0, 10.0);
    }
    break;
    case ViewportType::MR:
    {
        m_camPosition = OdGePoint3d(10.0, 0.0, 10.0);
    }
    break;
    case ViewportType::BL:
    {
        m_camPosition = OdGePoint3d(-10.0, -10.0, 10.0);
    }
    break;
    case ViewportType::BM:
    {
        m_camPosition = OdGePoint3d(0.0, -10.0, 10.0);
    }
    break;
    case ViewportType::BR:
    {
        m_camPosition = OdGePoint3d(10.0, -10.0, 10.0);
    }
    break;
    default:
        m_camPosition = OdGePoint3d(0.0, 0.0, 10.0);
        break;
    }

	m_camPosition += (m_camPosition - OdGePoint3d(0, 0, 0)).Normalize() * zoomFactor;

    glm::vec3 cameraPos = APIGLConverter::OdGePoint3dToVec3(m_camPosition);
    glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 0.0f, 1.0f);
    glm::mat4 view = glm::lookAt(cameraPos, cameraTarget, cameraUp);

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(projection));

    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(glm::value_ptr(view));
}


void GLEngineNative::Setup2DViewport(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, height, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void GLEngineNative::TLViewport()
{
    zoomFactor = 45.0f;
    m_viewportType = ViewportType::TL;
    int x, y, width, height;
    GetCurrentViewport(x, y, width, height);
    Setup3DViewport(width, height);
}

void GLEngineNative::TMViewport()
{
    zoomFactor = 45.0f;
	m_viewportType = ViewportType::TM;
	int x, y, width, height;
	GetCurrentViewport(x, y, width, height);
	Setup3DViewport(width, height);
}

void GLEngineNative::TRViewport()
{
    zoomFactor = 45.0f;
	m_viewportType = ViewportType::TR;
	int x, y, width, height;
	GetCurrentViewport(x, y, width, height);
	Setup3DViewport(width, height);
}

void GLEngineNative::MLViewport()
{
    zoomFactor = 45.0f;
	m_viewportType = ViewportType::ML;
	int x, y, width, height;
	GetCurrentViewport(x, y, width, height);
	Setup3DViewport(width, height);
}

void GLEngineNative::TMMViewport()
{
    zoomFactor = 45.0f;
    m_viewportType = ViewportType::TMM;
    int x, y, width, height;
    GetCurrentViewport(x, y, width, height);
    Setup3DViewport(width, height);
}

void GLEngineNative::BMMViewport()
{
    zoomFactor = 45.0f;
	m_viewportType = ViewportType::BMM;
	int x, y, width, height;
	GetCurrentViewport(x, y, width, height);
	Setup3DViewport(width, height);
}

void GLEngineNative::MRViewport()
{
    zoomFactor = 45.0f;
	m_viewportType = ViewportType::MR;
	int x, y, width, height;
	GetCurrentViewport(x, y, width, height);
	Setup3DViewport(width, height);
}

void GLEngineNative::BLViewport()
{
    zoomFactor = 45.0f;
	m_viewportType = ViewportType::BL;
	int x, y, width, height;
	GetCurrentViewport(x, y, width, height);
	Setup3DViewport(width, height);
}

void GLEngineNative::BMViewport()
{
    zoomFactor = 45.0f;
	m_viewportType = ViewportType::BM;
	int x, y, width, height;
	GetCurrentViewport(x, y, width, height);
	Setup3DViewport(width, height);
}

void GLEngineNative::BRViewport()
{
    zoomFactor = 45.0f;
	m_viewportType = ViewportType::BR;
	int x, y, width, height;
	GetCurrentViewport(x, y, width, height);
	Setup3DViewport(width, height);
}

void GLEngineNative::RegisterCommandPattern()
{
    m_appServices = OdHostAppService::getInstance();
    LineCmd* lineCmd = new LineCmd();
    m_appServices->getCurrentSession()->getPrompts().registerCommand("LINE", lineCmd);
    CircleCmd* circleCmd = new CircleCmd();
    m_appServices->getCurrentSession()->getPrompts().registerCommand("CIRCLE", circleCmd);
    SquareCmd* squareCmd = new SquareCmd();
    m_appServices->getCurrentSession()->getPrompts().registerCommand("SQUARE", squareCmd);
}

void CreateBitmapFont(HDC hdc) {
    HFONT hFont;
    HFONT hOldFont;

    hFont = CreateFont(
        -12,
        0, 0, 0,
        FW_NORMAL, FALSE, FALSE, FALSE,
        ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS,
        ANTIALIASED_QUALITY, FF_DONTCARE | DEFAULT_PITCH,
        L"Courier New"
    );

    hOldFont = (HFONT)SelectObject(hdc, hFont);
    wglUseFontBitmaps(hdc, 0, 256, 1000);
    SelectObject(hdc, hOldFont);
    DeleteObject(hFont);
}

void RenderText(const char* text) {
    glPushAttrib(GL_LIST_BIT);
    glListBase(1000);
    glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);
    glPopAttrib();
}

void GLEngineNative::drawGridXZ(float size, float step)
{
    // disable lighting
    glDisable(GL_LIGHTING);

    glBegin(GL_LINES);

    glColor4f(0.5f, 0.5f, 0.5f, 0.5f);
    for (float i = step; i <= size; i += step)
    {
        glVertex3f(-size, 0, i);   // lines parallel to X-axis
        glVertex3f(size, 0, i);
        glVertex3f(-size, 0, -i);   // lines parallel to X-axis
        glVertex3f(size, 0, -i);

        glVertex3f(i, 0, -size);   // lines parallel to Z-axis
        glVertex3f(i, 0, size);
        glVertex3f(-i, 0, -size);   // lines parallel to Z-axis
        glVertex3f(-i, 0, size);
    }

    // x-axis
    glColor3f(1, 0, 0);
    glVertex3f(-size, 0, 0);
    glVertex3f(size, 0, 0);

    // z-axis
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, -size);
    glVertex3f(0, 0, size);

    glEnd();

    // enable lighting back
    glEnable(GL_LIGHTING);
}


void GLEngineNative::drawGridXY(float size, float step)
{
    glDisable(GL_LIGHTING);

    glBegin(GL_LINES);

    glColor4f(0.5f, 0.5f, 0.5f, 0.5f);
    for (float i = step; i <= size; i += step)
    {
        glVertex3f(-size, i, 0);   // lines parallel to X-axis
        glVertex3f(size, i, 0);
        glVertex3f(-size, -i, 0);   // lines parallel to X-axis
        glVertex3f(size, -i, 0);

        glVertex3f(i, -size, 0);   // lines parallel to Y-axis
        glVertex3f(i, size, 0);
        glVertex3f(-i, -size, 0);   // lines parallel to Y-axis
        glVertex3f(-i, size, 0);
    }

    glColor3f(1, 0, 0);
    glVertex3f(-size, 0, 0);
    glVertex3f(size, 0, 0);

    // y-axis
    glColor3f(0, 1, 0);
    glVertex3f(0, -size, 0);
    glVertex3f(0, size, 0);

    glEnd();

    glEnable(GL_LIGHTING);
}

void GLEngineNative::drawAxis(float size)
{
    glDepthFunc(GL_ALWAYS);     // to avoid visual artifacts with grid lines
    glDisable(GL_LIGHTING);

    glLineWidth(5);
    glBegin(GL_LINES);
    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(size, 0, 0);
    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, size, 0);
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, size);
    glEnd();
    glLineWidth(1);

    glPointSize(10);
    glBegin(GL_POINTS);
    glColor3f(1, 0, 0);
    glVertex3f(size, 0, 0);
    glColor3f(0, 1, 0);
    glVertex3f(0, size, 0);
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, size);
    glEnd();
    glPointSize(1);

    glEnable(GL_LIGHTING);
    glDepthFunc(GL_LEQUAL);
}

void GLEngineNative::Draw3DGrid(float size, float step)
{
    glPushMatrix();
    glTranslatef(-size / 2, 0, -size / 2);
    for (float i = 0; i <= size; i += step)
    {
        glBegin(GL_LINES);
        glColor3f(0.5, 0.5, 0.5);
        glVertex3f(i, 0, 0);
        glVertex3f(i, 0, size);
        glVertex3f(0, 0, i);
        glVertex3f(size, 0, i);
        glEnd();
    }
    glPopMatrix();
}

void GLEngineNative::AddLine(OdGePoint3d startPnt, OdGePoint3d endPnt)
{
	MathLine* line = new MathLine();
	line->setStartPnt(startPnt);
	line->setEndPnt(endPnt);
	m_entities.push_back(line);
}

void GLEngineNative::CreateSession(std::string fileName)
{
	m_appServices->createSession(fileName);
    RegisterCommandPattern();
}

void GLEngineNative::AppendCommand(const std::string command)
{
	m_appServices->getCurrentSession()->getPrompts().appendCommand(command);
    
}

void GLEngineNative::RenderScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

 //   glm::mat4 model = glm::mat4(1.0f);

 //   float radius = 10.0f;
 //   m_camPosition = OdGePoint3d(
 //       radius * cos(glm::radians(angleY)) * cos(glm::radians(angleX)),
 //       radius * sin(glm::radians(angleX)),
 //       radius * sin(glm::radians(angleY)) * cos(glm::radians(angleX))
 //   );

 //   glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);

 //   glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

 //   glm::mat4 view = glm::lookAt(
 //       APIGLConverter::OdGePoint3dToVec3(m_camPosition),
 //       cameraTarget,
 //       cameraUp
 //   );

	//int dx = 0, dy = 0, width = 0, height = 0;
	//GetCurrentViewport(dx, dy, width, height);
 //   glm::mat4 projection = glm::perspective(
 //       glm::radians(45.0f),
 //       (float)width / (float)height,
 //       0.1f,
 //       100.0f
 //   );

    //GLuint shaderProgram = CreateShaderProgram();
    //glUseProgram(shaderProgram);
    //GLuint modelLoc = glGetUniformLocation(shaderProgram, "model");
    //GLuint viewLoc = glGetUniformLocation(shaderProgram, "view");
    //GLuint projLoc = glGetUniformLocation(shaderProgram, "projection");

    //glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    //glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    //glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

    // Draw3DGrid(100, 1);
    drawAxis();                         // for origin (0,0,0)
    // drawGridXZ(20);                     // draw XZ-grid at origin (world space)
    drawGridXY(20);                     // draw XY-grid at origin (world space)
    // RenderCube(10, 10);

    for (OdDbEntity* ent : m_entities)
    {
        if (ent != nullptr)
        {
            OdDrawable* drawable = static_cast<OdDrawable*>(ent);
            if (drawable != nullptr && drawable->m_renderMethod != nullptr)
            {
				drawable->m_renderMethod->render();
            }
        }
    }
    for (RenderEntity* ent : m_tempRenders)
    {
        if (ent != nullptr)
        {
			ent->render();
        }
    }
}

bool RayIntersectsSphere(glm::vec3 rayOrigin, glm::vec3 rayDirection, glm::vec3 sphereCenter, float sphereRadius, float& intersectionDistance)
{
    glm::vec3 oc = rayOrigin - sphereCenter;
    float a = glm::dot(rayDirection, rayDirection);
    float b = 2.0f * glm::dot(oc, rayDirection);
    float c = glm::dot(oc, oc) - sphereRadius * sphereRadius;
    float discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
    {
        return false;  // No intersection
    }
    else
    {
        discriminant = sqrt(discriminant);
        float t1 = (-b - discriminant) / (2.0f * a);
        float t2 = (-b + discriminant) / (2.0f * a);

        intersectionDistance = (t1 < t2) ? t1 : t2;
        return true;  // Intersection occurs
    }
}

void CalculateRay(int mouseX, int mouseY, int screenWidth, int screenHeight, glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::vec3& rayOrigin, glm::vec3& rayDirection)
{
    // Convert mouse coordinates to normalized device coordinates (NDC)
    float x = (2.0f * mouseX) / screenWidth - 1.0f;
    float y = 1.0f - (2.0f * mouseY) / screenHeight;
    float z = 1.0f;  // In NDC, we start with z = 1.0 for ray direction

    glm::vec3 rayNDC(x, y, z);

    // Convert from NDC to clip coordinates
    glm::vec4 rayClip(rayNDC.x, rayNDC.y, -1.0f, 1.0f);

    // Convert from clip coordinates to eye coordinates
    glm::vec4 rayEye = glm::inverse(projectionMatrix) * rayClip;
    rayEye = glm::vec4(rayEye.x, rayEye.y, -1.0f, 0.0f);  // We set w = 0.0 to represent a direction vector

    // Convert from eye coordinates to world coordinates
    glm::vec4 rayWorld = glm::inverse(viewMatrix) * rayEye;
    rayDirection = glm::normalize(glm::vec3(rayWorld));

    // Ray origin is the camera position
    rayOrigin = glm::vec3(glm::inverse(viewMatrix)[3]);
}

bool GLEngineNative::SelectEntity(int mouseX, int mouseY, int screenWidth, int screenHeight, glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
{
	if (m_entities.size() == 0)
    {
		return false;
	}

    glm::vec3 rayOrigin, rayDirection;
    CalculateRay(mouseX, mouseY, screenWidth, screenHeight, viewMatrix, projectionMatrix, rayOrigin, rayDirection);

    float closestDistance = FLT_MAX;
	OdDbEntity* selectedEntity = nullptr;
    for (auto& entity : m_entities)
    {
        float intersectionDistance;
        if (RayIntersectsSphere(rayOrigin, rayDirection, APIGLConverter::OdGePoint3dToVec3(entity->GetPosition()), entity->getSphereRadius(), intersectionDistance))
        {
            if (intersectionDistance < closestDistance)
            {
                closestDistance = intersectionDistance;
                selectedEntity = entity;
            }
        }
    }

    for (auto& entity : m_entities)
    {
		if (entity == selectedEntity)
		{
			entity->setIsSelected(true);
		}
		else
		{
			entity->setIsSelected(false);
		}
    }

    return selectedEntity == nullptr;
}

void GLEngineNative::GetCurrentViewport(int& x, int& y, int& width, int& height)
{
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    x = viewport[0];
    y = viewport[1];
    width = viewport[2];
    height = viewport[3];
}

HWND GLEngineNative::InitializeWindow(HINSTANCE hInstance, int nCmdShow, HWND parentHwnd) {
    if (!glfwInit()) {
        return nullptr;
    }

    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

    const wchar_t CLASS_NAME[] = L"GLWindowClass";
    BOOL quit = FALSE;

    // Register the window class.
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));

    RegisterClass(&wc);

    RECT rc{};
    GetClientRect(parentHwnd, &rc);
    LONG width = rc.right - rc.left;
    LONG height = rc.bottom - rc.top;

    // Create the window.
    HWND hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,              // Extended window styles.
        CLASS_NAME,                    // Window class
        L"Drawing App",                // Window text
        WS_CHILD | WS_VISIBLE,         // Window style - make it a child window that is visible
        210, 160, width - 220, height - 320,           // Position and dimensions
        parentHwnd,                    // Parent window    
        NULL,                          // Menu
        hInstance,                     // Instance handle
        NULL                           // Additional application data
    );

    if (hwnd == NULL) {
        return NULL;
    }

	EnableOpenGL(hwnd, &m_hdc, &m_hglrc);
	m_glWindow = hwnd;
    MSG msg;

    while (!quit)
    {
        if (pointPicked)
        {
            PickPoint();
        }
        if (isSelectMode)
		{
			SelectEntityHandle();
		}
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                quit = TRUE;
            }
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            RenderScene();
            SwapBuffers(m_hdc);
            glfwPollEvents();
        }
    }

    DisableOpenGL(hwnd, m_hdc, m_hglrc);
    DestroyWindow(hwnd);
    return hwnd;
}

void GLEngineNative::PickPoint()
{
    MSG msg;
    GLCircle* circle = new GLCircle();
	GLLine* line = new GLLine();
    m_tempRenders.push_back(circle);
    m_tempRenders.push_back(line);

    for (OdJig* jig : m_jigs)
    {
        jig->Preview();
    }

    while (pointPicked && m_totalPick >= points.size())
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                PostQuitMessage(0);
                return;
            }
            else
            {
                int mouseX = LOWORD(msg.lParam);
                int mouseY = HIWORD(msg.lParam);

                GLint viewport[4];
                GLdouble modelview[16];
                GLdouble projection[16];
                GLfloat winX, winY, winZ;
                GLdouble posX, posY, posZ;

                glGetIntegerv(GL_VIEWPORT, viewport);
                glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
                glGetDoublev(GL_PROJECTION_MATRIX, projection);

                winX = (float)mouseX;
                winY = (float)viewport[3] - (float)mouseY;
                glReadPixels(mouseX, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);

                gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);
                OdGePoint3d projectPoint = OdGePoint3d(posX, posY, 0);
                if (msg.message == WM_LBUTTONDOWN)
                {

                    points.push_back(projectPoint.ConvertTo2d());
                    if (m_totalPick == points.size())
                    {
                        pointPicked = false;
                    }
                }
                else if (msg.message == WM_MOUSEMOVE)
                {
                    circle->setCenter(projectPoint);
                    circle->setRadius(1);

                    if (m_jigs.size() > 0)
					{
						for (OdJig* jig : m_jigs)
						{
                            jig->AcquirePoint(projectPoint);
						}
                    }
                }
                else
                {
                    TranslateMessage(&msg);
                    DispatchMessage(&msg);
                }

                RenderScene();
                SwapBuffers(m_hdc);
                glfwPollEvents();
            }
        }
    }
	TriggerPointPicked(points);

	for (OdJig* jig : m_jigs)
	{
        m_tempRenders.pop_back();
	}
	m_jigs.clear();
    m_tempRenders.pop_back();
    m_tempRenders.pop_back();
	delete circle;
	delete line;
}

void GLEngineNative::SelectEntityHandle()
{
    MSG msg;
    GLCircle* circle = new GLCircle();
    m_tempRenders.push_back(circle);

    while (isSelectMode)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                PostQuitMessage(0);
                return;
            }
            else
            {
                int mouseX = LOWORD(msg.lParam);
                int mouseY = HIWORD(msg.lParam);

                GLint viewport[4];
                GLdouble modelview[16];
                GLdouble projection[16];
                GLfloat winX, winY, winZ;
                GLdouble posX, posY, posZ;

				int xx, yy, width, height;
				GetCurrentViewport(xx, yy, width, height);

                glGetIntegerv(GL_VIEWPORT, viewport);
                glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
                glGetDoublev(GL_PROJECTION_MATRIX, projection);

                winX = (float)mouseX;
                winY = (float)viewport[3] - (float)mouseY;
                glReadPixels(mouseX, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);

                gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);
                OdGePoint3d projectPoint = OdGePoint3d(posX, posY, 0);
                if (msg.message == WM_LBUTTONDOWN)
                {
                    points.push_back(projectPoint.ConvertTo2d());
                    isSelectMode = SelectEntity(mouseX, mouseY, width, height, GLNativeConverter::ConvertToGlmMat4(modelview), GLNativeConverter::ConvertToGlmMat4(projection));
                }
                else if (msg.message == WM_MOUSEMOVE)
                {
                    circle->setCenter(projectPoint);
                    circle->setRadius(1);
                }
                else
                {
                    TranslateMessage(&msg);
                    DispatchMessage(&msg);
                }

                RenderScene();
                SwapBuffers(m_hdc);
                glfwPollEvents();
            }
        }
    }
    TriggerEntityPicked();
    m_tempRenders.pop_back();
    delete circle;
}

void GLEngineNative::SetPointPickedCallback(PointPickedCallback callback)
{
    pointPickedCallback = callback;
}

void GLEngineNative::TriggerPointPicked(std::vector<OdGePoint2d> resPnt) {
    if (pointPickedCallback) {
        pointPickedCallback(resPnt);
    }
}

void GLEngineNative::SetEntityPickedCallback(EntityPickedCallback callback)
{
    entityPickedCallback = callback;
}

void GLEngineNative::TriggerEntityPicked() {
    if (entityPickedCallback) {
        entityPickedCallback();
    }
}

void GLEngineNative::Undo()
{
	m_appServices->getCurrentSession()->undo();
	m_entities.clear();
    m_appServices->getCurrentSession()->ExecuteAllPrompts();
}

void GLEngineNative::Redo()
{
	m_appServices->getCurrentSession()->redo();
    m_entities.clear();
    m_appServices->getCurrentSession()->ExecuteAllPrompts();
}

void GLEngineNative::ResizeChild(int width, int height)
{
    if (height == 0)
        height = 1;
	Setup3DViewport(width, height);
    //glViewport(0, 0, width, height);

    //glMatrixMode(GL_PROJECTION);
    //glLoadIdentity();

    //glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();
}

HRESULT GLEngineNative::InitializeCore(HWND hwnd)
{
    m_hdc = GetDC(hwnd);
    if (!m_hdc) return E_FAIL;

    PIXELFORMATDESCRIPTOR pfd = {
        sizeof(PIXELFORMATDESCRIPTOR),
        1,
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
        PFD_TYPE_RGBA,
        32,
        0, 0, 0, 0, 0, 0,
        0,
        0,
        0,
        0, 0, 0, 0,
        24,
        8,
        0,
        PFD_MAIN_PLANE,
        0,
        0, 0, 0
    };

    int pixelFormat = ChoosePixelFormat(m_hdc, &pfd);
    if (pixelFormat == 0) return E_FAIL;

    if (!SetPixelFormat(m_hdc, pixelFormat, &pfd)) return E_FAIL;

    m_hglrc = wglCreateContext(m_hdc);
    if (!m_hglrc) return E_FAIL;

    if (!wglMakeCurrent(m_hdc, m_hglrc)) return E_FAIL;
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_TEXTURE_2D);

    return S_OK;
}

void GLEngineNative::RenderCube(int windowWidth, int windowHeight)
{
    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    float halfWidth = static_cast<float>(windowWidth) / 2.0f;
    float halfHeight = static_cast<float>(windowHeight) / 2.0f;
    float size = halfWidth / 2.0f;
    glBegin(GL_QUADS);

    // Front face
    glColor3f(1.0f, 0.0f, 0.0f); // Red
    glVertex3f(-size, -size, size);
    glVertex3f(size, -size, size);
    glVertex3f(size, size, size);
    glVertex3f(-size, size, size);

    // Back face
    glColor3f(0.0f, 1.0f, 0.0f); // Green
    glVertex3f(-size, -size, -size);
    glVertex3f(-size, size, -size);
    glVertex3f(size, size, -size);
    glVertex3f(size, -size, -size);

    // Top face
    glColor3f(0.0f, 0.0f, 1.0f); // Blue
    glVertex3f(-size, size, -size);
    glVertex3f(-size, size, size);
    glVertex3f(size, size, size);
    glVertex3f(size, size, -size);

    // Bottom face
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
    glVertex3f(-size, -size, -size);
    glVertex3f(size, -size, -size);
    glVertex3f(size, -size, size);
    glVertex3f(-size, -size, size);

    // Right face
    glColor3f(0.0f, 1.0f, 1.0f); // Cyan
    glVertex3f(size, -size, -size);
    glVertex3f(size, size, -size);
    glVertex3f(size, size, size);
    glVertex3f(size, -size, size);

    // Left face
    glColor3f(1.0f, 0.0f, 1.0f); // Magenta
    glVertex3f(-size, -size, -size);
    glVertex3f(-size, -size, size);
    glVertex3f(-size, size, size);
    glVertex3f(-size, size, -size);

    glEnd();
}

void GLEngineNative::EnableOpenGL(HWND hWnd, HDC* hDC, HGLRC* hRC)
{
    PIXELFORMATDESCRIPTOR pfd;
    int format;

    *hDC = GetDC(hWnd);

    ZeroMemory(&pfd, sizeof(pfd));
    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;
    format = ChoosePixelFormat(*hDC, &pfd);
    SetPixelFormat(*hDC, format, &pfd);

    *hRC = wglCreateContext(*hDC);
    wglMakeCurrent(*hDC, *hRC);

    glShadeModel(GL_SMOOTH);                    // shading mathod: GL_SMOOTH or GL_FLAT
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);      // 4-byte pixel alignment

    // enable /disable features
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_CULL_FACE);

    // enable /disable features
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LINE_SMOOTH);

    // track material ambient and diffuse from surface color, call it before glEnable(GL_COLOR_MATERIAL)
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    glClearColor(0, 0, 0, 0);                   // background color
    glClearStencil(0);                          // clear stencil buffer
    glClearDepth(1.0f);                         // 0 is near, 1 is far
    glDepthFunc(GL_LEQUAL);

    initLights();
}

void GLEngineNative::DisableOpenGL(HWND hWnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hRC);
    ReleaseDC(hWnd, hDC);
}
