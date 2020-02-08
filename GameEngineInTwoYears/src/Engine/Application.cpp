#include "enpch.h"
#include "GLFW/glfw3.h"
#include "Application.h"
#include "Event/ApplicationEvent.h"
#include "Log.h"

namespace Engine
{
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