#pragma once

#include "ctnpch.h"
#include "Renderer.h"

namespace Centurion
{
	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData();

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexReferenceArray>& vertexReferenceArray, const glm::mat4& transform)
	{
		vertexReferenceArray->Bind();
		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
		shader->UploadUniformMat4("u_Transform", transform);
		RenderCommand::DrawIndexed(vertexReferenceArray);
	}

	void Renderer::EndScene()
	{

	}
}
