#pragma once
#include "Application.h"

#ifdef ENGINE_PLATFORM_WINDOWS
	
extern Engine::Application* Engine::CreateApplication();

int main(int argc, char** argv)
{
	std::cout<< "Engine is working" << std::endl;
	auto app = Engine::CreateApplication();
	app->Run();
	delete app;
}

#endif