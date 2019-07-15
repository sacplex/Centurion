#pragma once

#include "RenderCommand.h"

namespace Centurion
{
	class Renderer
	{
	public:
		static void BeginScene();

		static void Submit(const std::shared_ptr<VertexReferenceArray>& vertexReferenceArray);

		static void EndScene();

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};	
}