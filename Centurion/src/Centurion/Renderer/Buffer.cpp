#include "ctnpch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Centurion
{
	VertexBuffer* VertexBuffer::Create(float* vertics, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None: CTN_CORE_ASSERT(false, "RendererAPI::None is current not supported!");
				return nullptr;
			case RendererAPI::OpenGL: 
				return new OpenGLVertexBuffer(vertics, size);
		}

		CTN_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None: CTN_CORE_ASSERT(false, "RendererAPI::None is current not supported!");
			return nullptr;
		case RendererAPI::OpenGL:
			return new OpenGLIndexBuffer(indices, size);
		}

		CTN_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}

