#pragma once
#include "DhGLRenderer.h"

using namespace System;

namespace MathGL {
	public ref class GLRenderer
	{
		public:
		GLRenderer();
		~GLRenderer();

		void Initialize(IntPtr hwnd);
	private:
		DhGLRenderer* ImpObj;
	};
}


