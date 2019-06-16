#include "Centurion.h"

#include "imgui/imgui.h"

class ExampleLayer : public Centurion::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{}

	void OnUpdate() override
	{
		//CTN_CLIENT_INFO("ExampleLayer::Update");

		if (Centurion::Input::IsKeyPressed(CTN_KEY_TAB))
			CTN_CLIENT_INFO("Tab key is pressed!");
	}

	virtual void OnImGuiRender()
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello ImGui");
		ImGui::End();
	}

	void OnEvent(Centurion::Event& event) override
	{
		//CTN_CLIENT_TRACE("{0}", event);
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