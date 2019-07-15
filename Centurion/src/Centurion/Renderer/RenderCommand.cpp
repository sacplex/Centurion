#include "ctnpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Centurion
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}
