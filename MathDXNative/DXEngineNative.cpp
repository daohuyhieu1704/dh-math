#include "pch.h"
#include "windowsx.h"
#include "DXEngineNative.h"

DXEngineNative* DXEngineNative::m_instance = nullptr;

LRESULT DXEngineNative::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static UINT_PTR timerID = 1;
    static DWORD lastMouseMove = 0;
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
        int width = LOWORD(lParam);
        int height = HIWORD(lParam);
        SetWindowPos(hwnd, NULL, 0, 0, width, height, SWP_NOZORDER | SWP_NOMOVE);
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
    }
    return 0;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

HWND DXEngineNative::InitializeWindow(HINSTANCE hInstance, int nCmdShow, HWND parentHwnd)
{
    const wchar_t CLASS_NAME[] = L"DirectXWindowClass";

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
        L"Drawing App",        // Window text
        WS_SYSMENU | WS_VISIBLE | WS_MINIMIZEBOX | WS_OVERLAPPED | WS_BORDER | WS_CAPTION |
        WS_CLIPCHILDREN | WS_CLIPSIBLINGS,         // Window style - make it a child window that is visible
        70, 220, width - 240, height - 20,                // Position and dimensions
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

HRESULT DXEngineNative::InitializeCore(HWND hwnd)
{
    return 0;
}

void DXEngineNative::ResizeWindow(HWND hwnd, int width, int height)
{
    SetWindowPos(hwnd, NULL, 0, 0, width, height, SWP_NOZORDER | SWP_NOMOVE);
}