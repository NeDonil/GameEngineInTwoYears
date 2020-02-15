#pragma once
#include "Core.h"
#include "Window.h"
#include "Event/ApplicationEvent.h"
#include "Event/Event.h"
#include "LayerStack.h"
#include "ImGui/ImGuiLayer.h"

namespace Engine
{
	class ENGINE_API Application 
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		
		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		unsigned int m_VertexArray, m_VertexBuffer, m_ElementBuffer;
	private:
		static Application* s_Instance;
	};

	// To be defined in Client
	Application* CreateApplication();
}