#include "Application.h"
#include "Event/ApplicationEvent.h"
#include "Log.h"

namespace Engine
{
	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		WindowResizeEvent e(1366, 768);
		ENGINE_CLIENT_INFO(e);

		while (true);
	}
}