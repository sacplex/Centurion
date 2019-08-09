#include "ctnpch.h"
#include "Shader.h"
#include "Platform/OpenGL/OpenGLShader.h"

#include "Renderer.h"

namespace Centurion
{
	Shader* Shader::Create(const std::string& vertexSrc, std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: CTN_CORE_ASSERT(false, "RendererAPI::None is current not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLShader(vertexSrc, fragmentSrc);
		}

		CTN_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}