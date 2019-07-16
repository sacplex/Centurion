#pragma once

#include "RenderCommand.h"
#include "OrthographicCamera.h"
#include "Shader.h"

namespace Centurion
{
	class Renderer
	{
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;
	public:
		static void BeginScene(OrthographicCamera& camera);

		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexReferenceArray>& vertexReferenceArray);

		static void EndScene();

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};	
}