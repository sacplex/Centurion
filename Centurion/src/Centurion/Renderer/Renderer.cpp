#pragma once

#include "ctnpch.h"
#include "Renderer.h"

namespace Centurion
{
	void Renderer::BeginScene()
	{

	}

	void Renderer::Submit(const std::shared_ptr<VertexReferenceArray>& vertexReferenceArray)
	{
		vertexReferenceArray->Bind();
		RenderCommand::DrawIndexed(vertexReferenceArray);
	}

	void Renderer::EndScene()
	{

	}
}
