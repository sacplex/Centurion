#include "Centurion.h"

class ExampleLayer : public Centurion::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{}

	void OnUpdate() override
	{
		CTN_CLIENT_INFO("ExampleLayer::Update");
	}

	void OnEvent(Centurion::Event& event) override
	{
		CTN_CLIENT_TRACE("{0}", event);
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