#pragma once

#include "Centurion/Renderer/RendererContext.h"

struct GLFWwindow;

namespace Centurion
{
	class OpenGLContext : public RendererContext
	{
	private:
		GLFWwindow* m_WindowHandler;
	public:
		OpenGLContext(GLFWwindow* windowHandler);
		~OpenGLContext();
		virtual void Init() override;
		virtual void SwapBuffers() override;
	};
}


