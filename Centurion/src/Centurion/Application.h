#pragma once

#include "Core.h"

namespace Centurion {

	class CENTURION_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
	};

	// To be defined in client
	Application* CreateApplication();
}
