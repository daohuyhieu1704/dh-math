#include "pch.h"
#include "DhGLRenderer.h"

DhGLRenderer::DhGLRenderer()
{
}

DhGLRenderer::~DhGLRenderer()
{
}

void DhGLRenderer::Initialize(HWND hwnd)
{
	if (!glfwInit())
	{
		return;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "MathGL", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		return;
	}


	// get buffer size information
	int bufferWidth, bufferHeight;
	glfwGetFramebufferSize(window, &bufferWidth, &bufferHeight);

	// set context for GLEW to use
	glfwMakeContextCurrent(window);

	// allow modern extension features
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		glfwDestroyWindow(window);
		glfwTerminate();
		return;
	}

	// setup viewport size
	glViewport(0, 0, bufferWidth, bufferHeight);

	// loop until window closed
	while (!glfwWindowShouldClose(window))
	{
		// get + handle user input events
		glfwPollEvents();

		// clear window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
	}
}

void DhGLRenderer::Render()
{
}

void DhGLRenderer::Resize(int width, int height)
{
}

void DhGLRenderer::SetupPixelFormat(HDC hdc)
{
}
