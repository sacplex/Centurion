#include "ctnpch.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace Centurion
{
	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<VertexReferenceArray>& vertexReferenceArray)
	{
		glDrawElements(GL_TRIANGLES, vertexReferenceArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
}