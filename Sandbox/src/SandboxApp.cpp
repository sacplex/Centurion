#include "Centurion.h"

#include "imgui/imgui.h"

class ExampleLayer : public Centurion::Layer
{
private:
	std::shared_ptr<Centurion::Shader> m_Shader;
	std::shared_ptr<Centurion::VertexReferenceArray> m_VertexReferenceArray;
	std::shared_ptr<Centurion::VertexBuffer> m_VertexBuffer;
	std::shared_ptr<Centurion::IndexBuffer> m_IndexBuffer;

	Centurion::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 1.0f;
	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 20.0f;
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		m_VertexReferenceArray.reset(Centurion::VertexReferenceArray::Create());

		float vertices[3 * 7] = { // Data is in the CPU
			-0.5, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
			0.5, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
			0.0, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
		};

		// Now, lets move the data to the GPU

		m_VertexBuffer.reset(Centurion::VertexBuffer::Create(vertices, sizeof(vertices)));

		{
			Centurion::BufferLayout layout = {
				{Centurion::ShaderDataType::Float3, "a_Position"},
				{Centurion::ShaderDataType::Float4, "a_Color"}
			};

			m_VertexBuffer->SetLayout(layout);
		}

		m_VertexReferenceArray->AddVertexBuffer(m_VertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 }; // Order of drawing

		m_IndexBuffer.reset(Centurion::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexReferenceArray->SetIndexBuffer(m_IndexBuffer);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position + 0.5;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position,1);
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

		m_Shader.reset(new Centurion::Shader(vertexSrc, fragmentSrc));
	}

	void OnUpdate(Centurion::DeltaTime deltaTime) override
	{
		CTN_CLIENT_TRACE("Delta time: {0}s ({1}ms)", deltaTime.GetSeconds(), deltaTime.GetMilliseconds());

		if (Centurion::Input::IsKeyPressed(CTN_KEY_LEFT))
		{
			m_CameraPosition.x += m_CameraMoveSpeed * deltaTime;
		}

		else if (Centurion::Input::IsKeyPressed(CTN_KEY_RIGHT))
		{
			m_CameraPosition.x -= m_CameraMoveSpeed * deltaTime;
		}

		if (Centurion::Input::IsKeyPressed(CTN_KEY_UP))
		{
			m_CameraPosition.y -= m_CameraMoveSpeed * deltaTime;
		}

		else if (Centurion::Input::IsKeyPressed(CTN_KEY_DOWN))
		{
			m_CameraPosition.y += m_CameraMoveSpeed * deltaTime;
		}

		if (Centurion::Input::IsKeyPressed(CTN_KEY_A))
			m_CameraRotation -= m_CameraRotationSpeed * deltaTime;

		if (Centurion::Input::IsKeyPressed(CTN_KEY_D))
			m_CameraRotation += m_CameraRotationSpeed * deltaTime;

		Centurion::RenderCommand::SetClearColor({ 0, 0, 0, 0 });
		Centurion::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Centurion::Renderer::BeginScene(m_Camera);
		Centurion::Renderer::Submit(m_Shader, m_VertexReferenceArray);
		Centurion::Renderer::EndScene();
	}

	virtual void OnImGuiRender()
	{
		
	}

	void OnEvent(Centurion::Event& event) override
	{
		Centurion::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<Centurion::KeyPressedEvent>(CTN_BIND_EVENT_FN(ExampleLayer::OnKeyPressedEvent));
	}

	bool OnKeyPressedEvent(Centurion::KeyPressedEvent& event)
	{
		return false;
	}
};

class Sandbox : public Centurion::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

Centurion::Application* Centurion::CreateApplication()
{
	return new Sandbox();
}