#include "pch.h"
#include "GLEngineNative.h"


GLEngineNative* GLEngineNative::m_instance = nullptr;

LRESULT GLEngineNative::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
    case WM_CREATE:
    {
        GLEngineNative* engineNative = GLEngineNative::GetInstance();
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
        break;
    case WM_MOUSEMOVE:
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_SIZE:
    {
        int width = LOWORD(lParam);
        int height = HIWORD(lParam);
        glViewport(0, 0, width, height);
		GLEngineNative* engineNative = GLEngineNative::GetInstance();
        if (engineNative) {
            engineNative->RenderCube(width, height);
            SwapBuffers(engineNative->m_hdc);
        }
    }
    break;
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
        int width = rect.right - rect.left;
        int height = rect.bottom - rect.top;
        GLEngineNative* engineNative = GLEngineNative::GetInstance();
        engineNative->RenderCube(width, height);
        SwapBuffers(engineNative->m_hdc);
    }
    break;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

HWND GLEngineNative::InitializeWindow(HINSTANCE hInstance, int nCmdShow, HWND parentHwnd) {
    if (!glfwInit()) {
        return nullptr;
    }

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
        220, 20, width - 240, height - 40,           // Position and dimensions
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
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            glPushMatrix();
            glRotatef(theta, 0.0f, 0.0f, 1.0f);
            glBegin(GL_TRIANGLES);
            glColor3f(1.0f, 0.0f, 0.0f); glVertex2f(0.0f, 0.25f);
            glColor3f(0.0f, 1.0f, 0.0f); glVertex2f(0.21f, -0.12f);
            glColor3f(0.0f, 0.0f, 1.0f); glVertex2f(-0.21f, -0.12f);
            glEnd();
            glPopMatrix();
            SwapBuffers(m_hdc);
            theta += 1.0f;

        }

    }

    DisableOpenGL(hwnd, m_hdc, m_hglrc);
    DestroyWindow(hwnd);
    return hwnd;
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
