#pragma once
#include <Windows.h>
#include <GL/glew.h>
#include <gl/GL.h>
#include <GLFW/glfw3.h>

class DhGLRenderer
{
public:
    DhGLRenderer();
    ~DhGLRenderer();

    void Initialize(HWND hwnd);
    void Render();
    void Resize(int width, int height);

private:
    HGLRC hglrc;
    HDC hdc;
    HWND hwnd;

    void SetupPixelFormat(HDC hdc);
};

