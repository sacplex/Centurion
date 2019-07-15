#pragma once

#include "Centurion/Renderer/RendererAPI.h"

namespace Centurion
{
	class OpenGLRendererAPI : public RendererAPI
	{
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const std::shared_ptr<VertexReferenceArray>& vertexReferenceArray) override;
	};
}