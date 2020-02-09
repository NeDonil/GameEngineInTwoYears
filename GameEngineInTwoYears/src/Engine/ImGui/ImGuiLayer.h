#pragma once

#include "Engine/Layer.h"

#include "Engine/Event/ApplicationEvent.h"
#include "Engine/Event/MouseEvent.h"
#include "Engine/Event/KeyEvent.h"

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
		bool OnMouseButtonPressedEvent (MouseButtonPressedEvent&    e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent&   e);
		bool OnMouseMovedEvent         (MouseMovedEvent&            e);
		bool OnMouseScrolledEvent      (MouseScrolledEvent&         e);

		bool OnKeyPressedEvent         (KeyPressedEvent&            e);
		bool OnKeyReleasedEvent        (KeyReleasedEvent&           e);
        bool OnKeyTypedEvent           (KeyTypedEvent&              e);

		bool OnWindowResizedEvent      (WindowResizedEvent&         e);
	private:
		float m_Time = 0.0f;
	};
}