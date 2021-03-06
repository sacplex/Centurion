#pragma once

#include "RendererAPI.h"

namespace Centurion
{
	class RenderCommand
	{
	private:
		static RendererAPI* s_RendererAPI;
	public:
		inline static void SetClearColor(const glm::vec4& color)
		{
			s_RendererAPI->SetClearColor(color);
		}

		inline static void Clear()
		{
			s_RendererAPI->Clear();
		}

		inline static void DrawIndexed(const std::shared_ptr<VertexReferenceArray>& vertexReferenceArray)
		{
			s_RendererAPI->DrawIndexed(vertexReferenceArray);
		}
	};
}


