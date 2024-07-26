// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

// add headers that you want to pre-compile here
#include "framework.h"
#include <Windows.h>
#include <d3d11.h>
#include <d2d1.h>
#include <d2d1helper.h>
#include <DirectXMath.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d2d1.lib")

#define MAX_NAME_LENGTH 256
#define WM_MY_MESSAGE (WM_USER + 1)
#define HInstance() GetModuleHandle(NULL)


#endif //PCH_H
