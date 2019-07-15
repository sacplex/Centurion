#include "ctnpch.h"
#include "VertexReferenceArray.h"
#include "Platform/OpenGL/OpenGLVertexReferenceArray.h"

#include "Renderer.h"

namespace Centurion
{
	VertexReferenceArray* VertexReferenceArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: CTN_CORE_ASSERT(false, "RendererAPI::None is current not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLVertexReferenceArray();
		}

		CTN_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}