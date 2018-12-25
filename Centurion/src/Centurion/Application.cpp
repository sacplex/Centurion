#include "Application.h"

#include "Centurion/Events/ApplicationEvent.h"
#include "Log.h"

namespace Centurion {

	Application::Application()
	{
	}


	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		CTN_CORE_TRACE(e);

		while (true);
	}

}
