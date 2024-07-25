#include "pch.h"
#include "GLEngineNative.h"

LRESULT GLEngineNative::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
    case WM_LBUTTONDOWN:
    {
        break;
    }
    case WM_MOUSEMOVE:
    {
        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_SIZE:
    {
        break;
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
        break;
    }
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        BeginPaint(hwnd, &ps);
        EndPaint(hwnd, &ps);
        break;
    }
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

HWND GLEngineNative::InitializeWindow(HINSTANCE hInstance, int nCmdShow, HWND parentHwnd) {
    const wchar_t CLASS_NAME[] = L"GLWindowClass";

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
        0, 0, width, height,           // Position and dimensions
        parentHwnd,                    // Parent window    
        NULL,                          // Menu
        hInstance,                     // Instance handle
        NULL                           // Additional application data
    );

    if (hwnd == NULL) {
        return NULL;
    }

    ShowWindow(hwnd, nCmdShow);
    InitializeCore(hwnd);
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

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    return S_OK;
}
