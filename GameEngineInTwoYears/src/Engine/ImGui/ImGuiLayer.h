#pragma once

#include "Engine/Layer.h"

namespace Engine
{
	class ENGINE_API ImGuiLayer : public Engine::Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Engine::Event& event);
	private:
		float m_Time = 0.0f;
	};
}