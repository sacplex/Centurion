#pragma once

#include "Core.h"
#include "Core/DeltaTime.h"
#include "Events/ApplicationEvent.h"
#include "Events/Event.h"
#include "ImGui/ImGuiLayer.h"
#include "LayerStack.h"
#include "Window.h"

namespace Centurion {

	class Application
	{
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;

		LayerStack m_LayerStack;
		float m_LastFrameTime;

		static Application* s_Instance;
	public:
		Application();
		virtual ~Application();
		void Run();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverLay(Layer* layer);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	
	};

	// To be defined in client
	Application* CreateApplication();
}
