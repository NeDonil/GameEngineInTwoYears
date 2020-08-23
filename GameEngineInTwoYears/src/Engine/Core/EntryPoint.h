#pragma once
#include "Application.h"
#include "Log.h"
#include "Core.h"

#ifdef ENGINE_PLATFORM_WINDOWS
	
extern Engine::Application* Engine::CreateApplication();

int main(int argc, char** argv)
{
	Engine::Log::Init();

	auto app = Engine::CreateApplication();
	app->Run();
	delete app;

}

#endif