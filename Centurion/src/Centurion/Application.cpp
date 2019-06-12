#include "ctnpch.h"
#include "Application.h"
#include "Log.h"

namespace Centurion {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent)));
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
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose)));

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
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_Window->OnUpdate();
		}
	}


	bool Application::OnWindowClose(WindowCloseEvent &e)
	{
		m_Running = false;
		return true;
	}
}
