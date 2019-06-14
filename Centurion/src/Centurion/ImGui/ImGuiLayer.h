#pragma once

#include "Centurion/Layer.h"

#include "Centurion/Events/ApplicationEvent.h"
#include "Centurion/Events/KeyEvent.h"
#include "Centurion/Events/Mouse.h"

namespace Centurion
{
	class CENTURION_API ImGuiLayer : public Layer
	{
	private:
		float m_time = 0.0f;
	public:
		ImGuiLayer();
		~ImGuiLayer();
		virtual void OnAttach();
		virtual void OnDetach();
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	};
}


