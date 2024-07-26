#include "pch.h"
#include "GLEngineNative.h"


GLEngineNative* GLEngineNative::m_instance = nullptr;

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

    case WM_LBUTTONDOWN:
    {
    }
    break;
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
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_SIZE:
    {
        int width = LOWORD(lParam);
        int height = HIWORD(lParam);
        engineNative->ResizeChild(width, height);
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
    case WM_SYSCHAR:
        break;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

void GLEngineNative::Setup3DViewport(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLdouble)width / (GLdouble)height, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
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

void GLEngineNative::RenderScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -5.0f);
    // Rotate the cube
    glRotatef(45, 1.0f, 1.0f, 1.0f);

    glBegin(GL_QUADS);
    // Front face (z = 1.0f)
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);

    // Back face (z = -1.0f)
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);

    // Top face (y = 1.0f)
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);

    // Bottom face (y = -1.0f)
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);

    // Right face (x = 1.0f)
    glColor3f(1.0f, 0.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);

    // Left face (x = -1.0f)
    glColor3f(0.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);

    glEnd();

    // theta += 1.0f;
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
        220, 70, width - 240, height - 90,           // Position and dimensions
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

void GLEngineNative::ResizeChild(int width, int height)
{
    if (height == 0)
        height = 1;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(zoomFactor, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
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
}

void GLEngineNative::DisableOpenGL(HWND hWnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hRC);
    ReleaseDC(hWnd, hDC);
}
