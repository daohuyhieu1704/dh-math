// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H
#define GLFW_EXPOSE_NATIVE_WGL
#define GLFW_EXPOSE_NATIVE_WIN32

#define IDC_MAIN_EDIT 102 
#define MATH_PI 3.14159265358979323846
// add headers that you want to pre-compile here
#include "framework.h"
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#define WM_MY_MESSAGE (WM_USER + 1)
#endif //PCH_H
