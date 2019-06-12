#pragma once

#include "Centurion/Layer.h"

namespace Centurion
{
	class CENTURION_API ImGuiLayer : public Layer
	{
	private:
		float m_time = 0.0f;
	public:
		ImGuiLayer();
		~ImGuiLayer();
		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& event);
	};
}


