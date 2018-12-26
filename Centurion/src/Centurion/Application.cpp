#include "ctnpch.h"
#include "Application.h"

#include "Centurion/Events/ApplicationEvent.h"
#include "Log.h"

namespace Centurion {

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}


	Application::~Application()
	{
	}

	void Application::Run()
	{

		while (m_Running)
		{
			m_Window->OnUpdate();
		}
	}

}
