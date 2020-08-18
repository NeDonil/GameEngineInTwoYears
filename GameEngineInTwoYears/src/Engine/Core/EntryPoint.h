#pragma once
#include "Application.h"
#include "Log.h"
#include "Core.h"

#ifdef ENGINE_PLATFORM_WINDOWS
	
extern Engine::Application* Engine::CreateApplication();

int main(int argc, char** argv)
{
	Engine::Log::Init();

#ifdef ENABLE_PROFILING
	ENGINE_PROFILE_BEGIN_SESSION("Startup", "EngineProfile-Startup.json");
		auto app = Engine::CreateApplication();
	ENGINE_PROFILE_END_SESSION();

	ENGINE_PROFILE_BEGIN_SESSION("Runtime", "EngineProfile-Runtime.json");
		app->Run();
	ENGINE_PROFILE_END_SESSION();

	ENGINE_PROFILE_BEGIN_SESSION("Shutdown", "EngineProfile-Shutdown.json");
		delete app;
	ENGINE_PROFILE_END_SESSION();
#else
	auto app = Engine::CreateApplication();
	app->Run();
	delete app;
#endif

}

#endif