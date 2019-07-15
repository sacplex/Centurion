#include "ctnpch.h"
#include "OpenGLVertexReferenceArray.h"

#include <glad/glad.h>

namespace Centurion
{
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case Centurion::ShaderDataType::Float:		return GL_FLOAT;
			case Centurion::ShaderDataType::Float2:		return GL_FLOAT;
			case Centurion::ShaderDataType::Float3:		return GL_FLOAT;
			case Centurion::ShaderDataType::Float4:		return GL_FLOAT;
			case Centurion::ShaderDataType::Mat3:		return GL_FLOAT;
			case Centurion::ShaderDataType::Mat4:		return GL_FLOAT;
			case Centurion::ShaderDataType::Int:		return GL_INT;
			case Centurion::ShaderDataType::Int2:		return GL_INT;
			case Centurion::ShaderDataType::Int3:		return GL_INT;
			case Centurion::ShaderDataType::Int4:		return GL_INT;
			case Centurion::ShaderDataType::Bool:		return GL_BOOL;
		}

		CTN_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	OpenGLVertexReferenceArray::OpenGLVertexReferenceArray()
	{
		glCreateVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexReferenceArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}
	
	void OpenGLVertexReferenceArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexReferenceArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		CTN_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();

		for (const auto& element : layout)
		{
			// Structure the data
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, element.GetComponentCount(), ShaderDataTypeToOpenGLBaseType(element.Type), element.Normalized ? GL_TRUE : GL_FALSE, layout.GetStride(), (const void*)element.Offset);
			index++;
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexReferenceArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}
}