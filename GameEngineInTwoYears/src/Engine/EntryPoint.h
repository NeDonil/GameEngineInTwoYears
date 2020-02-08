#pragma once
#include "Application.h"
#include "Log.h"
#include <iostream>
#include "Core.h"

#ifdef ENGINE_PLATFORM_WINDOWS
	
extern Engine::Application* Engine::CreateApplication();

int main(int argc, char** argv)
{
	Engine::Log::Init();
	ENGINE_CORE_ERROR("Dima pidor");
	int variable = 50;
	ENGINE_CLIENT_INFO("Variable is equal {0}", variable);
	auto app = Engine::CreateApplication();
	app->Run();
	delete app;
}

#endif