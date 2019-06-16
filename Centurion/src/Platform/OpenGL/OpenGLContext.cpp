#include "ctnpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Centurion
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandler(windowHandle)
	{
		CTN_ASSERT(windowHandle, "Window handle is null");
	}


	OpenGLContext::~OpenGLContext()
	{
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandler);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		CTN_CORE_ASSERT(status, "FAIL to initialise Glad!");

		CTN_CORE_INFO("OpenGL Info:");
		CTN_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		CTN_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		CTN_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandler);
	}
}


