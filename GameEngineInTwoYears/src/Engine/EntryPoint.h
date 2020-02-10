#pragma once
#include "Application.h"
#include "Log.h"
#include "Core.h"
#include "glm/glm.hpp"

#ifdef ENGINE_PLATFORM_WINDOWS
	
extern Engine::Application* Engine::CreateApplication();

int main(int argc, char** argv)
{
	Engine::Log::Init();
	ENGINE_CORE_INFO("Logger initialize success");

	auto app = Engine::CreateApplication();
	glm::vec3(1.0f);
	app->Run();
	delete app;
}

#endif