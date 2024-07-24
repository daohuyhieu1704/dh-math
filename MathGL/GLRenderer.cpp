#include "pch.h"
#include "GLRenderer.h"

MathGL::GLRenderer::GLRenderer()
{
	ImpObj = new DhGLRenderer();
}

MathGL::GLRenderer::~GLRenderer()
{
	delete ImpObj;
}

void MathGL::GLRenderer::Initialize(IntPtr hwnd)
{
	ImpObj->Initialize((HWND)hwnd.ToPointer());
}
