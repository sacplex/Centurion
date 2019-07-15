#include "ctnpch.h"
#include "Application.h"
#include "Log.h"

#include <glad/glad.h>

#include "Input.h"

namespace Centurion {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	/*static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
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
	}*/

	Application::Application()
	{
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverLay(m_ImGuiLayer);

		//glGenVertexArrays(1, &m_VertexArray);
		//glBindVertexArray(m_VertexArray);

		m_VertexReferenceArray.reset(VertexReferenceArray::Create());
					
		float vertices[3 * 7] = { // Data is in the CPU
			-0.5, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
			0.5, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
			0.0, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
		};

		// Now, lets move the data to the GPU

		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		
		{
			BufferLayout layout = {
				{ShaderDataType::Float3, "a_Position"},
				{ShaderDataType::Float4, "a_Color"}
			};
			
			m_VertexBuffer->SetLayout(layout);
		}

		/*uint32_t index = 0;

		
		for (const auto& element : m_VertexBuffer->GetLayout())
		{
			// Structure the data
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, element.GetComponentCount(), ShaderDataTypeToOpenGLBaseType(element.Type), element.Normalized ? GL_TRUE : GL_FALSE, m_VertexBuffer->GetLayout().GetStride(), (const void*)element.Offset);
			index++;
		}*/

		m_VertexReferenceArray->AddVertexBuffer(m_VertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 }; // Order of drawing

		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) /  sizeof(uint32_t)));
		m_VertexReferenceArray->SetIndexBuffer(m_IndexBuffer);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position + 0.5;
				v_Color = a_Color;
				gl_Position = vec4(a_Position,1);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 colour;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{				
				colour = vec4(v_Position, 1.0);
				colour = v_Color;
			}
		)";

		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));
	}


	Application::~Application()
	{
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverLay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		CTN_CORE_TRACE("{0}", e);

		auto it = m_LayerStack.end();

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);

			break;

			if (e.Handled)
				break;
		}
	}
	
	void Application::Run()
	{

		while (m_Running)
		{
			glClearColor(0, 0, 0, 0);
			glClear(GL_COLOR_BUFFER_BIT);

			m_Shader->Bind();
			m_VertexReferenceArray->Bind();
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr); // Draw the indices

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_ImGuiLayer->Begin();

			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();

			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent &e)
	{
		m_Running = false;
		return true;
	}
}
