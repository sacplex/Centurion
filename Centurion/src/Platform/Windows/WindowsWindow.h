#pragma once

#include "Centurion/Window.h"

#include "Centurion/Renderer/RendererContext.h"

#include <GLFW/glfw3.h>

namespace Centurion {

	class WindowsWindow : public Window
	{
	private:
		GLFWwindow* m_Window;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
		RendererContext* m_Context;
	protected:
		virtual void Init(const WindowProps& props);
		virtual void ShutDown();
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		// Window attributes
		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		inline virtual void* GetNativeWindow() const { return m_Window; }
	};
}